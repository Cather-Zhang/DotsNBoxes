Hello CS 4341 A23!

Below is information about using the Referee we are providing for project 1.
Description adapted from Will Babincsak README UTTT
_________________________________________________________________________________

# Dependencies and Python Version

This is the referee program for the Dots and Boxes AI for Project 1. 
The details of how your programs need to communicate with the referee are on Canvas.

The referee has two dependencies, `numpy` and `pygame`. Please install these with 
`pip install numpy` and `python3 -m pip install -U pygame --user`. 
If there are issues with installing, please refer to
the official documentation for the libraries.

We can guarantee this program will work for Python 3.9 and up. 
Please check that are you using a valid version of python.
You can check your version with `python --version` and/or `python3 --version`.
You may need to use `python` or `python3` or even `python3.9` 
to properly run the program depending on how your system handled Python and if you are using an IDE.
We will use `python` in the README for simplicity.

___________________________________________________________________

# Running the Referee and Playing the Game

Once python and dependencies are sorted, you can run the referee with 

`python referee.py <Player 1 name> <Player 2 name> --time_limit <time limit>`

The Player 1 and 2 names are *single word names* for each of the agents.
`--time_limit` is an optional argument that allows you to specify the time limit to play (in seconds).
It defaults to 10 seconds. We will use 10 seconds in the competition. 
This argument option is provide to allow easier debugging.

The referee will create the files that it maintains in the same directory that the referee.py file is in.

If you would like to just play the game, run

`python game.py <Player 1 name> <Player 2 name>`

and then you can play using the UI.

You should not need to modify any of the code provided to you. 
You are to write your owm program that can communicate with this referee.

_________________________________________________________________________

# Bugs

If you for any reason suspect that the referee is not behaving as described in the assignment on Canvas, please let us know in the `project-1-referee-bugs` channel in Slack. 
_________________________________________________________________________

That is all! Have fun playing Dots and Boxes.

-Adeline Evans and Fabrizio Filizzola
