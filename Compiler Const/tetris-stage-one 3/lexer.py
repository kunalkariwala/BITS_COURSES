from sly import Lexer
import sys

class CalcLexer(Lexer):

    reserved_keywords = {
        'if': 'IF',
        'else': 'ELSE',
        'while': 'WHILE',
        'for': 'FOR',
        'print': 'PRINT'
    }

    reserved_tetrimino_movement = {
        'rotate_cw': 'ROTATE_CW',
        'rotate_acw': 'ROTATE_ACW',
        'move_left': 'MOVE_LEFT',
        'move_right' : 'MOVE_RIGHT',
        'pause' : 'PAUSE',
        'drop_speed' : 'DROPSPEED',
        'hard_drop' : 'HARDROP',
        'soft_drop' : 'SOFTDROP',
    }

    reserved_tetrimino = {
        'Mino' : 'MINO',
        'Tetrimino': 'TETRIMINO',
        'O_TETRIMINO': 'O_TETRIMINO',
        'I_TETRIMINO': 'I_TETRIMINO',
        'T_TETRIMINO': 'T_TETRIMINO',
        'L_TETRIMINO': 'L_TETRIMINO',
        'J_TETRIMINO': 'J_TETRIMINO',
        'S_TETRIMINO': 'S_TETRIMINO',
        'Z_TETRIMINO': 'Z_TETRIMINO',
    }

    tokens = { SEMICOLON, COMMA, DOT,
               PLUS, MINUS, TIMES, DIVIDE,
               EQ, ASSIGN, LE, LT, GE, GT, NE,
               L_PAREN, R_PAREN, L_CURLY, R_CURLY,
               FLOAT, NUMBER, STRING, BOOL,
               ID, COLOR
               }

    tokens = tokens.union(set(reserved_keywords.values()))
    tokens = tokens.union(set(reserved_tetrimino_movement.values()))
    tokens = tokens.union(set(reserved_tetrimino.values()))

    # String containing ignored characters
    ignore = ' \t\r'

    # Regular expression rules for tokens

    # token for comment
    ignore_comment = r'//.*'

    SEMICOLON = r';'
    COMMA = r','
    DOT = r'\.'

    # tokens for arithmetic operators
    PLUS    = r'\+'
    MINUS   = r'-'
    TIMES   = r'\*'
    DIVIDE  = r'/'

    # tokens for relational operators
    EQ      = r'=='
    ASSIGN  = r'='
    LE      = r'<='
    LT      = r'<'
    GE      = r'>='
    GT      = r'>'
    NE      = r'!='

    # tokens for brackets
    L_PAREN = r'\('
    R_PAREN = r'\)'
    L_CURLY = r'\{'
    R_CURLY = r'\}'

    # token for datatypes
    FLOAT = r'\d+.\d+'
    NUMBER = r'\d+'
    STRING = r'\".*?\"'
    BOOL = r'(TRUE|FALSE)'

    # token for color
    COLOR = r'#([a-fA-F0-9]{6})'

    # token for identifiers
    @_(r'[a-zA-Z_][a-zA-Z0-9_]*')
    def ID(self, t):
        t.type = self.reserved_keywords.get(t.value, 'ID')
        if (t.type == 'ID'):
            t.type = self.reserved_tetrimino.get(t.value, 'ID')
        if (t.type == 'ID'):
            t.type = self.reserved_tetrimino_movement.get(t.value, 'ID')
        return t

    # Line number tracking
    @_(r'\n+')
    def ignore_newline(self, t):
        self.lineno += t.value.count('\n')

    # Handling bad characters
    def error(self, t):
        print('Line %d: Bad character %r' % (self.lineno, t.value[0]))
        self.index += 1


if __name__ == '__main__':
    lexer = CalcLexer()
    with open(sys.argv[1], 'r') as file:
        data = file.read()
    for tok in lexer.tokenize(data):
        print(tok)

    # Q1.(ii)
    print("Number of distinct patterns: ", len(lexer._rules))
    # Ans = 26

    # Q1. (iii)
    print("Number of distinct token types: ",len(lexer.tokens))
    # Ans = 46

    # Q1. (v)
    count = 0
    for token in lexer.tokens:
        if type(token) == int:
            count += 1
    print("Number of enumerated tokens :", count)
    # Ans = 0

    # Q1. (vi)
    count = 0
    for rule in lexer._rules:
        if rule[0] == rule[1]:  # tokentype == lexeme(pattern)
            count += 1
    print("Number of tokens where the token are just the lexemes themselves: ", count)

    # Q1. (vii)
    print("Regexp for all the characters that will be just ignored by your lexer :")
    print(lexer.ignore)
    print(lexer.ignore_comment)
    print(lexer.ignore_newline.pattern)
    # Ans =  ((⊔\t\r)|(//.*)|(\n+))
    # ⊔ represents white space