#include "board.h"

int main() {
    int size;
    // get the size of the board from the user
    while (true) {
        std::cout << "Enter board size: ";
        std::cin >> size;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n'); 
            std::cout << "Invalid input. Please enter an integer." << std::endl;
        } else if (size < 5 || size > 30) {
            // Check bounds
            std::cout << "Coordinates must be between 5 and 30" << std::endl;
        } else {
            // Valid input
            break;
        }
    }

    // get the number of bombs from the user
    int bombs;
    while (true) {
        std::cout << "Enter bomb amount: ";
        std::cin >> bombs;

        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(1000, '\n');  
            std::cout << "Invalid input. Please enter an integer." << std::endl;
        } else if (bombs < 1 || bombs >= size*size) {
            // Check bounds
            std::cout << "Coordinates must be between 1 and " << (size*size) - 1 << std::endl;
        } else {
            // Valid input
            break;
        }
    }
    
    // create the board
    Board board(size, bombs);
    
    // while the game is not finished, keep playing
    while (!board.gameOver()) {
        board.play();
    }
    
    return 0;
}