#pragma once


//Core
#include<algorithm>
#include<deque>
#include<iostream>
#include<map>
#include<memory>
#include<set>
#include<thread>
#include<utility>
#include<vector>
#include<list>
#include<stack>
#include<string>
#include<fstream>
#include<sstream>
#include<cmath>

//SFML
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"


enum class gameState { 
    PLAYING = 0, 
    LOST, 
    WON, 
    PAUSED, 
    QUIT,
    RESTART 
};

enum BrickT {
	SOFT = 'S',
	MEDUIM = 'M',
	HARD = 'H',
	INF = 'I',
	UNDEF = 'U'
};

class brickTypeClass {
public:
    const static char SOFT = 'S';
    const static char MEDUIM = 'M';
    const static char HARD = 'H';
    const static char INF = 'I';
    const static char UNDEF = 'U';

    static int getIndex(char e) {
        switch (e)
        {
        case SOFT:
            return 0;
        case MEDUIM:
            return 1;
        case HARD:
            return 2;
        case INF:
            return 3;
        default:
            return 4;
        }
    }

    static char getTypeFromIndex(int e)
    {
        switch (e)
        {
        case 0:
            return SOFT;
        case 1:
            return MEDUIM;
        case 2:
            return HARD;
        case 3:
            return INF;
        default:
            return UNDEF;
        }
    }
};