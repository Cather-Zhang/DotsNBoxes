#include "Edge.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Edge::Edge(string move) {
    //cout << move << endl;
    stringstream ss(move);
    string name;
    int startx, starty, endx, endy;
    // Extract the name (first word)
    if (ss >> name) {
        // Use the stringstream to extract the integers
        if (ss >> startx && ss.ignore(1) && ss >> starty && ss.ignore() && ss >> endx && ss.ignore(1) && ss >> endy) {
            //cout << "startX: " << startx << endl;
            //cout << "startY: " << starty << endl;
            //cout << "endX: " << endx << endl;
            //cout << "endY: " << endy << endl;
            if (startx == endx) {
                //cout << "startX and endX equals" <<endl;
                this->startX = startx;
                this->type = HORIZONTAL;
                starty < endy ? this->startY = starty : this->startY = endy;
            }
            else if (starty == endy) {
                //cout << "startY and endY equals" <<endl;
                this->startY = starty;
                this->type = VERTICAL;
                startx < endx ? this->startX = startx : this->startX = endx;
            }
            this->playerName = name;
        } else {
            // Parsing integers failed
            cout << "Failed to parse integers from the string." << endl;
        }
    } else {
        // Parsing name failed
        cout << "Failed to parse the name from the string." << endl;
    }

}

bool Edge::isValid(int x1, int y1, int x2, int y2) {
    return x1 >= 0 && x1 <= 9 && x2 >= 0 && x2 <= 9 && y1 >= 0 && y1 <= 9 && y2 >= 0 && y2 <= 9 && (abs(x1 - x2) + abs(y1 - y2) == 1);
}

bool Edge::isVertical() {
    return (this->type == VERTICAL);
}

bool Edge::isHorizontal() {
    return (this->type == HORIZONTAL);
}

void Edge::print() {
    cout << "Start: (" << startX << ", " << startY << "), ";
    if (type == VERTICAL)
    {
        cout << "End: (" << startX + 1 << ", " << startY << "), ";
        cout << "vertical edge, " ;
    }
    else {
        cout << "End: (" << startX << ", " << startY + 1 << "), ";
        cout << "horizontal edge, ";
    }
    cout << "Player: " << playerName << endl;
}

string Edge::toString() {
    string str;
    if (type == VERTICAL) {
        str = "DOTSNBOXES " + to_string(startX) + "," + to_string(startY) + " " + to_string(startX+1) + "," + to_string(startY);
    }
    else {
        str = "DOTSNBOXES " + to_string(startX) + "," + to_string(startY) + " " + to_string(startX) + "," + to_string(startY+1);     
    }
    return str;
}