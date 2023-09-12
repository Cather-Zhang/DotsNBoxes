#include "test.h"
#include<iostream>

using namespace std;

// cd "c:\Users\Cather Zhang\Desktop\DotsNBoxes\src\" ; if ($?) { g++ test.cpp Point.cpp Edge.cpp -o test } ; if ($?) { .\test }
Tests::Tests() {
	// TODO Auto-generated constructor stub
}

Tests::~Tests() {
	// TODO Auto-generated destructor stub
}

int main() {
    Tests* newTest = new Tests();

    bool pointTest = newTest->testPoint();
    if (pointTest) cout << "point tests passed!" << endl;
    else cout << "point tests did not pass" << endl;

    bool edgeTest = newTest->testEdge();
    if (edgeTest) cout << "edge tests passed!" << endl;
    else cout << "edge tests did not pass" << endl;

    return 0;
}

bool Tests::testPoint() {
    Point* p1 = new Point(1, 2);
    Point* p2 = new Point(1, 3);

    Point* p3 = new Point(0, 2);
    Point* p4 = new Point(2, 4);

    Point* p5 = new Point(-1, 3);
    Point* p6 = new Point(1, 10);

    bool testHorizontal = p1->isHorizontal(p2);
    if (testHorizontal) cout << "Test Point Horizontal passed" << endl;

    bool testVertical = p1->isVertical(p3);
    if (testVertical) cout << "Test Point Vertical passed" << endl;

    bool testPointOnBoard = (!p5->isOnBoard()) && (!p6->isOnBoard());
    if (testPointOnBoard) cout << "Test Point on board passed" << endl;

    return testHorizontal && testVertical && testPointOnBoard;
}

bool Tests::testEdge() {
    Point* p1 = new Point(1, 2);
    Point* p2 = new Point(1, 3);

    Point* p3 = new Point(0, 2);
    Point* p4 = new Point(2, 4);

    Point* p5 = new Point(-1, 3);

    Edge* e1 = new Edge(p1, p2, "team1"); //horizontal
    Edge* e2 = new Edge(p2, p4, "team1"); //invalid
    Edge* e3 = new Edge(p1, p5, "team1"); //invalid
    Edge* e4 = new Edge(p1, p3, "team1"); //vertical

    bool testHorizontal = e1->isHorizontal();
    if (testHorizontal) cout << "Test Edge Horizontal passed" << endl;

    bool testVertical = e4->isVertical();
    if (testVertical) cout << "Test Edge Vertical passed" << endl;

    bool testInvalidEdge = (!e2->isValid()) && (!e3->isValid());
    if (testInvalidEdge) cout << "Test Invalid Edge passed" << endl;

    return testHorizontal && testVertical && testInvalidEdge;
}