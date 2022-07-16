import pygame
pygame.init()

# Colors
dark = (59,59,59)
grey = (150,150,150)
black = (0, 0, 0)
white = (255, 255, 255)
green = (0, 232, 0)
red = (232, 0, 0)
blue = (0, 0, 172)
orange = (255,120,0)
purple = (155, 0, 232)
yellow = (232, 232, 0)
cyan = (0, 232, 232)
colors = (blue, green, yellow, red, orange, purple, cyan)


# Sizes
blockSize = 30
border = 1
rows = 21
cols = 12
screenHeight = rows*blockSize
screenWidth = cols*blockSize + 200
screenSize = (screenWidth, screenHeight)
fontSize = 20



# Speed
tickInterval = 20 #miliseconds
delay = 300 #miliseconds
repeat = 100 #miliseconds
speed = 0.7 #seconds

pygame.key.set_repeat(delay, repeat)


# Miscellaneous
emptyColor = black
boundaryColor = grey
borderColor = black
borderThickness = 4
emptyCell = (emptyColor, 0)
boundaryCell = (boundaryColor, 0)
points = [0, 40, 100, 300, 1200]
score = 0


singlePlayer = True