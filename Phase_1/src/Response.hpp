#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "Survey.hpp"
#include <map>

class Response{
    private:
        string userName;            //Responsed by this user            
        int surveyIndex;            //Which survey this response belongs to
        map<int, string> answers;   //Contains the choice of the user and text of the choice

public:
    //Constructor
    Response(string, int);

    //Getters
    string getUser() const;
    int getSurveyIndex() const;
    map<int, string> getAnswers() const;

    void recordAnswer(int, string);
    void display(const Survey&) const;    
};
#endif