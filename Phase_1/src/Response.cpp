#include "Response.hpp"
#include <iostream>
using namespace std;

/**
* @brief Constructs a new Response.
* @param userName User who responded an specific survey.
* @param surveyIndex Index of an object Survey in a vector.
*/
Response::Response(string userName, int surveyIndex) {
    this->userName = userName;
    this->surveyIndex = surveyIndex;
}

/**
* @brief Returns userName.
*/
string Response::getUser() const{
    return userName;
}

/**
* @brief Returns surveyIndex.
*/
int Response::getSurveyIndex() const {
    return surveyIndex;
}

/**
* @brief Stores an answer for an specific question.
* @param questionIndex Index of the question in a vector container.
* @param answer Text of the answer.
*/
void Response::recordAnswer(int questionIndex, string answer) {
    answers[questionIndex] = answer;
}

/**
* @brief Displays the answers of an a specific survey by an specific user.
* @param survey A Survey object to get the questions from an specific survey.
*/
void Response::display(const Survey& survey) const {
    cout << "User: " << userName << "\n\n";
    for (const auto& pair : answers) {
        int questionIndex = pair.first; //First map's key
        string userInput = pair.second; //Second map's key

        Question q = survey.getQuestion(questionIndex); //Get each question of the survey
        cout << "Q" << questionIndex + 1 << ": " << q.getText() << "\n";

        if (q.getIsMultipleChoice()) {
            int selected = stoi(userInput); // Convert string to int
            cout << "Answer: " << q.getChoiceText(selected) << "\n";    //Get the user's selected choice
        } else {
            cout << "Answer: " << userInput << "\n";    //Get user's response
        }
    }
    cout << "=================" << endl;
}

/**
* @brief Returns answers.
*/
map<int, string> Response::getAnswers() const{
    return answers;
}