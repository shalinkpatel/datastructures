from subprocess import Popen, PIPE
from treys import Card, Evaluator
import random
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from tqdm import tqdm

matplotlib.rcParams['interactive'] == True


players = int(input("number of players: "))
commands = [input("command for player "+str(i+1)+"?: ") for i in range(players)]
names = [input("name for player "+str(i+1)+"?: ") for i in range(players)]
itr = int(input("number of iterations: "))
prog = [Popen(command.split(), shell=True, stdout=PIPE, stdin=PIPE, stderr=None) for command in commands]

fig, ax = plt.subplots()
hs = [None]*players
for i in range(players):
    hs[i], = ax.plot([], [], label=names[i])
    ax.set(title="Poker Hands", xlabel="Hands", ylabel="Wins")
legend = ax.legend()

def conv_card(card):
    rank = card // 4
    suit = 1 << (card % 4)
    return Card.new(Card.int_to_str((rank << 8) + (suit << 12)))

def conv(hand):
    return list(map(conv_card, hand))
    
def upd(wins):
    dp = len(hs[0].get_xdata())
    
    for i in range(players):
        hs[i].set_ydata(np.append(hs[i].get_ydata(), wins[i]))
        hs[i].set_xdata(np.append(hs[i].get_xdata(), dp))
    
    ax.relim()
    ax.autoscale_view() 
    
    plt.draw()
    plt.pause(0.0001)


evaluator = Evaluator()
wins = [0]*players

for game in tqdm(range(itr)):
    # print('playing game',game+1)
    scores = [None]*players
    
    for player,e in enumerate(prog):
        deck = list(range(52))
        random.shuffle(deck)
        hand = [deck.pop() for i in range(5)]
        #print(commands[player])
        #print('\tplayer',player,'started with',Card.print_pretty_cards(conv(hand)))
        
        s = ' '.join(map(str, hand))
        e.stdin.write(bytes(s + '\n', 'UTF-8'))
        e.stdin.flush()
        
        l = list(map(int,e.stdout.readline().strip().split()))
        for x in l[1:]:
            for i in range(5):
                if hand[i] == x:
                    hand[i] = deck.pop()
                    break
        
        # for i in range(len(hand)):
        #     hand[i] = (hand[i]//13) + (hand[i]%13)*4
        hand = conv(hand)
        scores[player] = evaluator.evaluate(hand, [])            
        #print('\tplayer',player,'ended with',Card.print_pretty_cards(hand),'score =',scores[player])

    mx = min(scores)

    
    for i in range(players):
        if scores[i] == mx:
            wins[i] += 1
            
    upd(wins)

for e in prog:
    e.kill()
    
plt.show()
print('wins', wins)