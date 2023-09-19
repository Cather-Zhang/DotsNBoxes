import pygame
import sys

# Define constants
ROWS, COLS = 9, 9
GRID_SIZE = 100
DOT_RADIUS = 10
LINE_WIDTH = 3
LINE_WIDTH_P = 3
WINDOW_WIDTH = COLS * GRID_SIZE
WINDOW_HEIGHT = ROWS * GRID_SIZE

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 255)
ORANGE = (255, 165, 0)  # RGB color values for orange

# Initialize Pygame
pygame.init()
screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
pygame.display.set_caption("Dots and Boxes")


def global_to_xy(row, col):
    x = col * (GRID_SIZE - 3) + 10
    y = row * (GRID_SIZE - 3) + 10
    return x, y


def draw_dots():
    for row in range(ROWS + 1):
        for col in range(COLS + 1):
            pygame.draw.circle(screen, BLACK, global_to_xy(row, col), DOT_RADIUS)


def draw_dashed_line(x1, y1, x2, y2, dash_length=5):
    dx = x2 - x1
    dy = y2 - y1
    distance = max(abs(dx), abs(dy))
    dx = dx / distance
    dy = dy / distance
    for i in range(0, int(distance), dash_length * 2):
        x_start = int(x1 + i * dx)
        y_start = int(y1 + i * dy)
        x_end = int(x1 + (i + dash_length) * dx)
        y_end = int(y1 + (i + dash_length) * dy)
        pygame.draw.line(screen, BLACK, (x_start, y_start), (x_end, y_end), 2)


def draw_lines(edges):
    # draw edges based on backend info
    for edge in edges.keys():
        row1, col1 = edge[0]
        y1, x1 = global_to_xy(col1, row1)
        row2, col2 = edge[1]
        y2, x2 = global_to_xy(col2, row2)
        player = edges[edge]
        if player == 1:
            pygame.draw.line(screen, ORANGE, (x1, y1), (x2, y2), LINE_WIDTH_P)
        elif player == 2:
            pygame.draw.line(screen, BLUE, (x1, y1), (x2, y2), LINE_WIDTH_P)
        else:
            draw_dashed_line(x1, y1, x2, y2)
    pygame.display.flip()


def draw_squares(squares):
    for square in squares:
        x, y = square[0]
        player = square[1]
        if player == 1:
            pygame.draw.rect(screen, ORANGE, (global_to_xy(x, y), [GRID_SIZE - 3, GRID_SIZE - 3]))
        else:
            pygame.draw.rect(screen, BLUE, (global_to_xy(x, y), [GRID_SIZE - 3, GRID_SIZE - 3]))


def draw_game_board(edges, squares):
    screen.fill(WHITE)
    draw_dots()
    draw_lines(edges)
    draw_squares(squares)
    pygame.display.flip()
