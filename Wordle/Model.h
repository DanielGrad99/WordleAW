#pragma once

#include <unordered_set>

#include "View.h"
#include "Controller.h"

class Model {
public:
    Model(View& view, Controller& controller);

    void start();

private:

    bool playLevel();

    std::string getRandomWord();
    bool isValidWord(const std::string& word);

    static std::unordered_set<std::string> generateWords(const std::string& filename);

    View& mView;
    Controller& mController;

    std::unordered_set<std::string> mCommonWords;
    std::unordered_set<std::string> mUncommonWords;

};
