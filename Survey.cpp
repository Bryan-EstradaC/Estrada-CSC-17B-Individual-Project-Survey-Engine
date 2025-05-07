#include "Survey.hpp"
#include <iostream>
using namespace std;

/**
* @brief Constructs a new Survey.
* @param title Title of the survey.
*/
Survey::Survey(string title) {
    this->title = title;
}

/**
* @brief Add a new question to the survey.
* @param q A Question object to be pushed to a container of Question objects.
*/
void Survey::addQuestion(Question q) {
    questions.push_back(q);
}

/**
* @brief Displays the title of the survey and its questions.
*/
void Survey::display() const {
    cout << "Survey: " << title << "\n\n";
    for (int i = 0; i < questions.size(); i++) {
        cout << "Q" << i + 1 << ": ";
        questions[i].display();
        cout << endl;
    }
}

/**
* @brief Returns an specific question.
* @param index Question's index in a vector.
*/
Question Survey::getQuestion(int index) const {
    if (index >= 0 && index < questions.size()) {
        return questions[index];
    } else {
        throw out_of_range("Invalid question index");
    }
}


/**
* @brief Returns a vector of Question.
*/
vector<Question> Survey::getAllQuestions() const {
    return questions;
}

/**
* @brief Returns a survey's title.
*/
string Survey::getTitle() const {
    return title;
}