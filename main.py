from game.snake import *
from time import sleep
from ctypes import *
from argparse import ArgumentParser
import os

# 0 : left
# 1 : right
# 2 : up
# 3 : down

if os.name == 'nt':
    os.system('del *.so')
else:
    os.system('rm *.so')
try:
    os.system('gcc --std=c11 -shared -o lib_action.so -fPIC lib_action.c')
    _action = CDLL('./lib_action.so')
except Exception as e:
    print('ERROR : Check gcc or lib_action.c')
    print(str(e))
    exit(0)

parser = ArgumentParser()
parser.add_argument("--play", required = False, action = 'store_true')
parser.add_argument("--visual", required = False, action = 'store_true')
parser.add_argument("-time", required = False, default = 500, type = int)
parser.add_argument("-board_size", required = False, default = 10, type = int)

args = parser.parse_args() # Receive arguments

RELATIVE_POS = False
local_state = False

board_size = args.board_size
visual = args.visual
play = args.play

game = Game(player = "ROBOT",
            board_size = board_size,
            local_state = local_state,
            relative_pos = RELATIVE_POS)

game.reset()

if play is True:
    game.create_window()
    game.start()
    exit(0)

score = 0
N = 1000
if visual:
    N = 1
for t in range(N):
    time = args.time
    game.reset()
    while not game.game_over and time > 0:
        state = game.state().tolist()
        # state = game.state()
        # print(state)
        # state = state.tolist()
        board = (c_char_p * 10)()
        for i in range(10):
            row = ''
            for x in state[i]:
                row += chr(x)
            row = row.encode('utf-8')
            state[i] = row
        board[:] = state

        body = game.snake.body.copy()
        cbody = (c_char_p * game.snake.length)()

        for i in range(game.snake.length):
            row = ''
            row += chr(game.snake.body[i][0])
            row += chr(game.snake.body[i][1])
            row = row.encode('utf-8')
            body[i] = row
        cbody[:] = body
        prv = game.snake.previous_action

        nxt = _action.action_decision(board, cbody, game.snake.length, prv, time)
        game.play(nxt)
        if visual:
            game.render()
        time -= 1
    if not visual:
        print('#%d score : %d' % (t + 1, game.snake.length - 3))
    score += game.snake.length - 3

print('total score : %f' % (score / N))
