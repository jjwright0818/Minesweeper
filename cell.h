#pragma once

#include <utility>

class Cell {
    public:
        
        //constructor
        Cell() {}
        Cell(int x, int y);
        //destructor
        ~Cell() {}

        // changes cell values
        void setBomb();
        void setScore(int s);

        // prints score if visible
        void printCell();

        // return bomb values
        int getScore();
        bool getStatus();
        bool isBomb();

        // sets visible
        void changDisplay();

    private:
        bool bomb;
        bool visible;
        int score;
        std::pair<int, int> position;

};

#include "cell-inl.h"