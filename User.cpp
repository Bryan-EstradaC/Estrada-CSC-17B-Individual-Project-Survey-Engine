#include "User.hpp"


User::User(){}

User::User(string name = "", bool admin = false) {
    this->username = name;
    this->isAdmin = admin;
}

string User::getUsername() const { 
    return username; 
}

bool User::getIsAdmin() const { 
    return isAdmin; 
}
void User::setAdmin(bool admin) { 
    isAdmin = admin; 
}

void User::addTakenSurvey(int index) { 
    takenSurveys.push_back(index); 
}

vector<int> User::getTakenSurveys() const { 
    return takenSurveys; 
}

void User::userToFile(ofstream& out) const {
    int len = username.size();
    out.write(reinterpret_cast<char*>(&len), sizeof(len));
    out.write(username.c_str(), len);
    out.write(reinterpret_cast<const char*>(&isAdmin), sizeof(isAdmin));
    int surveyCount = takenSurveys.size();
    out.write(reinterpret_cast<char*>(&surveyCount), sizeof(surveyCount));
    for (int index : takenSurveys)
        out.write(reinterpret_cast<char *>(&index), sizeof(index));
}

void User::userFromFile(ifstream& in) {
    int len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    username.resize(len);
    in.read(&username[0], len);
    in.read(reinterpret_cast<char*>(&isAdmin), sizeof(isAdmin));

    int surveyCount;
    in.read(reinterpret_cast<char*>(&surveyCount), sizeof(surveyCount));
    takenSurveys.resize(surveyCount);
    for (int i = 0; i < surveyCount; ++i)
        in.read(reinterpret_cast<char*>(&takenSurveys[i]), sizeof(takenSurveys[i]));
}