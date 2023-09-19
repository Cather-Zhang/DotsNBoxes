
import numpy as np
import pygame
import core_gameplay as gp
import display as disp
from dotsandboxes import generateEdges
from external_players import external_player

# Each AI function will have its own file to allow for more modular creation
import human


def nums_output(nums, p1_name, p2_name):
    symbols = [p1_name, p2_name]
    s = ''
    i = 0
    j = 1
    p = 0
    while i < 4:
        board = nums[i]
        spot = nums[j]
        s += symbols[p] + " " + str(board) + " " + str(spot) + '\n'
        p += 1
        p %= 2
        i += 1
        j += 1
    return s


class Game:
    def __init__(self, f_p1, f_p2, p1_name=None, p2_name=None, rand_start=False):
        self.names = [gp.PLAYER0_MARKER if p1_name is None else p1_name,
                      gp.PLAYER1_MARKER if p2_name is None else p2_name]
        self.f_p1 = f_p1
        self.f_p2 = f_p2
        self.p1_points = 0
        self.p2_points = 0
        self.board = generateEdges(9, 9)
        self.completed_squares = []
        self.moves = 0
        self.pass_or_go = False
    
        # Allows to easily change players and markers
        self.current_player = 0
        self.markers = [gp.PLAYER0_MARKER, gp.PLAYER1_MARKER]
        self.winner = gp.NO_MARKER

        #  Pygame initialization
        pygame.init()

    def run(self):
        #  Drawing function
        disp.draw_game_board(self.board, self.completed_squares)

        # GAME LOOP
        running = True
        while running:

            if self.winner != gp.NO_MARKER:

                self.end_game()
                continue

            current_marker = self.markers[self.current_player]
            if self.current_player == 0:

                selected_move = self.f_p1(self.board,
                                          self.names[1], self.names[0], self.pass_or_go)

            else:

                selected_move = self.f_p2(self.board,
                                          self.names[0], self.names[1], self.pass_or_go)

            try:

                (r1, c1), (r2, c2) = selected_move
                int(r1)
                int(c1)
                int(r2)
                int(c2)

                move = selected_move

            except TypeError:

                # there was a bad move given
                sig, msg = selected_move
                if sig == gp.BAD_MOVE_I_WIN:
                    self.winner = gp.MARKERS[self.current_player]
                elif sig == gp.BAD_MOVE_I_LOST:
                    self.winner = gp.MARKERS[(self.current_player + 1) % 2]
                elif sig == gp.BAD_MOVE_DRAW:
                    self.winner = gp.DRAW
                self.end_game(reason=msg)
                running = False
                continue
            else:
                selected_move = move

            if not self.pass_or_go:
                self.moves+=1

                points = self.getPoints(move)

                # add points for player
                if self.current_player == 1:
                    self.p1_points += points
                else:
                    self.p2_points += points

                # check if no more moves left (end game)
                    if self.moves > 162:
                        # generate end game flag
                        if self.p1_points > self.p2_points:
                            self.winner = gp.MARKERS[0]
                            # p1 wins
                        elif self.p2_points > self.p1_points:
                            self.winner = gp.MARKERS[1]
                            # p2 wins
                        else:
                            # draw
                            self.winner = gp.DRAW
                    # end the game
                # if points = 0, change turns
                if points == 0:
                    self.pass_or_go = False
                else:
                    self.pass_or_go = True
            else:
                self.pass_or_go = False
            self.current_player = (self.current_player + 1) % 2

            # if points > 0, player gets another turn, but still do pass turn

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                    continue

            #  Drawing function
            disp.draw_game_board(self.board, self.completed_squares)

    def current_player_name(self) -> str:
        return str(self.names[int(self.current_player - 1)])


    def end_game(self, reason=None):

        if self.winner > gp.DRAW:
            print("Player " + str(self.names[int(self.winner - 1)]) + " wins")
            L = str(self.names[int(self.winner - 1)])
            w = str(self.names[(int(self.winner - 1) + 1) % 2])
            if reason is None:
                reason = "The winning player has won 3 local boards in a row on the global board!"
            print("Player " + w + " wins")
            msg = f"END: {w} WINS! {L} LOSES! " + reason
        else:
            msg = "END: Match TIED!"
        eg = open("end_game", "w")
        eg.write(msg)
        print(msg)
        eg.close()
        open("{p}.go".format(p=self.names[0]), "w").close()
        open("{p}.go".format(p=self.names[1]), "w").close()

    def getPoints(self, edge):
        points = 0
        marked = self.board.get(edge)  # asserts orientation will be correct for below computations
        # if edge is in edges and if edge is not marked, then valid move
        if marked is not None and marked == 0:
            self.board[edge] = self.current_player + 1
            r1, c1 = edge[0]
            r2, c2 = edge[1]
            # determine vertical vs horizontal
            # see planning.txt for coordinate modification source
            if r1 == r2:  # horizontal edge
                # square 1 check
                mod1 = ((r1 - 1, c1), (r2 - 1, c2))
                mod2 = ((r1 - 1, c1), (r2, c2 - 1))
                mod3 = ((r1 - 1, c1 + 1), (r2, c2))
                points += self.checkSquareCompleted(mod1, mod2, mod3)

                # square 2 check
                mod1 = ((r1, c1), (r2 + 1, c2 - 1))
                mod2 = ((r1, c1 + 1), (r2 + 1, c2))
                mod3 = ((r1 + 1, c1), (r2 + 1, c2))
                points += self.checkSquareCompleted(mod1, mod2, mod3)

                return points

            if c1 == c2:  # vertical edge
                # square 1 check
                mod1 = ((r1, c1 - 1), (r2 - 1, c2))
                mod2 = ((r1, c1 - 1), (r2, c2 - 1))
                mod3 = ((r1 + 1, c1 - 1), (r2, c2))
                points += self.checkSquareCompleted(mod1, mod2, mod3)

                # square 2 check
                mod1 = ((r1, c1), (r2 - 1, c2 + 1))
                mod2 = ((r1 + 1, c1), (r2, c2 + 1))
                mod3 = ((r1, c1 + 1), (r2, c2 + 1))
                points += self.checkSquareCompleted(mod1, mod2, mod3)

                return points

        # if it makes it outside the above if statements without returning,
        # then it is an invalid move
        return -1

    # takes the 3 associated edges of a valid edge completed, and
    # determines if a square has been completed for a specific orientation
    # returns 1 if square was completed, and 0 if not completed
    # edge 1 should always contain top left coordinate for square completion tracking purposes
    def checkSquareCompleted(self, edge1, edge2, edge3):
        coord, _ = edge1
        edge1 = self.board.get(edge1)
        if edge1 is not None and edge1:
            edge2 = self.board.get(edge2)
            if edge2 is not None and edge2:
                edge3 = self.board.get(edge3)
                if edge3 is not None and edge3:
                    self.completed_squares.append((coord, self.current_player + 1))
                    return 1  # if it makes it here, then all edges are in bounds and have been previously marked
        return 0  # if it makes it here, not all edges were in bound and marked, so no square has been completed

        # check valid move
        # make sure inside dictionary and not marked

if __name__ == "__main__":
    game = Game(human.human_player, human.human_player, p1_name='Player 1', p2_name='Player 2', rand_start=True)
    game.run()
