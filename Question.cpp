#include "Question.hpp"
#include <iostream>
using namespace std;

/**
* @brief Constructs a new Question.
* @param text The text of the question.
* @param mc True if the question is multiple choice; false otherwise.
*/
Question::Question(string text, bool mc) {
    this->text = text;
    this->isMultipleChoice = mc;
}

/**
* @brief Adds a new choice to a question
* @param choice
*/
void Question::addChoice(string choice) {
    if (isMultipleChoice) {
        choices.push_back(choice);
    }
}

/**
* @brief Displays the question
*/
void Question::display() const {
        cout << text << endl;
        if (isMultipleChoice) {
            for (int i = 0; i < choices.size(); i++) {
                cout << "  " << i + 1 << ". " << choices[i] << endl;
            }
        }
    }

/**
* @brief Returns isMultipleChoice
*/   
bool Question::getIsMultipleChoice() const {
    return isMultipleChoice;
}

/**
* @brief Returns the vector of choices
*/  
vector<string> Question::getChoices() const {
    return choices;
}

/**
* @brief Returns the text of the question
*/  
string Question::getText() const {
    return text;
}

/**
* @brief Returns a specific choice of a question
*/  
string Question::getChoiceText(int choiceNumber) const {
    if (choiceNumber >= 1 && choiceNumber <= choices.size()) {
        return choices[choiceNumber - 1];
    } else {
        return "Invalid choice";
    }
}