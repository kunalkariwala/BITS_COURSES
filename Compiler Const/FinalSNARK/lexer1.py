from sly import Lexer
 
class tetLexer(Lexer):

    tokens = {blockSize,border,rows,cols,screenHeight,
    screenWidth,screenSize,fontSize,tickInterval,delay,repeat,speed,
    emptyColor,boundaryColor,borderColor,borderThickness,emptyCell,boundaryCell,
    points,score,singlePlayer}

    blockSize = r'blockSize'
    border = r'border'
    rows = r'rows'
    cols = r'cols'
    screenHeight = r'screenHeight'
    screenWidth = r'screenWidth'
    screenSize = r'screenSize'
    fontSize = r'fontSize'

    tickInterval = r'tickInterval'
    delay = r'delay'
    repeat = r'repeat'
    speed = r'speed'

    emptyColor = r'black'
    boundaryColor = r'boundaryColor'
    borderColor = r'borderColor'
    borderThickness = r'borderThickness'
    emptyCell = r'emptyCell'
    boundaryCell = r'boundaryCell'
    points = r'points'
    score = r'score'
    singlePlayer = r'singlePlayer'

    def count(self):
        for token in self.tokens:
            print((token))


if __name__ == '__main__':
    i = 1

    lexer = tetLexer()
    print(lexer.tokens)