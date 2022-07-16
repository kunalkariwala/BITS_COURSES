# tetlexer.py
 
from sly import Lexer
 
class tetLexer(Lexer):
    # Set of token names
    tokens = {EOS, COMMA, NUM, STR, BOOL, COMMENT, EOL, DIMS, SOUND, PCS, K_KEY, SPEED, PGA_BIAS, DISCO_MODE, GHOST_MODE, SCORING, OPENING_MSG, ENDING_MSG, OPEN_BRACKET, CLOSE_BRACKET, ARITHOP, ASSIGN, RELOP, COLOR}
 
    # String containing ignored characters between tokens
    ignore = ' \t'
 
    # Regular expression rules for tokens
    EOS = r';'
    COMMA = r','
    NUM = r'[0-9]+'
    STR = r'\".*?\"' #non greedy string matching i.e end matching till first " is encountered
    BOOL = r'(ON|OFF)'
    COMMENT = r'//.*'
    EOL = r'\n'
    DIMS = r'board'
    SOUND = r'sound'
    PCS = r'pieces'
    K_KEY = r'(rotate|go_left|go_right|soft_drop|hard_drop|pause)'
    SPEED = r'speed'
    PGA_BIAS = r'pga_bias'
    DISCO_MODE = r'disco_mode'
    GHOST_MODE = r'ghost_mode'
    SCORING = r'scoring'
    OPENING_MSG = r'opening_msg'
    ENDING_MSG = r'ending_msg'
    OPEN_BRACKET = r'(\(|\[|\{)'
    CLOSE_BRACKET = r'(\)|\]|\})'
    ARITHOP = r'(\+|-|\*|/)'
    ASSIGN = r'='
    RELOP = r'(<=|>=|<|>|<>)'
    COLOR = r'#([0-9a-fA-F]{6})'
 
    def count(self):
        for token in self.tokens:
            print((token))
    
if __name__ == '__main__':
    i = 1
 
    lexer = tetLexer()

    """
    Lengths of lexemes:
        Fixed length:
            * EOS, COMMA, EOL, OPEN_BRACKET, CLOSE_BRACKET, ARITHOP, ASSIGN .. 1 each
            * DIMS, SOUND, SPEED ............................................. 5 each
            * PCS ............................................................ 6
            * COLOR, SCORING ................................................. 7 each
            * PGA_BIAS ....................................................... 8
            * DISCO_MODE, GHOST_MODE, ENDING_MSG ............................. 10 each
            * OPENING_MSG .................................................... 11
        Variable length:
            * NUM ............................................................ >=1
            * STR ............................................................ >=2
            * BOOL ........................................................... 2 (ON) or 3 (OFF)
            * COMMENT ........................................................ >=2
            * K_KEY .......................................................... depends on the value
            * RELOP .......................................................... 1 (<, >) or 2 (<=, >=, <>)

    """
    print("Number of tokens = ", len(lexer.tokens))                          # Ans. 24
    print("Number of ignore tokens = ", len(lexer.ignore))                   # Ans. 2
    print("Number of patterns = ", len(lexer.tokens) + len(lexer.ignore))    # Ans. 26
    print("Number of tokens encoded as enumerated types or numbers = none")  # Ans. 0
    print("Number of unique lexemes = 14")                                   # Ans. 14 [EOS, COMMA, EOL, DIMS, SOUND, PCS, SPEED, PGA_BIAS, DISCO_MODE, GHOST_MODE, SCORING, OPENING_MSG, CLOSING_MSG, ASSIGN]