#ifndef SURVEY_ENGINE_HPP
#define SURVEY_ENGINE_HPP

#include "Survey.hpp"
#include "Response.hpp"
#include "User.hpp"
#include "Record.hpp"
#include <vector>
#include <fstream>

class Survey_Engine {
    private:
        vector<Survey> surveys;
        vector<Response> responses;
        vector<User> users;
        User* currentUser = nullptr;
    
    public:
        Survey_Engine();
        void loginUser();
        void saveData();
        void createSurvey();    
        void takeSurvey();    
        void viewResults() const;
        void start();
    
};
#endif