#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "Survey.hpp"
#include <map>


class Response{
    private:
    string userName;
    int surveyIndex;  // which survey this response belongs to
    map<int, string> answers;

public:
    Response(string, int);
    string getUser() const;
    int getSurveyIndex() const;
    void recordAnswer(int, string);
    void display(const Survey&) const;
    map<int, string> getAnswers() const;
};
#endif