#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <vector>
#include <string>
using namespace std;

class Question {
    private:
        string text;            //Text of the question
        vector<string> choices; //Contains the choices (responses) of a question
        bool isMultipleChoice;  //Indicates if a question is multiple choice
    
    public:
        //Constructor
        Question(string, bool); 
        
        //Getters
        bool getIsMultipleChoice() const;    
        vector<string> getChoices() const;    
        string getText() const;   
        string getChoiceText(int) const;

        void addChoice(string);    
        void display() const; 
};
#endif