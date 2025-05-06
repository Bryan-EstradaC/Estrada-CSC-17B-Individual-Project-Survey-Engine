#ifndef RECORD_HPP
#define RECORD_HPP
#include "User.hpp"
#include "Response.hpp"
#include "Survey.hpp"
#include <list>
#include <fstream>

class Record {
    public:
    static void saveUsers(const vector<User>&, const string&);    
    static vector<User> loadUsers(const string&);
    
    static void saveSurveys(const vector<Survey>&, const string&);
    static vector<Survey> loadSurveys(const string&);

    static void saveResponses(const vector<Response>&, const string&);
    static vector<Response> loadResponses(const string&);
};
#endif