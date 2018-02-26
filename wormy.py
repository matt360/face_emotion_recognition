# Wormy (a Nibbles clone)
# By Al Sweigart al@inventwithpython.com
# http://inventwithpython.com/pygame
# Released under a "Simplified BSD" license

#KRT 14/06/2012 modified Start Screen and Game Over screen to cope with mouse events
#KRT 14/06/2012 Added a non-busy wait to Game Over screen to reduce processor loading from near 100%

#
# Modified by Grant Clarke
# g.clarke@abertay.ac.uk
#
#

import random, pygame, sys
from pygame.locals import *

FPS = 15
WINDOWWIDTH = 640
WINDOWHEIGHT = 480
CELLSIZE = 20
assert WINDOWWIDTH % CELLSIZE == 0, "Window width must be a multiple of cell size."
assert WINDOWHEIGHT % CELLSIZE == 0, "Window height must be a multiple of cell size."
CELLWIDTH = int(WINDOWWIDTH / CELLSIZE)
CELLHEIGHT = int(WINDOWHEIGHT / CELLSIZE)

#             R    G    B
WHITE     = (255, 255, 255)
BLACK     = (  0,   0,   0)
RED       = (255,   0,   0)
GREEN     = (  0, 255,   0)
DARKGREEN = (  0, 155,   0)
DARKGRAY  = ( 40,  40,  40)
BGCOLOR = BLACK

UP = 'up'
DOWN = 'down'
LEFT = 'left'
RIGHT = 'right'

HEAD = 0 # syntactic sugar: index of the worm's head

#
# GLOBAL VARIABLES used by multiple functions
#
# Set a random start point.
gStartx = random.randint(5, CELLWIDTH - 6)
gStarty = random.randint(5, CELLHEIGHT - 6)
gWormCoords = [{'x': gStartx,     'y': gStarty},
              {'x': gStartx - 1, 'y': gStarty},
              {'x': gStartx - 2, 'y': gStarty}]
gDirection = RIGHT

gApple = {'x': 0, 'y': 0}

#
#
#
def main():
    init()
    showStartScreen()
    while True:
        runGame()
        showGameOverScreen()

def init():
    global FPSCLOCK, DISPLAYSURF, BASICFONT

    pygame.init()
    FPSCLOCK = pygame.time.Clock()
    DISPLAYSURF = pygame.display.set_mode((WINDOWWIDTH, WINDOWHEIGHT))
    BASICFONT = pygame.font.Font('freesansbold.ttf', 18)
    pygame.display.set_caption('Wormy')
    
def runGame():
    game_init()    
    while True: # main game loop
        game_over = game_update()
        game_render()
        if game_over == True:
            return # game over, stop running the game


def game_init():
    global gWormCoords, gDirection, gApple

    # Set a random start point.
    gStartx = random.randint(5, CELLWIDTH - 6)
    gStarty = random.randint(5, CELLHEIGHT - 6)
    gWormCoords = [{'x': gStartx,     'y': gStarty},
                  {'x': gStartx - 1, 'y': gStarty},
                  {'x': gStartx - 2, 'y': gStarty}]
    gDirection = RIGHT
        
    # Start the gApple in a random place.
    gApple = getRandomLocation();


def game_update():
    global gWormCoords, gDirection, gApple

    for event in pygame.event.get(): # event handling loop
        if event.type == QUIT:
            terminate()
        elif event.type == KEYDOWN:
            if (event.key == K_LEFT or event.key == K_a) and gDirection != RIGHT:
                gDirection = LEFT
            elif (event.key == K_RIGHT or event.key == K_d) and gDirection != LEFT:
                gDirection = RIGHT
            elif (event.key == K_UP or event.key == K_w) and gDirection != DOWN:
                gDirection = UP
            elif (event.key == K_DOWN or event.key == K_s) and gDirection != UP:
                gDirection = DOWN
            elif event.key == K_ESCAPE:
                terminate()

    # check if the worm has hit itself or the edge
    if gWormCoords[HEAD]['x'] == -1 or gWormCoords[HEAD]['x'] == CELLWIDTH or gWormCoords[HEAD]['y'] == -1 or gWormCoords[HEAD]['y'] == CELLHEIGHT:
        return True # game over, return True
    for wormBody in gWormCoords[1:]:
        if wormBody['x'] == gWormCoords[HEAD]['x'] and wormBody['y'] == gWormCoords[HEAD]['y']:
            return True # game over, return True

    # check if worm has eaten an apply
    if gWormCoords[HEAD]['x'] == gApple['x'] and gWormCoords[HEAD]['y'] == gApple['y']:
        # don't remove worm's tail segment
        gApple = getRandomLocation() # set a new gApple somewhere
    else:
        del gWormCoords[-1] # remove worm's tail segment

    # move the worm by adding a segment in the gDirection it is moving
    if gDirection == UP:
        newHead = {'x': gWormCoords[HEAD]['x'], 'y': gWormCoords[HEAD]['y'] - 1}
    elif gDirection == DOWN:
        newHead = {'x': gWormCoords[HEAD]['x'], 'y': gWormCoords[HEAD]['y'] + 1}
    elif gDirection == LEFT:
        newHead = {'x': gWormCoords[HEAD]['x'] - 1, 'y': gWormCoords[HEAD]['y']}
    elif gDirection == RIGHT:
        newHead = {'x': gWormCoords[HEAD]['x'] + 1, 'y': gWormCoords[HEAD]['y']}
    gWormCoords.insert(0, newHead)
    # game is not over, return False
    return False

def game_render():
    DISPLAYSURF.fill(BGCOLOR)
    drawGrid()
    drawWorm(gWormCoords)
    drawApple(gApple)
    drawScore(len(gWormCoords) - 3)
    pygame.display.update()
    FPSCLOCK.tick(FPS)

def drawPressKeyMsg():
    pressKeySurf = BASICFONT.render('Press a key to play.', True, DARKGRAY)
    pressKeyRect = pressKeySurf.get_rect()
    pressKeyRect.topleft = (WINDOWWIDTH - 200, WINDOWHEIGHT - 30)
    DISPLAYSURF.blit(pressKeySurf, pressKeyRect)

# KRT 14/06/2012 rewrite event detection to deal with mouse use
def checkForKeyPress():
    for event in pygame.event.get():
        if event.type == QUIT:      #event is quit 
            terminate()
        elif event.type == KEYDOWN:
            if event.key == K_ESCAPE:   #event is escape key
                terminate()
            else:
                return event.key   #key found return with it
    # no quit or key events in queue so return None    
    return None

    
def showStartScreen():
    titleFont = pygame.font.Font('freesansbold.ttf', 100)
    titleSurf1 = titleFont.render('Wormy!', True, WHITE, DARKGREEN)
    titleSurf2 = titleFont.render('Wormy!', True, GREEN)

    degrees1 = 0
    degrees2 = 0
    
#KRT 14/06/2012 rewrite event detection to deal with mouse use
    pygame.event.get()  #clear out event queue
    
    while True:
        DISPLAYSURF.fill(BGCOLOR)
        rotatedSurf1 = pygame.transform.rotate(titleSurf1, degrees1)
        rotatedRect1 = rotatedSurf1.get_rect()
        rotatedRect1.center = (WINDOWWIDTH / 2, WINDOWHEIGHT / 2)
        DISPLAYSURF.blit(rotatedSurf1, rotatedRect1)

        rotatedSurf2 = pygame.transform.rotate(titleSurf2, degrees2)
        rotatedRect2 = rotatedSurf2.get_rect()
        rotatedRect2.center = (WINDOWWIDTH / 2, WINDOWHEIGHT / 2)
        DISPLAYSURF.blit(rotatedSurf2, rotatedRect2)

        drawPressKeyMsg()
#KRT 14/06/2012 rewrite event detection to deal with mouse use
        if checkForKeyPress():
            return
        pygame.display.update()
        FPSCLOCK.tick(FPS)
        degrees1 += 3 # rotate by 3 degrees each frame
        degrees2 += 7 # rotate by 7 degrees each frame


def terminate():
    pygame.quit()
    sys.exit()


def getRandomLocation():
    return {'x': random.randint(0, CELLWIDTH - 1), 'y': random.randint(0, CELLHEIGHT - 1)}


def showGameOverScreen():
    gameOverFont = pygame.font.Font('freesansbold.ttf', 150)
    gameSurf = gameOverFont.render('Game', True, WHITE)
    overSurf = gameOverFont.render('Over', True, WHITE)
    gameRect = gameSurf.get_rect()
    overRect = overSurf.get_rect()
    gameRect.midtop = (WINDOWWIDTH / 2, 10)
    overRect.midtop = (WINDOWWIDTH / 2, gameRect.height + 10 + 25)

    DISPLAYSURF.blit(gameSurf, gameRect)
    DISPLAYSURF.blit(overSurf, overRect)
    drawPressKeyMsg()
    pygame.display.update()
    pygame.time.wait(500)
#KRT 14/06/2012 rewrite event detection to deal with mouse use
    pygame.event.get()  #clear out event queue 
    while True:
        if checkForKeyPress():
            return
#KRT 12/06/2012 reduce processor loading in gameover screen.
        pygame.time.wait(100)

def drawScore(score):
    scoreSurf = BASICFONT.render('Score: %s' % (score), True, WHITE)
    scoreRect = scoreSurf.get_rect()
    scoreRect.topleft = (WINDOWWIDTH - 120, 10)
    DISPLAYSURF.blit(scoreSurf, scoreRect)


def drawWorm(gWormCoords):
    for coord in gWormCoords:
        x = coord['x'] * CELLSIZE
        y = coord['y'] * CELLSIZE
        wormSegmentRect = pygame.Rect(x, y, CELLSIZE, CELLSIZE)
        pygame.draw.rect(DISPLAYSURF, DARKGREEN, wormSegmentRect)
        wormInnerSegmentRect = pygame.Rect(x + 4, y + 4, CELLSIZE - 8, CELLSIZE - 8)
        pygame.draw.rect(DISPLAYSURF, GREEN, wormInnerSegmentRect)


def drawApple(coord):
    x = coord['x'] * CELLSIZE
    y = coord['y'] * CELLSIZE
    appleRect = pygame.Rect(x, y, CELLSIZE, CELLSIZE)
    pygame.draw.rect(DISPLAYSURF, RED, appleRect)


def drawGrid():
    for x in range(0, WINDOWWIDTH, CELLSIZE): # draw vertical lines
        pygame.draw.line(DISPLAYSURF, DARKGRAY, (x, 0), (x, WINDOWHEIGHT))
    for y in range(0, WINDOWHEIGHT, CELLSIZE): # draw horizontal lines
        pygame.draw.line(DISPLAYSURF, DARKGRAY, (0, y), (WINDOWWIDTH, y))


if __name__ == '__main__':
    main()
