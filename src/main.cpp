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
    //bool myTurn = true;

    // Use the constants defined in main.h
    cout << "Welcome to game: " << PROGRAM_NAME << endl;
    cout << "The grid is " << MAX_ROW << " x " << MAX_COL << endl;

    cout << "Constructing a new game" << endl;

/*

    Edge* my1 = new Edge(VERTICAL, 0, 0, MY_TEAM);
    Edge* opp1 = new Edge(HORIZONTAL, 0, 0, "opp");

    Edge* my2 = new Edge(HORIZONTAL, 0, 1, MY_TEAM);
    Edge* opp2 = new Edge(VERTICAL, 0, 1, "opp");

    Board* b = new Board();
    b->put(my1);
    b->put(opp1);
    b->put(my2);
    b->put(opp2);

    GameStatus* gs = new GameStatus(b, MIN);

    Minimax* minimax = new Minimax();

    pair<int, vector<GameStatus*>> paths = minimax->minimaxAlphaBeta(gs, 3, INT_MIN, INT_MAX, true);
    Edge* nextMove = paths.second[1]->previousMove;
    cout << "Best path" << endl;
    nextMove->print();
    cout << nextMove->toString() << endl;
    cout << "final evaluation: " << paths.first << endl;
    
*/

    GameStatus* gs = new GameStatus(MAX);
    Minimax* minimax = new Minimax;
    //ofstream oppGoFile("BotsNDoxes.go");
    //oppGoFile.close();
    //hmod("BotsNDoxes.go", S_IRWXU | S_IRWXG | S_IRWXO);
    string moveFileName = "move_file";
    string goFileName = MY_TEAM".go";
    string winFileName = "end_game";
    string myPassFileName = MY_TEAM".pass";
    //ofstream moveFileOut(moveFileName);
    //moveFileOut.close();
    
    while (1)
    {
        
        // Check if game is ended yet;
        if (filesystem::exists(winFileName))
            break;

        if (filesystem::exists(myPassFileName)) {
            ofstream moveFileOut(moveFileName);
            moveFileOut << MY_TEAM << " 0,0 0,0";
            moveFileOut.close();
            /*
            remove("BotsNDoxes.pass");
            ofstream oppGoFile("opp.go");
            oppGoFile.close();
            chmod("opp.go", S_IRWXU | S_IRWXG | S_IRWXO);
            */
        }
        
        // Check if it is my turn to go
        if (filesystem::exists(goFileName))
        {   
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
                // Update opponent's move
                if (!move.find("0,0 0,0") != string::npos) {
                    //
                    Edge* newMove = new Edge(move);
                    gs->update(newMove);
                    //cout << "opponent's move" << endl;
                    //newMove->print();
                    /*
                    if (gs->update(newMove)) {
                        
                        ofstream myPassFile(MY_TEAM".pass");
                        myPassFile.close();
                        chmod(MY_TEAM".pass", S_IRWXU | S_IRWXG | S_IRWXO);
                        remove(MY_TEAM".go");
                        continue;
                    }
                    */
                }
            }
            

            // Generate move based on opponent's move
            //cout << "Generating move" << endl;
            Edge* nextMove = minimax->getNextMove(gs);
            gs->update(nextMove);
            //nextMove->print();
            /*
            if (gs->update(nextMove)) {
                remove(MY_TEAM".go");
                ofstream myPassFile("opp.pass");
                myPassFile.close();
                chmod("opp.pass", S_IRWXU | S_IRWXG | S_IRWXO);
                continue;
            }
            */
            ofstream moveFileOut(moveFileName);
            moveFileOut << nextMove->toString();
            moveFileOut.close();
            this_thread::sleep_for(std::chrono::milliseconds(100));
            /*
            if (remove("BotsNDoxes.go") != 0) {
                perror("Error removing file");
            }
            ofstream oppGoFile("opp.go");
            oppGoFile.close();
            chmod("opp.go", S_IRWXU | S_IRWXG | S_IRWXO);
            //cout << "Board after my move" << endl;
            //gs->board->printBoard();
            */
        }
        
        /*
        ifstream goOppFile("opp.go");
        if (goOppFile.good()){
            goOppFile.close();
            cout << "Input opponent's move" << endl;
            string move;
            getline(cin, move);
            ofstream moveFileOut(moveFileName);
            moveFileOut << move;
            moveFileOut.close();

            remove("opp.go");
            ofstream myGoFile("BotsNDoxes.go");
            myGoFile.close();
            chmod("BotsNDoxes.go", S_IRWXU | S_IRWXG | S_IRWXO);
        }

        ifstream oppPassFile("opp.pass");
        if (oppPassFile.good()){
            oppPassFile.close();
            cout << "Please skip by tying invalid move" << endl;
            string move;
            getline(cin, move);
            ofstream moveFileOut(moveFileName);
            moveFileOut << move;
            moveFileOut.close();

            remove("opp.pass");
            ofstream myGoFile("BotsNDoxes.go");
            myGoFile.close();
            chmod("BotsNDoxes.go", S_IRWXU | S_IRWXG | S_IRWXO);
        }
        */


    
    }


    return 0;
}

