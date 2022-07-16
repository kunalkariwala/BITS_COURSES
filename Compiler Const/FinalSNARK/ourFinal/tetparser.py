from tkinter.font import BOLD
from sly import Parser
from tetlexer import tetLexer

class tetParser(Parser):

	cnt = 1
	data_map = dict()
	colors = []
	tokens = tetLexer.tokens
	points = []

	##########################################################################################
	################################## EXPR LIST #############################################
	########################################################################################## 

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

	##########################################################################################
	################################## EXPR LIST #############################################
	########################################################################################## 




	##########################################################################################
	############################### ASSIGNS EXPR #############################################
	########################################################################################## 

	@_('color_assign')
	def assign_expr(self,p):
		return p
    
	@_('color_tup_assign')
	def assign_expr(self,p):
		return p
    
	@_('num_assign')
	def assign_expr(self,p):
		return p

	@_('color_arr_assign')
	def assign_expr(self,p):
		return p
	
	@_('num_arr_assign')
	def assign_expr(self,p):
		return p

	@_('bool_assign')
	def assign_expr(self,p):
		return p

	##########################################################################################
	############################### ASSIGNS EXPR #############################################
	##########################################################################################







	##########################################################################################
	############################### BOOL ASSIGNS #############################################
	########################################################################################## 

	@_('bool_var ASSIGN BOOL')
	def bool_assign(self,p):
		self.data_map[p.bool_var] = (p.BOOL == "TRUE")
		print("bool_var: ", p.bool_var)
		return p

	@_('SINGLE_PLAYER')
	def bool_var(self,p):
		return "SINGLE_PLAYER"


	##########################################################################################
	############################### BOOL ASSIGNS #############################################
	########################################################################################## 




    
    
	##########################################################################################
	############################### COLOUR ASSIGNS ###########################################
	##########################################################################################

	@_('TETCOLORS ASSIGN color_arr')
	def color_arr_assign(self,p):
		# self.data_map[p.TETCOLORS] = p.color_arr
		print(p.color_arr)
		return p

	@_('L_SQUARE color_list R_SQUARE')
	def color_arr(self,p):
		return p

	@_('color_list COMMA COLOR')
	def color_list(self,p):
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
		self.colors.append(color)
		return p
	
	@_('COLOR')
	def color_list(self,p):
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
		self.colors.append(color)
		return p

	@_('COLOR_VAR ASSIGN COLOR')
	def color_assign(self,p):
		# self.data_map[p.COLOR_VAR] = p.COLOR
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
		self.data_map[p.COLOR_VAR] = color
		print("COLOR_VAR : ", p.COLOR_VAR)
		return p

	@_('COLOR_VAR ASSIGN color_tup')
	def color_tup_assign(self,p):
		color_tuple_str = str(p.color_tup)
		num_tup_one = []
		num_tup_two = []
		num_encountered = 0
		num_tup_three = []
		index = 0
		for ch in color_tuple_str:
			# print(ch)
			if ord('0') <= ord(ch) <= ord('9'):
				num_encountered = num_encountered + 1
				# print("OUTER")
				if index == 0:
					# print("first")
					num_tup_one.append(ord(ch)-ord('0'))
				elif index == 1:
					# print("second")
					num_tup_two.append(ord(ch)-ord('0'))
				elif index == 2:
					# print("third")
					num_tup_three.append(ord(ch)-ord('0'))
				if num_encountered == 3:
					num_encountered = 0
					index = index + 1
		# print(num_tup_one)
		# print(num_tup_two)
		# print(num_tup_three)
		color = (num_tup_one[0]*100 + num_tup_one[1]*10+num_tup_one[2] , num_tup_two[0]*100 + num_tup_two[1]*10+num_tup_two[2], num_tup_three[0]*100 + num_tup_three[1]*10+num_tup_three[2])
		self.data_map[p.COLOR_VAR] = color
		print("COLOR_VAR : ", p.COLOR_VAR)
		return p

	@_('SCORE_COLOR ASSIGN COLOR')
	def color_assign(self,p):
		# self.data_map[p.COLOR_VAR] = p.COLOR
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
		self.data_map[p.SCORE_COLOR] = color
		print("SCORE_COLOR : ", p.SCORE_COLOR)
		return p

	@_('SCORE_COLOR ASSIGN color_tup')
	def color_tup_assign(self,p):
		color_tuple_str = str(p.color_tup)
		num_tup_one = []
		num_tup_two = []
		num_encountered = 0
		num_tup_three = []
		index = 0
		for ch in color_tuple_str:
			# print(ch)
			if ord('0') <= ord(ch) <= ord('9'):
				num_encountered = num_encountered + 1
				# print("OUTER")
				if index == 0:
					# print("first")
					num_tup_one.append(ord(ch)-ord('0'))
				elif index == 1:
					# print("second")
					num_tup_two.append(ord(ch)-ord('0'))
				elif index == 2:
					# print("third")
					num_tup_three.append(ord(ch)-ord('0'))
				if num_encountered == 3:
					num_encountered = 0
					index = index + 1
		# print(num_tup_one)
		# print(num_tup_two)
		# print(num_tup_three)
		color = (num_tup_one[0]*100 + num_tup_one[1]*10+num_tup_one[2] , num_tup_two[0]*100 + num_tup_two[1]*10+num_tup_two[2], num_tup_three[0]*100 + num_tup_three[1]*10+num_tup_three[2])
		self.data_map[p.SCORE_COLOR] = color
		print("SCORE_COLOR : ", p.SCORE_COLOR)
		return p

	@_('SCREEN_COLOR ASSIGN COLOR')
	def color_assign(self,p):
		# self.data_map[p.COLOR_VAR] = p.COLOR
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
		self.data_map[p.SCREEN_COLOR] = color
		print("SCREEN_COLOR : ", p.SCREEN_COLOR)
		return p

	@_('SCREEN_COLOR ASSIGN color_tup')
	def color_tup_assign(self,p):
		color_tuple_str = str(p.color_tup)
		num_tup_one = []
		num_tup_two = []
		num_encountered = 0
		num_tup_three = []
		index = 0
		for ch in color_tuple_str:
			# print(ch)
			if ord('0') <= ord(ch) <= ord('9'):
				num_encountered = num_encountered + 1
				# print("OUTER")
				if index == 0:
					# print("first")
					num_tup_one.append(ord(ch)-ord('0'))
				elif index == 1:
					# print("second")
					num_tup_two.append(ord(ch)-ord('0'))
				elif index == 2:
					# print("third")
					num_tup_three.append(ord(ch)-ord('0'))
				if num_encountered == 3:
					num_encountered = 0
					index = index + 1
		# print(num_tup_one)
		# print(num_tup_two)
		# print(num_tup_three)
		color = (num_tup_one[0]*100 + num_tup_one[1]*10+num_tup_one[2] , num_tup_two[0]*100 + num_tup_two[1]*10+num_tup_two[2], num_tup_three[0]*100 + num_tup_three[1]*10+num_tup_three[2])
		self.data_map[p.SCREEN_COLOR] = color
		print("SCORE_COLOR : ", p.SCREEN_COLOR)
		return p

	@_('BOUNDARY_COLOR ASSIGN COLOR')
	def color_assign(self,p):
		# self.data_map[p.COLOR_VAR] = p.COLOR
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
		self.data_map[p.BOUNDARY_COLOR] = color
		print("BOUNDARY_COLOR : ", p.BOUNDARY_COLOR)
		return p

	@_('BOUNDARY_COLOR ASSIGN color_tup')
	def color_tup_assign(self,p):
		color_tuple_str = str(p.color_tup)
		num_tup_one = []
		num_tup_two = []
		num_encountered = 0
		num_tup_three = []
		index = 0
		for ch in color_tuple_str:
			# print(ch)
			if ord('0') <= ord(ch) <= ord('9'):
				num_encountered = num_encountered + 1
				# print("OUTER")
				if index == 0:
					# print("first")
					num_tup_one.append(ord(ch)-ord('0'))
				elif index == 1:
					# print("second")
					num_tup_two.append(ord(ch)-ord('0'))
				elif index == 2:
					# print("third")
					num_tup_three.append(ord(ch)-ord('0'))
				if num_encountered == 3:
					num_encountered = 0
					index = index + 1
		color = (num_tup_one[0]*100 + num_tup_one[1]*10+num_tup_one[2] , num_tup_two[0]*100 + num_tup_two[1]*10+num_tup_two[2], num_tup_three[0]*100 + num_tup_three[1]*10+num_tup_three[2])
		self.data_map[p.BOUNDARY_COLOR] = color
		print("BOUNDARY_COLOR : ", p.BOUNDARY_COLOR)
		return p

	@_('BORDER_COLOR ASSIGN COLOR')
	def color_assign(self,p):
		# self.data_map[p.COLOR_VAR] = p.COLOR
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
		self.data_map[p.BORDER_COLOR] = color
		print("BORDER_COLOR : ", p.BORDER_COLOR)
		return p

	@_('BORDER_COLOR ASSIGN color_tup')
	def color_tup_assign(self,p):
		color_tuple_str = str(p.color_tup)
		num_tup_one = []
		num_tup_two = []
		num_encountered = 0
		num_tup_three = []
		index = 0
		for ch in color_tuple_str:
			# print(ch)
			if ord('0') <= ord(ch) <= ord('9'):
				num_encountered = num_encountered + 1
				# print("OUTER")
				if index == 0:
					# print("first")
					num_tup_one.append(ord(ch)-ord('0'))
				elif index == 1:
					# print("second")
					num_tup_two.append(ord(ch)-ord('0'))
				elif index == 2:
					# print("third")
					num_tup_three.append(ord(ch)-ord('0'))
				if num_encountered == 3:
					num_encountered = 0
					index = index + 1
		color = (num_tup_one[0]*100 + num_tup_one[1]*10+num_tup_one[2] , num_tup_two[0]*100 + num_tup_two[1]*10+num_tup_two[2], num_tup_three[0]*100 + num_tup_three[1]*10+num_tup_three[2])
		self.data_map[p.BORDER_COLOR] = color
		print("BORDER_COLOR : ", p.BORDER_COLOR)
		return p

	@_('L_PAREN NUMBER COMMA NUMBER COMMA NUMBER R_PAREN')
	def color_tup(self,p):
		return p
	
	##########################################################################################
	############################### COLOUR ASSIGNS ###########################################
	##########################################################################################





	
	#######################################################################################
	############################### NUM ASSIGNS ###########################################
	#######################################################################################

	@_('POINTS ASSIGN num_arr')
	def num_arr_assign(self,p):
		return p

	@_('L_SQUARE num_list R_SQUARE')
	def num_arr(self,p):
		return p

	@_('num_list COMMA NUMBER')
	def num_list(self,p):
		self.points.append(int(p.NUMBER))
		return p

	@_('NUMBER')
	def num_list(self,p):
		self.points.append(int(p.NUMBER))
		return p


	@_('block_size_assign')
	def num_assign(self,p):
		return p

	@_('border_assign')
	def num_assign(self,p):
		return p

	@_('row_assign')
	def num_assign(self,p):
		return p

	@_('col_assign')
	def num_assign(self,p):
		return p

	@_('font_size_assign')
	def num_assign(self,p):
		return p

	@_('tick_int_assign')
	def num_assign(self,p):
		return p

	@_('delay_assign')
	def num_assign(self,p):
		return p

	@_('repeat_assign')
	def num_assign(self,p):
		return p

	@_('speed_assign')
	def num_assign(self,p):
		return p

	@_('border_thick_assign')
	def num_assign(self,p):
		return p

	@_('score_assign')
	def num_assign(self,p):
		return p

	@_('screen_height_assign')
	def num_assign(self,p):
		return p

	@_('screen_width_assign')
	def num_assign(self,p):
		return p

	@_('screen_size_assign')
	def num_assign(self,p):
		return p
	
	@_('BLOCK_SIZE ASSIGN NUMBER')
	def block_size_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)

	@_('BORDER ASSIGN NUMBER')
	def border_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)

	@_('ROWS ASSIGN NUMBER')
	def row_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)
	
	@_('COLS ASSIGN NUMBER')
	def col_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)

	@_('FONT_SIZE ASSIGN NUMBER')
	def font_size_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)
	
	@_('TICK_INTERVAL ASSIGN NUMBER')
	def tick_int_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)

	@_('DELAY ASSIGN NUMBER')
	def delay_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)

	@_('REPEAT ASSIGN NUMBER')
	def repeat_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)

	@_('SPEED ASSIGN NUMBER')
	def speed_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)

	@_('SPEED ASSIGN DECIMAL_NUMBER')
	def speed_assign(self,p):
		self.data_map[p[0]] = p.DECIMAL_NUMBER
		print(p[0]," = ",p.DECIMAL_NUMBER)


	@_('BORDER_THICKNESS ASSIGN NUMBER')
	def border_thick_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)

	@_('SCORE ASSIGN NUMBER')
	def score_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)

	@_('SCREEN_HEIGHT ASSIGN NUMBER')
	def screen_height_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)

	@_('SCREEN_WIDTH ASSIGN NUMBER')
	def screen_width_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)

	@_('SCREEN_SIZE ASSIGN NUMBER')
	def screen_size_assign(self,p):
		self.data_map[p[0]] = p.NUMBER
		print(p[0]," = ",p.NUMBER)
	
	#######################################################################################
	############################### NUM ASSIGNS ###########################################
	#######################################################################################



	

	def compile(self):
		lexer = tetLexer()
		parser = tetParser()

		with open('temp.ranks', 'r') as fileh:
			text = fileh.read()
			# print("This works!")
			result = parser.parse(lexer.tokenize(text))
			# print(result)
			# print(parser.data_map)

# if __name__ == '__main__':
# 	lexer = tetLexer()
# 	parser = tetParser()
 
# 	# while True:
	
 
# 	with open('temp.ranks', 'r') as fileh:
# 		text = fileh.read()
# 		print("This works!")
# 		result = parser.parse(lexer.tokenize(text))
# 		# print(result)
# 		print(parser.data_map)
				