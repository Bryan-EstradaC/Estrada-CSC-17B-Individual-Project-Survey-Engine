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
        vector<Survey> surveys;         //Contains the surveys created by the admin
        vector<Response> responses;     //Contains the responses of the user by specific users
        vector<User> users;             //Contains users registered in the program
        User* currentUser = nullptr;    //Points to the user using in the program
    
    public:
        //Constructor
        Survey_Engine();
        
        void loginUser();
        void saveData();
        void createSurvey();    
        void takeSurvey();    
        void viewResults() const;
        void start();
    
};
#endif