#ifndef USER_HPP
#define USER_HPP

#include <fstream>
#include <string>
#include <vector>
using namespace std;

class User {
    private:
        string username;            //Username
        bool isAdmin;               //Defines if the user is admin or not
        vector<int> takenSurveys;   //Surveys taken by the user
    
    public:
        //Constructors
        User();
        User(string, bool);  

        //Getters
        string getUsername() const;
        bool getIsAdmin() const;
        vector<int> getTakenSurveys() const;   

        //Setter
        void setAdmin(bool);    

        void addTakenSurvey(int);    
         
        //Binary files handlers
        void userToFile(ofstream&) const;    
        void userFromFile(ifstream&);
};
#endif