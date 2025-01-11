#pragma once

#include <iostream>
#include <random>
#include <set>
#include "board.h"

Board::Board(int s, int b) : 
    size(s), bombs(b), toWin((size * size) - bombs), isOver(false), grid(s, std::vector<Cell>(s)){
    
    // create a cell at each spot in 2D matrix grid
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            grid[x][y] = Cell(x, y);
        }
    }

    // randomize bomb positions
    std::set<std::pair<int, int>> bombPositions;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);

    // ensure no duplicates
    while (int(bombPositions.size()) < bombs) {
        int x = dis(gen);
        int y = dis(gen);

        bombPositions.insert({x, y});
    }

    // assign bombs
    for (std::pair<int, int> pos : bombPositions) {
        grid[pos.first][pos.second].setBomb();
    }

    calculateScore();
}

void Board::printBoard() {
    // clear board
    std::cout << "\033[2J\033[H" << std::flush;

    std::cout << "   ";
    
    for (int i = 0; i < size; i++) {
        std::cout << " " << i << " ";
    }

    std::cout << std::endl << std::endl;

    int i = 0;
    
    for (std::vector<Cell> row : grid) {
        std::cout << i << "  ";
        
        for (Cell cell : row) {
            cell.printCell();
        }
        std::cout << std::endl;
        i++;
    }
}

void Board::play() {
    printBoard();
    
    // if player has revealed all non bombs, end the game
    if (toWin == 0) {
        isOver = true;
        std::cout << "You Win!" << std::endl;
        return;
    }
    
    std::pair<int, int> coordinates = getUserInput();
    
    // create pointer to cell
    Cell* selected = &grid[coordinates.second][coordinates.first];

    // check if user selected already revealed swaure
    if (!selected->getStatus()) {
        // change visible to true
        selected->changDisplay();

        // check if selected is bomb
        if (selected->isBomb() == true) {
            isOver = true;
            printBoard();
            std::cout << "Game Over" << std::endl;
        }

        // call recursive function
        if (selected->getScore() == 0) revealZero(coordinates);

        toWin--;
    }
}

void Board::revealZero(std::pair<int, int> coordinates) {
    int x = coordinates.first;
    int y = coordinates.second;
    
    // increment over all neighboring cells
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            
            int nx = x + i;
            int ny = y + j;

            if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
                // check if already visible
                if (grid[nx][ny].getStatus() == true) {
                    continue;
                } 
                
                grid[nx][ny].changDisplay();

                // check if we need recursive call
                if (grid[nx][ny].getScore() == 0) {
                    revealZero(std::make_pair(nx , ny));
                }
                toWin--;
            }

        }
    }
}

void Board::calculateScore() {
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            grid[x][y].setScore(getNeighbors(x, y));
        }
    }
}

bool Board::gameOver() {
    return isOver;
}

int Board::getNeighbors(int x, int y) {
    // helper function for calculate score
    int score = 0;
    
    // increment over all neighbors
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            
            int nx = x + i;
            int ny = y + j;

            if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
                if (grid[nx][ny].isBomb()) {
                    score++;
                }
            }

        }
    }

    return score;
}

std::pair<int, int> Board::getUserInput() {
    int x, y;

    while (true) {
        std::cout << "Enter coordinates (x y): ";
        std::cin >> x >> y;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter integers." << std::endl;
        } else if (x < 0 || x >= size || y < 0 || y >= size) {
            std::cout << "Coordinates must be between 0 and " << size - 1 << std::endl;
        } else {
            break;
        }
    }

    return std::make_pair(x, y);
}
