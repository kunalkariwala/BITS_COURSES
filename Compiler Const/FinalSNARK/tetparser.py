from sly import Parser
from tetlexer import tetLexer

class tetParser(Parser):

	cnt = 1
	data_map = dict()

	tokens = tetLexer.tokens

	@_('expr_list expr')
	def expr_list(self, p):
		return p

	@_('expr')
	def expr_list(self, p):
		return p

	@_('assign_expr SEMICOLON')
	def expr(self,p):
		return p

	@_('EOL')
	def expr(self,p):
		self.cnt += 1
		return p
	
	@_('COMMENT')
	def expr(self,p):
		return p

	#############################Arithmetic operations######################################

	@_('expr2 PLUS term')
	def expr2(self,p): 
		self.data_map[p[1]] = p.expr2 + p.term
		return p.expr2 + p.term
	
	@_('expr2 MINUS term')
	def expr2(self,p):
		return p.expr2 - p.term
	
	@_('expr2 TIMES term')
	def expr2(self,p):return p.expr2 * p.term

	@_('expr2 DIVIDE term')
	def expr2(self,p):return p.expr2 / p.term

	@_('term')
	def expr2(self,p):return p.term

	@_('term TIMES factor')
	def term(self,p):return p.term * p.factor

	@_('term DIVIDE factor')
	def term(self,p):return p.term / p.factor

	@_('factor')
	def term(self,p):return p.factor

	@_('NUMBER')
	def factor(self,p): return int(p.NUMBER)

	@_('L_PAREN expr2 R_PAREN')
	def factor(self,p): return p.expr2

	########################################################################################

	########################

	@_('bool_assign')
	def assign_expr(self,p):
		return p

	@_('num_assign')
	def assign_expr(self,p):
		return p

	@_('str_assign')
	def assign_expr(self,p):
		return p

	@_('array_assign')
	def assign_expr(self,p):
		return p
		
	########################

	@_('bool_var ASSIGN BOOL')
	def bool_assign(self,p):
		self.data_map[p.bool_var] = (p.BOOL == "TRUE")
		print("bool_var: ", p.bool_var)
		return p

	@_('SINGLE_PLAYER')
	def bool_var(self,p):
		return "SINGLE_PLAYER"

	########################

	@_('num_var ASSIGN NUMBER')
	def num_assign(self,p):
		self.data_map[p.num_var] = int(p.NUMBER)
		print("num_var: ", p.num_var)
		return p
	
	@_('num_var ASSIGN expr2')
	def num_assign(self,p):
		self.data_map[p.num_var] = int(p.expr2)
		print("num_var: ",p.num_var)
		return p

	@_('SPEED')
	def num_var(self,p):
		return "speed"

	########################
	@_('ROWS')
	def num_var(self,p):
		return "rows"

	@_('COLUMNS')
	def num_var(sefl,p):return "columns"
    		

	@_('str_var ASSIGN STRING')
	def str_assign(self,p):
		self.data_map[p.str_var] = p.STRING
		print("str_var: ", p.str_var)
		return p

	@_('MOVEMENTS')
	def str_var(self,p):
		return p.MOVEMENTS
	
	@_('')

	@_('OPENING_MSG')
	def str_var(self,p):
		return p.OPENING_MSG

	@_('ENDING_MSG')
	def str_var(self,p):
		return p.ENDING_MSG

	########################

	@_('scoring_set')
	def array_assign(self,p):
		self.data_map["points"] = p.scoring_set
		print("array_var: ", "scoring_set")
		return p

	@_('pieces_set')
	def array_assign(self,p):
		for pc_spec in p.pieces_set:
			self.data_map[pc_spec[0]] = pc_spec
		print("array_var: ", "pieces_set")
		return p


	@_('SCORING ASSIGN L_SQUARE number_list R_SQUARE')
	def scoring_set(self,p):
		return p.number_list

	@_('number_list COMMA NUMBER')
	def number_list(self,p):
		num_list = p.number_list
		num_list.append(p.NUMBER)
		return num_list

	@_('NUMBER')
	def number_list(self,p):
		return [p.NUMBER]

	@_('TETRMINOS ASSIGN L_SQUARE piece_list R_SQUARE')
	def pieces_set(self,p):

		return p.piece_list

	@_('piece_list COMMA tuples')
	def piece_list(self,p):
		pcs = p.piece_list
		pcs.append(p.tuples)
		return pcs

	@_('tuples')
	def piece_list(self,p):
		return [p.tuples]

	@_('L_TETRIMINO')
	def TTYPE(self,p):return p.L_TETRIMINO

	@_('I_TETRIMINO')
	def TTYPE(self,p):return p.I_TETRIMINO

	@_('T_TETRIMINO')
	def TTYPE(self,p):return p.T_TETRIMINO

	@_('O_TETRIMINO')
	def TTYPE(self,p):return p.O_TETRIMINO

	@_('J_TETRIMINO')
	def TTYPE(self,p):return p.J_TETRIMINO

	@_('S_TETRIMINO')
	def TTYPE(self,p):return p.S_TETRIMINO

	@_('Z_TETRIMINO')
	def TTYPE(self,p):return p.Z_TETRIMINO

	@_('L_PAREN COLOR COMMA TTYPE R_PAREN')
	def tuples(self,p):
		color_hex = str(p.COLOR)
		color_hex_int = []
		for ch in color_hex:
			if ord('0') <= ord(ch) <= ord('9'):
				color_hex_int.append(ord(ch)-ord('0'))
			elif ord('a') <= ord(ch) <= ord('z'):
				color_hex_int.append(ord(ch)-ord('a')+10)
			elif ord('A') <= ord(ch) <= ord('Z'):
				color_hex_int.append(ord(ch)-ord('A')+10)

		color = (color_hex_int[0]*16 + color_hex_int[1],
					color_hex_int[2]*16 + color_hex_int[3],
					color_hex_int[4]*16 + color_hex_int[5])
		print("colour : ", color)
		print("Tetrimino :", p.TTYPE)
		return (p.TTYPE, color)


if __name__ == '__main__':
	lexer = tetLexer()
	parser = tetParser()
 
	# while True:
	
 
	with open('tet_conf.tads', 'r') as fileh:
		text = fileh.read()
		# for tok in lexer.tokenize(text):
		# 	print('type=%r, value=%r' % (tok.type, tok.value))
		# print(text)
		
		# for tok in lexer.tokenize(data):
		#	 print('\tt<%r>,%r' % (tok.type, tok.value))
	
		# text = input('> ')
		# try:
		result = parser.parse(lexer.tokenize(text))
		# print(result)
		print(parser.data_map)
				