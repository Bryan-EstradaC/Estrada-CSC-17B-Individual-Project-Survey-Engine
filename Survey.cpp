#include "Survey.hpp"
#include <iostream>
using namespace std;

Survey::Survey(string title) {
    this->title = title;
}

void Survey::addQuestion(Question q) {
    questions.push_back(q);
}

void Survey::display() const {
    cout << "Survey: " << title << "\n\n";
    for (int i = 0; i < questions.size(); i++) {
        cout << "Q" << i + 1 << ": ";
        questions[i].display();
        cout << endl;
    }
}

Question Survey::getQuestion(int index) const {
    if (index >= 0 && index < questions.size()) {
        return questions[index];
    } else {
        throw out_of_range("Invalid question index");
    }
}

vector<Question> Survey::getAllQuestions() const {
    return questions;
}

string Survey::getTitle() const {
    return title;
}