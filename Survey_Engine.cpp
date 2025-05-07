#include "Survey_Engine.hpp"
#include <iostream>
using namespace std;

/**
 * @brief Constructs a Survey_Engine and loads users, surveys, and responses from binary files.
 */
Survey_Engine::Survey_Engine(){
    users = Record::loadUsers("users.dat");
    surveys = Record::loadSurveys("surveys.dat");
    responses = Record::loadResponses("responses.dat");
}

/**
 * @brief Logs in an existing user or creates a new one.
 */
void Survey_Engine::loginUser(){
    string username;
    cout << "=== Log in or sign up ===" << endl;
    cout << "Enter username: ";
    cin >> username;
    //getline(cin, username);
    //cin.ignore();
    for(auto& user : users){
        if(user.getUsername() == username){
            currentUser = &user;
            cout << "Welcome back, " << username << "!" << endl;
            return;
        }
    }
    // char role;
    bool isAdmin;
    // cout << "Are you an admin? (y/n): ";
    // cin >> role;
    // if( role == 'Y' || role == 'y'){
    //     isAdmin = true;
    // }
    
    if(users.empty()){
        isAdmin = true;
    } else{
        isAdmin = false;
    }
    users.emplace_back(username, isAdmin);
    currentUser = &users.back();
    cout << "New user created. Welcome, " << username << "!" << endl;
    if(currentUser->getIsAdmin() == true){
        cout << "You are the admin!" << endl;
    }
}

/**
 * @brief Saves all current users, surveys, and responses to binary files.
 */
void Survey_Engine::saveData(){
    Record::saveUsers(users, "users.dat");
    Record::saveResponses(responses, "responses.dat");
    Record::saveSurveys(surveys, "surveys.dat");
}

/**
 * @brief Allows an admin to create a new survey.
 */
void Survey_Engine::createSurvey() {
    // if(!currentUser || !currentUser->getIsAdmin()){
    //     cout << "Only admins can create surveys." << endl;
    //     return;
    // }

    string title;
    cout << "\nEnter title of the survey: ";
    cin.ignore();
    getline(cin, title);
    Survey newSurvey(title);

    int numQuestions;
    cout << "How many questions? ";
    cin >> numQuestions;
    cin.ignore();

    for (int i = 0; i < numQuestions; i++) {
        string qText;
        cout << "\nEnter question " << i + 1 << ": ";
        getline(cin, qText);

        char choiceType;
        cout << "Is it multiple choice (y/n): ";
        cin >> choiceType;
        cin.ignore();

        Question q(qText, choiceType == 'y');

        if (choiceType == 'y') {
            int numChoices;
            cout << "How many choices? ";
            cin >> numChoices;
            cin.ignore();

            for (int j = 0; j < numChoices; j++) {
                string choice;
                cout << "Enter choice " << j + 1 << ": ";
                getline(cin, choice);
                q.addChoice(choice);
            }
        }

        newSurvey.addQuestion(q);
    }

    surveys.push_back(newSurvey);
    cout << "\nSurvey created successfully!" << endl;
}

/**
 * @brief Allows the current user to take a selected survey.
 */
void Survey_Engine::takeSurvey() {
    if (surveys.empty()) {
        cout << "\nNo surveys available.\n";
        return;
    }

    // string user;
    // cout << "\nEnter your name: ";
    // getline(cin, user);

    cout << "\nAvailable Surveys:\n";
    for (int i = 0; i < surveys.size(); i++) {
        cout << i + 1 << ". " << surveys[i].getTitle() << endl;
    }

    int choice;
    cout << "Select a survey: ";
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > surveys.size()) {
        cout << "Invalid survey selection.\n";
        return;
    }

    Survey selectedSurvey = surveys[choice - 1];
    Response userResponse(currentUser->getUsername(), choice - 1);

    vector<Question> questions = selectedSurvey.getAllQuestions();
    cout << "=== " << selectedSurvey.getTitle() << " ===" << endl;
    for (int i = 0; i < questions.size(); i++) {
        cout << i + 1 << ": ";
        questions[i].display();

        string answer;
        cout << "Your answer: ";
        getline(cin, answer);
        userResponse.recordAnswer(i, answer);
    }

    responses.push_back(userResponse);
    cout << "\nSurvey completed!" << endl;
}

/**
 * @brief Displays recorded responses to a selected survey.
 */
void Survey_Engine::viewResults() const {
    if (surveys.empty()) {
        cout << "\nNo surveys available.\n";
        return;
    }

    // Step 1: List all surveys
    cout << "\n=== Available Surveys ===\n";
    for (int i = 0; i < surveys.size(); i++) {
        cout << i + 1 << ". " << surveys[i].getTitle() << endl;
    }

    // Step 2: User selects a survey
    int surveyChoice;
    cout << "Select a survey to view responses: ";
    cin >> surveyChoice;
    cin.ignore();

    if (surveyChoice < 1 || surveyChoice > surveys.size()) {
        cout << "Invalid survey selection.\n";
        return;
    }

    int selectedSurveyIndex = surveyChoice - 1;
    const Survey& selectedSurvey = surveys[selectedSurveyIndex];

    // Step 3: Collect users who responded to this survey
    vector<const Response*> matchedResponses;
    for (const auto& r : responses) {
        if (r.getSurveyIndex() == selectedSurveyIndex) {
            matchedResponses.push_back(&r);
        }
    }

    if (matchedResponses.empty()) {
        cout << "\nNo responses found for this survey.\n";
        return;
    }

    // Step 4: Display list of users
    cout << "\nUsers who responded to \"" << selectedSurvey.getTitle() << "\":\n";
    int idx = 1;
    map<int, const Response*> responseMap;
    for (const auto& r : matchedResponses) {
        cout << idx << ". " << r->getUser() << endl;
        responseMap[idx] = r;
        idx++;
    }

    // Step 5: Let user choose which response to view
    int userChoice;
    cout << "Select a user to view their response: ";
    cin >> userChoice;
    cin.ignore();

    if (responseMap.find(userChoice) != responseMap.end()) {
        cout << "\n==== "<< selectedSurvey.getTitle() << " ====";
        cout << "\n--- Response Details ---\n";
        responseMap[userChoice]->display(selectedSurvey);
    } else {
        cout << "Invalid user selection.\n";
    }
}

/**
 * @brief Starts the survey engine menu loop.
 */
void Survey_Engine::start(){
    loginUser();
    int choice;
    if(currentUser->getIsAdmin() == true){
        do{
            cout << "\n===== SURVEY ENGINE =====" << endl;
            cout << "1. Create Survey" << endl;
            cout << "2. Take Survey" << endl;
            cout << "3. View Results" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch(choice){
                case 1: createSurvey();
                        break;
                case 2: takeSurvey();
                        break;
                case 3: viewResults();
                        break;
                case 4: saveData();
                        cout << "Goodbye" << endl;
                        break;
                default: cout << "Invalid choice. Try again" << endl;
            }
        }while( choice != 4);
    } else{
        do{
            cout << "==== Survey Engine ====" << endl;
            cout << "1. Take Survey" << endl;
            cout << "2. View Results" << endl;
            cout << "3. Exit" << endl;
            cin >> choice;

            switch(choice){
                case 1: takeSurvey();
                        break;
                case 2: viewResults();
                        break;
                case 3: saveData();
                        cout << "Goodbye" << endl;
                        break;
                default: cout << "Invalid choice. Try again" << endl;
            }
        }while( choice != 3);
    }
}