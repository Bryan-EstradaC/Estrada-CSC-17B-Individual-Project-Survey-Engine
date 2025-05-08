#include "User.hpp"


/**
* @brief Constructs a new Survey.
*/
User::User(){}

/**
* @brief Constructs a new Survey.
* @param name username
* @param admin Defines whether the user is admin or not
*/
User::User(string name = "", bool admin = false) {
    this->username = name;
    this->isAdmin = admin;
}

/**
* @brief Returns username.
*/
string User::getUsername() const { 
    return username; 
}


/**
* @brief Returns isAdmin.
*/
bool User::getIsAdmin() const { 
    return isAdmin; 
}

/**
* @brief Sets whether a user is admin or not.
* @param admin Bool variable that will set member variable to true or false.
*/
void User::setAdmin(bool admin) { 
    isAdmin = admin; 
}

/**
* @brief Writes user's information to a binary file.
* @param out fstream object to write to a binary file.
*/
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

/**
* @brief Read user's information from a binary file.
* @param in fstream object to read from a binary file.
*/
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