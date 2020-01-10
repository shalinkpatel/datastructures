import random
import subprocess
from tqdm import tqdm
import sys
from collections import deque, Counter

KOSARAJU_EXE = './kosaraju'

def makeGraph(nodes, avgEdge):
	edges = []

	for i in range(nodes):
		for j in range(nodes):
			if i==j:
				continue
			if random.random() < avgEdge/nodes:
				edges.append((i,j))
	return edges

def dfsutil(node, adj, visited):
	visited.add(node)
	for v in adj[node]:
		if v not in visited:
			dfsutil(v, adj, visited)

def dfs(node, adj):
	visited = set()
	dfsutil(node, adj, visited)
	return visited

def dumbSolver(nodes, edges, toPrint=False):
	adjacent = [[] for i in range(nodes)]
	for edge in edges:
		adjacent[edge[0]].append(edge[1])

	reachable = [dfs(node, adjacent) for node in range(nodes)]
	compDA = [-1]*nodes
	compSet = []
	edgeList = []
	edgeSet = set()
	sc = 0
	for i, reached in enumerate(reachable):
		if compDA[i] == -1:
			compSet.append(set())
			compDA[i] = sc
			for node in reached:
				if i in reachable[node]:
					compDA[node] = sc
					compSet[sc].add(node)
			sc+=1

		for node in adjacent[i]:
			if compDA[i] != compDA[node]:
					edgeList.append((i, node))

	edgeSet = {(compDA[i], compDA[node]) for i, node in edgeList}

	if toPrint:
		print(len(compSet))
		for sc in compSet:
			print(len(sc), end='')
			for node in sc:
				print(' '+str(node), end='')
			print('')

		print(len(edgeSet))
		for edge in edgeSet:
			print(compDA[edge[0]], compDA[edge[1]])

	return set([frozenset(i) for i in compSet]), Counter([(frozenset(compSet[edge[0]]), frozenset(compSet[edge[1]])) for edge in edgeSet])

def getRawOutput(nodes, edges):
	p = subprocess.Popen([KOSARAJU_EXE], stdout=subprocess.PIPE, stdin=subprocess.PIPE, encoding='utf8')
	return p.communicate(str(nodes)+' '+str(len(edges))+'\n'+'\n'.join([str(edge[0])+' '+str(edge[1]) for edge in edges]))[0]

def getExternSolve(nodes, edges):
	output = getRawOutput(nodes, edges)
	outputQ = deque(output.split())
	nsc = int(outputQ.popleft())
	compSet = [frozenset([int(outputQ.popleft()) for n in range(int(outputQ.popleft()))]) for sc in range(nsc)]
	ne = int(outputQ.popleft())
	return set(compSet), Counter([(compSet[int(outputQ.popleft())], compSet[int(outputQ.popleft())]) for n in range(ne)])

print("Will test 10000 graphs total, size 10-100")

for j in range(1, 11):
	nodes = j*10
	print("Testing graphs of size", nodes)
	for i in tqdm(range(1000)):
		edges = makeGraph(nodes, 3)
		set1, solved1 = dumbSolver(nodes, edges)
		set2, solved2 = getExternSolve(nodes, edges)
		if solved1 != solved2 or set1 != set2:
			print("Wrong answer at graph of size", nodes)
			print("Input was:")
			print(nodes, len(edges))
			for edge in edges:
				print(edge[0], edge[1])
			print("Right answer:")
			dumbSolver(nodes, edges, True)
			print("You answered:")
			print(getRawOutput(nodes, edges))
			sys.exit()

print("yay, everything passed (unless tester code is broken lol)")

'''edges = makeGraph(20, 3)
solved1 = dumbSolver(20, edges, True)
print('')
print(getRawOutput(20, edges))
solved2 = getExternSolve(20, edges)
print(solved1)
print(solved2)
print(solved1 == solved2)'''
