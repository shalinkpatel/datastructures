import subprocess
import itertools
import pickle
from tqdm import tqdm
import time
import sys
import os

BASEBALL_EXE = './baseball'

if __name__ == '__main__':
	if len(sys.argv) > 1:
		BASEBALL_EXE = sys.argv[1]

	solutions = pickle.load(open('solutions.pickle', 'rb'))

	crashes = []
	weirds = []
	incorrects = []
	totalTime = 0

	for file in tqdm([i for i in os.listdir('testcases') if '.txt' in i]):
		f = open(os.path.join('testcases', file))
		f.readline()
		teamDict = {}
		games = []
		possibleWins = []
		wins = []
		for i, line in enumerate(f):
			c = line.split()
			if len(c) == 0:
				continue
			teamDict[c[0]] = i
			possibleWins.append(int(c[1])+int(c[3]))
			wins.append(int(c[1]))
			games.append([int(i) for i in c[4:]]) 
		f.close()

		p = subprocess.Popen([BASEBALL_EXE], stdout=subprocess.PIPE, stdin=subprocess.PIPE, encoding='utf8')
		start = time.time()
		output = p.communicate(open(os.path.join('testcases', file)).read())[0].split('\n')
		totalTime += time.time()-start

		if p.returncode != 0:
			print('Crashed with return code', p.returncode, 'on file', file)
			crashes.append(file)
			action = input('Continue or exit [C/e]? ')
			if action == 'e':
				sys.exit()
			else:
				continue

		try:
			wrong = []
			for line in output:
				c = line.split()
				if len(c) == 0:
					continue
				if c[2] == 'not':
					answer = False
				elif c[2] == 'eliminated':
					answer = True
				else:
					raise ValueError('Could not interpret answer')
				if answer != solutions[file][c[0]]:
					wrong.append(c[0]+' was '+('eliminated' if solutions[file][c[0]] else 'not eliminated')+', you said it was '+('eliminated' if answer else 'not eliminated'))
					continue
				if answer:
					toBeat = possibleWins[teamDict[c[0]]]
					cert = c[9:-1]
					totalWins = sum(wins[teamDict[i]] for i in cert)
					for game in itertools.combinations(cert, 2):
						totalWins += games[teamDict[game[0]]][teamDict[game[1]]]
					if toBeat >= (totalWins/len(cert)):
						wrong.append('Certificate for '+c[0]+"'s elimination was incorrect. You answered "+', '.join(cert)+'. However, this certificate only wins on average '+str(totalWins/len(cert))+' times, which is not enough to beat a possible '+str(toBeat)+' wins from '+c[0])
			if len(wrong) > 0:
				print('Incorrect answer(s) on file', file)
				incorrects.append(file)
				print('Error summary:')
				print('\n'.join(wrong))
				action = input('Continue or exit [C/e]? ')
				if action == 'e':
					sys.exit()
				else:
					continue
		except:
			print('Something weird happened on file', file)
			print('Probably your program outputted something unexpected')
			print('Make sure your output conforms exactly to the definition in the problem statement')
			weirds.append(file)
			action = input('Continue or exit [C/e]? ')
			if action == 'e':
				sys.exit()
			else:
				continue

	print('-----RUN SUMMARY-----')
	if len(crashes) > 0:
		print('Crashed on '+', '.join(crashes))
	if len(weirds) > 0:
		print('Weird stuff happened on '+', '.join(weirds))
	if len(incorrects) > 0:
		print('Incorrect on '+', '.join(incorrects))
	if len(crashes)+len(weirds)+len(incorrects) > 0:
		print('In total,', len(crashes)+len(weirds)+len(incorrects), 'cases failed')
	else:
		print('All cases passed!')
		print('Took', totalTime, 'seconds')
		