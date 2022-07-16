# tetlexer.py
 
from tkinter import SINGLE
from sly import Lexer
 
class tetLexer(Lexer):
    # Set of token names
    tokens = {
    BLOCK_SIZE,BORDER,ROWS,COLS,SCREEN_HEIGHT,
    SCREEN_WIDTH,SCREEN_SIZE,FONT_SIZE,
    TICK_INTERVAL,DELAY,REPEAT,SPEED,
    EMPTY_COLOR,BOUNDARY_COLOR,BORDER_THICKNESS,
    EMPTY_CELL,BOUNDARY_CELL,POINTS,
    SCORE,SINGLE_PLAYER,ROTATE_ACW,
    ROTATE_CW,MOVE_LEFT,MOVE_RIGHT,
    PAUSE,DROPSPEED,HARDROP,
    SOFTDROP,O_TETRIMINO,L_TETRIMINO,
    I_TETRIMINO,T_TETRIMINO,J_TETRIMINO,
    S_TETRIMINO,Z_TETRIMINO ,PLUS,
    MINUS,TIMES,DIVIDE, SEMICOLON, 
    COMMA,DECIMAL_NUMBER,NUMBER, STRING, BOOL, 
    COMMENT, EOL, TETRMINOS, 
    K_KEY,SCORING, OPENING_MSG, ENDING_MSG, 
    L_CURLY,L_PAREN,L_SQUARE,
    R_CURLY,R_PAREN,R_SQUARE, ASSIGN, COLOR,BORDER_COLOR,
    COLOR_VAR,SCORE_COLOR,SCREEN_COLOR,TETCOLORS
    }
    
    # String containing ignored characters between tokens
    ignore = ' \t'
    # Regular expression rules for tokens
    O_TETRIMINO = r'O_TETRMINO'
    I_TETRIMINO = r'I_TETRMINO'
    L_TETRIMINO = r'L_TETRMINO'
    T_TETRIMINO = r'T_TETRMINO'
    J_TETRIMINO = r'J_TETRMINO'
    S_TETRIMINO = r'S_TETRMINO'
    Z_TETRIMINO = r'Z_TETRMINO'

    COLOR_VAR = r'COLOR_([A-Za-z]+)'
    SCORE_COLOR = r'scoreColor'
    SCREEN_COLOR = r'screenColor'
    BLOCK_SIZE = r'blockSize'
    BORDER = r'border'
    ROWS = r'rows'
    COLS = r'cols'
    SCREEN_HEIGHT = r'screenHeight'
    SCREEN_WIDTH = r'screenWidth'
    SCREEN_SIZE = r'screenSize'
    FONT_SIZE = r'fontSize'

    TICK_INTERVAL = r'tickInterval'
    DELAY = r'delay'
    REPEAT = r'repeat'
    SPEED = r'speed'

    EMPTY_COLOR = r'emptyColor'
    BOUNDARY_COLOR = r'boundaryColor'
    BORDER_COLOR = r'colorBorder'
    BORDER_THICKNESS = r'thicknessBorder'
    EMPTY_CELL = r'emptyCell'
    BOUNDARY_CELL = r'boundaryCell'
    POINTS = r'points'
    SCORE = r'score'
    SINGLE_PLAYER = r'singlePlayer'
    TETCOLORS = r'tetriminoColors'

    ROTATE_CW = r'rotate_cw'
    ROTATE_ACW = r'rotate_acw'
    MOVE_LEFT = r'move_left'
    MOVE_RIGHT = r'move_right'
    PAUSE = r'pause'
    DROPSPEED = r'drop_speed'
    HARDROP = r'hard_drop'
    SOFTDROP = r'soft_drop'

    SEMICOLON = r';'
    COMMA = r','
    DECIMAL_NUMBER = r'[0-9]+\.[0-9]*|\.[0-9]+'
    NUMBER = r'[0-9]+'
    STRING = r'\".*?\"'
    BOOL = r'(TRUE|FALSE)'

    COMMENT = r'//.*'
    EOL = r'\n'
    TETRMINOS = r'tetriminos'
    SCORING = r'scoring'
    OPENING_MSG = r'opening_msg'
    ENDING_MSG = r'ending_msg'

    L_PAREN = r'\('
    R_PAREN = r'\)'
    L_CURLY = r'\{'
    R_CURLY = r'\}'
    L_SQUARE = r'\['
    R_SQUARE = r'\]'
    
    PLUS    = r'\+'
    MINUS   = r'\-'
    TIMES   = r'\*'
    DIVIDE  = r'/'
    ASSIGN = r'='
    COLOR = r'#([0-9a-fA-F]{6})'
 
    def count(self):
        for token in self.tokens:
            print((token))
    
if __name__ == '__main__':
    i = 1
 
    lexer = tetLexer()
    print(lexer.tokens)