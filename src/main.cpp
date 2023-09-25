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
    Edge* my1 = new Edge(VERTICAL, 3, 0, MY_TEAM);
    Edge* opp1 = new Edge(HORIZONTAL, 3, 0, "opp");

    Edge* my2 = new Edge(HORIZONTAL, 3, 1, MY_TEAM);
    Edge* opp2 = new Edge(VERTICAL, 3, 2, "opp");

    Edge* my3 = new Edge(VERTICAL, 4, 2, MY_TEAM);
    Edge* opp3 = new Edge(VERTICAL, 4, 0, "opp");

    Edge* my4 = new Edge(VERTICAL, 5, 0, MY_TEAM);
    Edge* opp4 = new Edge(VERTICAL, 4, 1, "opp");

    Edge* my5 = new Edge(HORIZONTAL, 6, 0, MY_TEAM);
    Edge* opp5 = new Edge(HORIZONTAL, 6, 1, "opp");

    Edge* my6 = new Edge(VERTICAL, 5, 2, MY_TEAM);
    Edge* opp6 = new Edge(VERTICAL, 3, 1, "opp");
    Edge* my7 = new Edge(HORIZONTAL, 4, 0, MY_TEAM);
    */
    
    
    /*
    GameStatus* gs = new GameStatus(MAX);
    Minimax* minimax = new Minimax();
    
    gs->update(my1);
    gs->update(opp1);
    gs->update(my2);
    gs->update(opp2);
        
    gs->update(my3);
    gs->update(opp3);
    gs->update(my4);
    gs->update(opp4);
    gs->update(my5);
    gs->update(opp5);
    gs->update(my6);
    gs->update(opp6);
    gs->update(my7);
    gs->update(opp7);
    string moveFileName = "move_file_1";
    ifstream moveFileIn(moveFileName);
    string move;
    // read opponent's move first
    if (!moveFileIn) {
        cout << "Can't open opponent's move, trying again" << endl;
        
    }
    //cout << "Pass: Move file ifstream opened" << endl;
    while (getline(moveFileIn, move)) {
        Edge* e = new Edge(move);
        gs->update(e);
    }
    
    int chains = gs->board->totalChainsCreated(gs->previousMove);
    cout << chains << endl;
    
*/
    
    //cout << gs->evaluate() << endl;
    /*
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
    string invalidMove = "0,0 0,0";
    
    while (!gs->isTerminal())
    {
        
        // Game ended
        if (filesystem::exists(winFileName)) {
            cout << "detected end file" << endl;
            break;
        }

        // Opponent scored, I pass
        if (filesystem::exists(myPassFileName)) {
            //cout << "I need to pass" << endl;
            string move;
            ifstream moveFileIn(moveFileName);

            // read opponent's move first
            if (!moveFileIn) {
                //cout << "Pass: Can't open opponent's move, trying again" << endl;
                this_thread::sleep_for(std::chrono::milliseconds(500));
                continue;
            }
            //cout << "Pass: Move file ifstream opened" << endl;
            while (getline(moveFileIn, move)) {
                // Process each line from the file here
                //cout << move << endl;
            }
            //cout << "Pass: Opponent's move read: " << move << endl;
            moveFileIn.close();

            // Update opponent's move
            Edge* newMove = new Edge(move);
            gs->update(newMove);

            string str = MY_TEAM" " + to_string(0) + "," + to_string(0) + " " + to_string(0) + "," + to_string(0);
            //cout << str << endl;
            //cout << "opening move file" << endl;
            ofstream moveFileOut(moveFileName);

            if (!moveFileOut) {
                //cout << "Pass: Can't writing invalid move, trying again" << endl;
                this_thread::sleep_for(std::chrono::milliseconds(500));
                continue;
            }
            //cout << "Pass: Move file ofstream opened" << endl;
            moveFileOut << str;
            moveFileOut.close();
            //cout << "Pass: Invalid move wrote successfully" << endl;
            //this_thread::sleep_for(std::chrono::seconds(1));
        }
        
        // My turn to go
        if (filesystem::exists(goFileName))
        {   
            //cout << "My go file detected" << endl;
            string move;
            ifstream moveFileIn(moveFileName);

            // read opponent's move first
            if (!moveFileIn) {
                //cout << "Go: Can't open opponent's move, trying again" << endl;
                this_thread::sleep_for(std::chrono::milliseconds(500));
                continue;
            }
            //cout << "Go: Move file ifstream opened" << endl;
            while (getline(moveFileIn, move)) {
                // Process each line from the file here
                //cout << move << endl;
            }
            moveFileIn.close();
            //cout << "Go: move read: " << move << endl;

            // Initial game state, I move first (only happen once)
            if (move == "") {
                gs->team = MIN;
            }
            else {
                if (move.find(MY_TEAM) != string::npos) {
                    //cout << "Go: Still my team's move file, try again" << endl;
                    this_thread::sleep_for(std::chrono::milliseconds(500));
                    continue;
                }
                
                // Update opponent's move on the game board 
                if (move.find(invalidMove) == string::npos) {
                    Edge* newMove = new Edge(move);
                    gs->update(newMove);
                    //cout << "Go: opponent's move : ";
                    //newMove->print();
                }
            }
            
            // Generate move based on opponent's move
            //cout << "Generating move" << endl;
            Edge* nextMove = minimax->getNextMove(gs);
            string moveToWrite = nextMove->toString();
            gs->update(nextMove);
            nextMove->print();

            // Write the new move to moveFile
            ofstream moveFileOut(moveFileName);
            if (!moveFileOut) {
                cout << "Go: Can't writing valid move" << endl;
            }
            moveFileOut << moveToWrite;
            moveFileOut.close();
            
        }
        this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    cout << "Game ended!" << endl;
    delete gs;
    delete minimax;


    return 0;
}

