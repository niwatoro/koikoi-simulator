#include "game.hpp"
#include <iostream>

void displayMenu() {
    std::cout << "花札 (Hanafuda) - Koi-Koi Game\n";
    std::cout << "============================\n";
    std::cout << "1. Player vs AI\n";
    std::cout << "2. AI vs AI\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose mode (1-3): ";
}

int main() {
    while (true) {
        displayMenu();
        
        int choice;
        std::cin >> choice;
        
        if (choice == 3) {
            std::cout << "Thanks for playing!\n";
            break;
        }
        
        // Get number of rounds
        std::cout << "Enter number of rounds (default is 12): ";
        int rounds;
        std::cin >> rounds;
        if (rounds <= 0) rounds = 12;
        
        Game game(rounds);
        
        switch (choice) {
            case 1:
                game.playerVsAI();
                break;
            case 2:
                game.AIvsAI();
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                continue;
        }
    }
    
    return 0;
}
