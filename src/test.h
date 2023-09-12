#pragma once
#include "GameStatus.h"
#include <windows.h>


class Tests {
public:
	Tests();
	virtual ~Tests();

	bool testPoint();
    bool testEdge();
};
