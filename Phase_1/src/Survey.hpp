#ifndef SURVEY_HPP
#define SURVEY_HPP

#include "Question.hpp"


class Survey {
    private:
        string title;               //Title of the survey.
        vector<Question> questions; //Contains the questions of a survey.
    
    public:
        //Constructor 
        Survey(string);      
        
        //Getters
        Question getQuestion(int) const;    
        vector<Question> getAllQuestions() const;    
        string getTitle() const;

        void addQuestion(Question);    
        void display() const;
};
#endif