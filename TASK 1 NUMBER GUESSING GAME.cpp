#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
using namespace std;
namespace GuessGame {
    // Function to generate a random number within a specified range
    int generateRandomNumber(int min, int max) {
        return rand() % (max - min + 1) + min;
    }

    // Function to display ASCII art
    void displayASCIIArt() {
        cout << R"(
   _____                 _   _                 _ 
  / ____|               | | (_)               | |
 | |  __  ___   ___   __| |_ _ _ __ ___   __ _| |
 | | |_ |/ _ \ / _ \ / _` | | '_ ` _ \ / _` | |
 | |__| | (_) | (_) | (_| | | | | | | | (_| | |
  \_____|\___/ \___/ \__,_|_|_| |_| |_|\__,_|_|
                                               
                                               
)" << std::endl;
    }

    // Function to play the guessing game
    bool playGame(int minRange, int maxRange, int maxAttempts) {
        // Seed the random number generator with the current time
        srand(time(nullptr));

        // Generate a random number within the specified range
        int secretNumber = generateRandomNumber(minRange, maxRange);

        int guess;
        int attempts = 0;

        cout << "I have selected a random number between " << minRange << " and " << maxRange << "." << std::endl;
        cout << "You have " << maxAttempts << " attempts to guess it." << std::endl;

        // Keep looping until the user guesses the correct number or runs out of attempts
        while (attempts < maxAttempts) {
            cout << "Attempt #" << attempts + 1 << ": Enter your guess: ";
            cin >> guess;

            // Check if the guess is within the range
            if (guess < minRange || guess > maxRange) {
                cout << "Invalid guess! Please enter a number between " << minRange << " and " << maxRange << "." << std::endl;
                continue;
            }

            // Check if the guess is correct
            if (guess == secretNumber) {
                cout << "Congratulations! You guessed the correct number in " << attempts + 1 << " attempts." << std::endl;
                return true; // Indicate that the user won
            } else if (guess < secretNumber) {
               cout << "Too low! Try again." << std::endl;
            } else {
                cout << "Too high! Try again." << std::endl;
            }

            // Increment the number of attempts
            attempts++;
        }

        // If the user runs out of attempts
        cout << "Sorry, you have run out of attempts. The correct number was: " << secretNumber << std::endl;
        return false; // Indicate that the user lost
    }

    // Function to ask the user if they want to play again
    bool playAgain() {
        char choice;
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
        return (choice == 'y' || choice == 'Y');
    }
}

int main() {
    using namespace std;

    int minRange = 1;
    int maxRange = 100;
    int maxAttempts = 5;
    int gamesPlayed = 0;
    int gamesWon = 0;

    GuessGame::displayASCIIArt();

    bool play = true;
    while (play) {
        gamesPlayed++;

        if (GuessGame::playGame(minRange, maxRange, maxAttempts)) {
            gamesWon++;
        }

        float winRate = (gamesPlayed == 0) ? 0.0f : static_cast<float>(gamesWon) / gamesPlayed * 100;

        cout << "Statistics: " << endl;
        cout << "Games Played: " << gamesPlayed << endl;
        cout << "Games Won: " << gamesWon << endl;
        cout << "Win Rate: " << winRate << "%" << endl;

        play = GuessGame::playAgain();
    }

    cout << "Thanks for playing! Goodbye!" << endl;

    return 0;
}

