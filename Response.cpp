#include "Response.hpp"
#include <iostream>
using namespace std;

Response::Response(string userName, int surveyIndex) {
    this->userName = userName;
    this->surveyIndex = surveyIndex;
}

string Response::getUser() const{
    return userName;
}

int Response::getSurveyIndex() const {
    return surveyIndex;
}

void Response::recordAnswer(int questionIndex, string answer) {
    answers[questionIndex] = answer;
}

void Response::display(const Survey& survey) const {
    cout << "User: " << userName << "\n";
    for (const auto& pair : answers) {
        int questionIndex = pair.first;
        string userInput = pair.second;

        Question q = survey.getQuestion(questionIndex);
        cout << "Q" << questionIndex + 1 << ": " << q.getText() << "\n";

        if (q.getIsMultipleChoice()) {
            int selected = stoi(userInput); // Convert string to int
            cout << "Answer: " << q.getChoiceText(selected) << "\n";
        } else {
            cout << "Answer: " << userInput << "\n";
        }
        cout << endl;
    }
}
map<int, string> Response::getAnswers() const{
    return answers;
}