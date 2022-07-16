import ply.lex as lex
 # List of token names.   This is always required
 tokens = ('NUMBER', 'PLUS', 'MINUS', 'TIMES', 'DIVIDE', 'LPAREN', 'RPAREN', )
 # Regular expression rules for simple tokens
 t_PLUS    = r'\+'
 t_MINUS   = r'-'
 t_TIMES   = r'\*'
 t_DIVIDE  = r'/'
 t_LPAREN  = r'\('
 t_RPAREN  = r'\)'
 t_ignore  = ' \t'
 
 # Regular expression rules with some / that require action code
 def t_NUMBER(t):
     r'\d+'
     t.value = int(t.value)    
     return t 
 # Build the lexer
 lexer = lex.lex()
