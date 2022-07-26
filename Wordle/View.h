#pragma once

#include <iostream>
#include <vector>

#include "AWView.h"

class View {
public:

    enum class Colour {
        GREEN, YELLOW, GRAY, WHITE, RESET
    };

    struct Letter {
        char letter;
        Colour colour;
    };

    View(std::ostream& stream);

    void reset();

    void startLevel();

    /**
     * @brief Set the Guess object
     *
     * @param guessNumber [0, 5]
     * @param word The letters
     */
    void setGuess(int guessNumber, std::vector<Letter>& word);

    void setMessage(std::string msg);
    void askForNextWord();
    void askToPlayAgain(bool won);

private:

    void goToStartOfCurLine();


    void clearScreen();
    void goToPos(int r, int c);
    void switchToColour(const Colour& c);

    AWView mAWView;

    std::ostream& mStream;
    Colour mCurColour;
};
