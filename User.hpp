#ifndef USER_HPP
#define USER_HPP

#include <fstream>
#include <string>
#include <vector>
using namespace std;

class User {
    private:
        string username;
        bool isAdmin;
        vector<int> takenSurveys;
    
    public:
        User();
        User(string, bool);  

        string getUsername() const;
        bool getIsAdmin() const;
        vector<int> getTakenSurveys() const;   

        void setAdmin(bool);    

        void addTakenSurvey(int);    
         
        void userToFile(ofstream&) const;    
        void userFromFile(ifstream&);
};
#endif