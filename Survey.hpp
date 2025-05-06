#ifndef SURVEY_HPP
#define SURVEY_HPP

#include "Question.hpp"


class Survey {
    private:
        string title;
        vector<Question> questions;
    
    public:
        Survey(string);    
        void addQuestion(Question);    
        void display() const;    
        Question getQuestion(int) const;    
        vector<Question> getAllQuestions() const;    
        string getTitle() const;
};
#endif