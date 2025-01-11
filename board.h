#pragma once

#include <utility>
#include <vector>

#include "cell-inl.h"

class Board {
    public:
        
        //constructor
        Board(int s, int b);
        //destructor
        ~Board() {}

        // display the board
        void printBoard();

        // play call
        void play();

        // recursive revealing of zero and adjacent squares
        void revealZero(std::pair<int, int> coordinates);

        // end game
        bool gameOver();
    private:
        // assign value of each cell
        void calculateScore();

        // get the status of neighboring squares
        int getNeighbors(int x, int y);

        // get user input for play
        std::pair<int, int> getUserInput();

        int size;
        int bombs;
        int toWin;
        bool isOver;
        
        std::vector<std::vector<Cell>> grid;
};

#include "board-inl.h"