#pragma once

#include <iostream>
#include "cell.h"

Cell::Cell(int x, int y) : bomb(false), visible(false){
    position = std::make_pair(x, y);
}

void Cell::setBomb() {
    bomb = true;
}

void Cell::setScore(int s) {
    score = s;
}

void Cell::printCell() {
    if (visible == false) {
        std::cout << " - ";
    } else {
        if (bomb == true){
            std::cout << " B ";
        } else {
            std::cout << " " << score << " ";
        }
    }
}

bool Cell::getStatus() {
    return visible;
}

int Cell::getScore() {
    return score;
}

bool Cell::isBomb() {
    return bomb;
}

void Cell::changDisplay() {
    visible = true;
}