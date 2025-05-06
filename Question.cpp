#include "Question.hpp"
#include <iostream>
using namespace std;

Question::Question(string text, bool mc) {
    this->text = text;
    this->isMultipleChoice = mc;
}

void Question::addChoice(string choice) {
    if (isMultipleChoice) {
        choices.push_back(choice);
    }
}

    void Question::display() const {
        cout << text << endl;
        if (isMultipleChoice) {
            for (int i = 0; i < choices.size(); i++) {
                cout << "  " << i + 1 << ". " << choices[i] << endl;
            }
        }
    }

bool Question::getIsMultipleChoice() const {
    return isMultipleChoice;
}

vector<string> Question::getChoices() const {
    return choices;
}

string Question::getText() const {
    return text;
}

string Question::getChoiceText(int choiceNumber) const {
    if (choiceNumber >= 1 && choiceNumber <= choices.size()) {
        return choices[choiceNumber - 1];
    } else {
        return "Invalid choice";
    }
}