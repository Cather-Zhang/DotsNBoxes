"""
This file comprises a portion of the source code of the Dots and Boxes referee implementation for the WPI course 'CS 4341:
Introduction to Artificial Intelligence' running A term of the 2023-2024 academic year. Adapted from the Othello
referee code written by Dyllan Cole <dcole@wpi.edu>

File:   external_players.py
Author: Adeline Evans <amevans@wpi.edu> Fabrizio Filizzola <jffilizzolaortiz@wpi.edu>
Date:   9 September 2023
"""

import os
import re
import time
from functools import partial
from os import listdir
from os.path import isfile, join

import pygame

from dotsandboxes import getPoints

from core_gameplay import BAD_MOVE_I_WIN, BAD_MOVE_I_LOST, BAD_MOVE_DRAW, local_to_global


def get_competitors(p1_name, p2_name, time_limit):

    return (partial(external_player, time_limit=time_limit),
            partial(external_player, time_limit=time_limit))


def external_player(board, name, opponent_name, pass_or_go=False, time_limit=10):
    # Remove old go file if there is one
    if pass_or_go:
        # do pass stuff
        old = "{p}.go".format(p=opponent_name)
        if os.path.exists(old):
            os.remove(old)
        old = "{p}.pass".format(p=opponent_name)
        if os.path.exists(old):
            os.remove(old)

        # Get last modified time of move file and signal next player to go
        mtime = os.path.getmtime("move_file")
        open("{p}.pass".format(p=name), "w").close()
    else:

        old = "{p}.go".format(p=opponent_name)
        if os.path.exists(old):
            os.remove(old)
        old = "{p}.pass".format(p=opponent_name)
        if os.path.exists(old):
            os.remove(old)

        # Get last modified time of move file and signal next player to go
        mtime = os.path.getmtime("move_file")
        open("{p}.go".format(p=name), "w").close()

    # Check if move_file has been modified every 50 milliseconds
    modified = False

    st = time.time()
    check_incr = 0.05
    check_time = st + 0.05
    while time.time() < st + time_limit:
        if time.time() > check_time:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    return BAD_MOVE_DRAW, "Game manually terminated!"
            if os.path.getmtime("move_file") > mtime:
                modified = True
                break
            check_time += check_incr

    if modified:
        with open("move_file", "r") as fp:
            # Get last non-empty line from file
            line = ""
            for next_line in fp.readlines():
                if next_line.isspace():
                    break
                else:
                    line = next_line

            # Tokenize move

            try:
                tokens = line.split()
                group_name = tokens[0]
                coord1 = tokens[1].split(",")
                r1 = int(coord1[0])
                c1 = int(coord1[1])
                coord2 = tokens[2].split(",")
                r2 = int(coord2[0])
                c2 = int(coord2[1])
            except:
                return BAD_MOVE_I_LOST, f'Invalid move!'


            # Verify that move is from expected player
            if group_name != name:
                return BAD_MOVE_I_WIN, 'Out-of-order move!'

            if pass_or_go:
                if r1 != 0 or c1 != 0 or r2 != 0 or c2 != 0:
                    return BAD_MOVE_I_LOST, f'Invalid move!'
            else:
                # Check if move is valid

                # make sure coords are in correct order, force correct if not
                if r1 > r2 or c1 > c2:
                    r3 = r1
                    c3 = c1
                    r1 = r2
                    c1 = c2
                    r2 = r3
                    c2 = c3

                marked = board.get(((r1, c1), (r2, c2)))

                if marked != 0:
                    return BAD_MOVE_I_LOST, f'Invalid move!'

    else:
        # Player didn't move in time!
        return BAD_MOVE_I_LOST, f'Time out!'

    return ((r1, c1), (r2, c2))







