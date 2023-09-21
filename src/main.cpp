#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <cstdio>
#include <filesystem>
#include <chrono>
#include <thread>

#include "main.h"
using namespace std;

int main(int argc, char *argv[]) {
    

    // Use the constants defined in main.h
    cout << "Welcome to game: " << PROGRAM_NAME << endl;
    cout << "The grid is " << MAX_ROW << " x " << MAX_COL << endl;
    cout << "My team is: " << MY_TEAM << endl;
    //cout << "Constructing a new game" << endl;

/*


    //Edge* opp1 = new Edge(HORIZONTAL, 0, 0, "opp");
    Edge* my1 = new Edge(VERTICAL, 0, 0, MY_TEAM);

    Edge* opp1 = new Edge(HORIZONTAL, 0, 0, "opp");
    Edge* my2 = new Edge(VERTICAL, 0, 1, MY_TEAM);

    Edge* opp2 = new Edge(HORIZONTAL, 1, 0, "opp");

    Edge* opp3 = new Edge(VERTICAL, 1, 0, "opp");
    Edge* my3 = new Edge(VERTICAL, 2, 1, MY_TEAM);
    Edge* opp4 = new Edge(HORIZONTAL, 3, 0, "opp");
    Edge* my4 = new Edge(VERTICAL, 2, 0, MY_TEAM);
    Edge* opp5 = new Edge(HORIZONTAL, 0, 1, "opp");
    
    
    Edge* my5 = new Edge(VERTICAL, 2, 2, MY_TEAM);

    Edge* my6 = new Edge(VERTICAL, 1, 3, MY_TEAM);

    Edge* opp7 = new Edge(VERTICAL, 2, 3, "opp");
    Edge* my7 = new Edge(HORIZONTAL, 1, 0, MY_TEAM);
    
    
    GameStatus* gs = new GameStatus(MIN);
    
    gs->update(my1);
    gs->update(opp1);
    gs->update(my2);
    gs->update(opp2);
        
    gs->update(opp3);
    gs->update(my3);
    gs->update(opp4);
    gs->update(my4);
    gs->update(opp5);
    
    
    gs->update(my5);
    gs->update(opp6);
    gs->update(my6);
    gs->update(opp7);
    gs->update(my7);
    
    //cout << gs->evaluate() << endl;
    Minimax* minimax = new Minimax();

    pair<int, vector<GameStatus*>> paths = minimax->minimaxAlphaBeta(gs, 1, INT_MIN, INT_MAX, true);
    Edge* nextMove = paths.second[1]->previousMove;
    cout << "Best path" << endl;
    
    for (GameStatus* gs: paths.second) {
        gs->previousMove->print();
    }
    
    cout << nextMove->toString() << endl;
    cout << "final evaluation: " << paths.first << endl;
*/



    Minimax* minimax = new Minimax();
    
    GameStatus* gs = new GameStatus(MAX);
    
    
    string moveFileName = "move_file";
    string goFileName = MY_TEAM".go";
    string winFileName = "end_game";
    string myPassFileName = MY_TEAM".pass";

    
    while (1)
    {
        
        // Check if game is ended yet;
        if (filesystem::exists(winFileName))
            break;

        if (filesystem::exists(myPassFileName)) {
            string move;

            ifstream moveFileIn(moveFileName);
            // read opponent's move first
            if (!moveFileIn) {
                cerr << "Error opening the move file." << endl;
                return 1; // Exit the program with an error code
            }


            while (getline(moveFileIn, move)) {
                // Process each line from the file here
                //cout << move << endl;
            }
            moveFileIn.close();

            // Update opponent's move
            Edge* newMove = new Edge(move);
            gs->update(newMove);
            
            string str = MY_TEAM" " + to_string(0) + "," + to_string(0) + " " + to_string(0) + "," + to_string(0);
            //cout << str << endl;
            //cout << "opening move file" << endl;
            ofstream moveFileOut(moveFileName);
            if (!moveFileOut) {
                cerr << "Error opening and writing the move file 0000." << endl;
                return 1; // Exit the program with an error code
            }
            moveFileOut << str;
            moveFileOut.close();
            //this_thread::sleep_for(std::chrono::seconds(1));
        }
        
        // Check if it is my turn to go
        if (filesystem::exists(goFileName))
        {   
            //cout << "My turn" << endl;
            string move;

            ifstream moveFileIn(moveFileName);
            // read opponent's move first
            if (!moveFileIn) {
                cerr << "Error opening the move file." << endl;
                return 1; // Exit the program with an error code
            }


            while (getline(moveFileIn, move)) {
                // Process each line from the file here
                //cout << move << endl;
            }
            moveFileIn.close();

            if (move == "") {
                gs->team = MIN;
            }
            else {
                if (move.find(MY_TEAM) != string::npos) {
                    continue;
                }
                // Update opponent's move
                if (!move.find("0,0 0,0") != string::npos) {
                    Edge* newMove = new Edge(move);
                    gs->update(newMove);
                    //cout << "opponent's move" << endl;
                    //newMove->print();
                }
            }
            

            // Generate move based on opponent's move
            //cout << "Generating move" << endl;
            Edge* nextMove = minimax->getNextMove(gs);
            gs->update(nextMove);
            //nextMove->print();
            ofstream moveFileOut(moveFileName);
            moveFileOut << nextMove->toString();
            moveFileOut.close();
            //this_thread::sleep_for(std::chrono::seconds(1));
        }
        this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    delete gs;
    delete minimax;


    return 0;
}

