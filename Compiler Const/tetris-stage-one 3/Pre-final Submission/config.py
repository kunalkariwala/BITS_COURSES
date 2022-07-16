# import pygame
# pygame.init()
from tetparser import tetParser

class configData():
    configObj = tetParser()
    configObj.compile()
    data = configObj.data_map
    colorsArr = configObj.colors
    pointsArr = configObj.points

    print("Printing from config file")
    print(colorsArr)
    print(data)

    black = (255,255,255) if 'screenColor' not in data.keys() else data['screenColor']
    white = (000,000,000) if 'scoreColor' not in data.keys() else data['scoreColor']
    colors = tuple(colorsArr)


    # Sizes
    blockSize = 30 if 'blockSize' not in data.keys() else int(data['blockSize'])
    border = 1
    rows = 21 if 'rows' not in data.keys() else int(data['rows'])
    cols = 12 if 'cols' not in data.keys() else int(data['cols'])
    screenHeight = rows*blockSize
    screenWidth = cols*blockSize + 200
    screenSize = (screenWidth, screenHeight)
    fontSize = 20 if 'fontSize' not in data.keys() else int(data['fontSize'])
    orderThickness = 2

    # Speed
    tickInterval = 20 if 'tickInterval' not in data.keys() else int(data['tickInterval'])
    delay = 300 if 'delay' not in data.keys() else int(data['delay'])
    repeat = 100 if 'repeat' not in data.keys() else int(data['repeat']) 
    speed = 0.7 if 'speed' not in data.keys() else float(data['speed'])

    # pygame.key.set_repeat(delay, repeat)


    # Miscellaneous
    emptyColor = black
    boundaryColor = grey if 'boundaryColor' not in data.keys() else data['boundaryColor']
    borderColor = black if 'borderColor' not in data.keys() else data['colorBorder']
    borderThickness = 4 if 'borderThickness' not in data.keys() else int(data['thicknessBorder'])
    emptyCell = (emptyColor, 0)
    boundaryCell = (boundaryColor, 0)
    points = pointsArr
    score = 0 if 'score' not in data.keys() else int(data['score'])

    singlePlayer = True if 'singlePlayer' not in data.keys() else data['SINGLE_PLAYER']
