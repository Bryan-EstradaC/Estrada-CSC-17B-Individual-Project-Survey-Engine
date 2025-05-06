#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <vector>
#include <string>
using namespace std;


class Question {
    private:
        string text;
        vector<string> choices;
        bool isMultipleChoice;
    
    public:
        Question(string, bool);    
        void addChoice(string);    
        void display() const;    
        bool getIsMultipleChoice() const;    
        vector<string> getChoices() const;    
        string getText() const;    
        string getChoiceText(int) const;
};
#endif