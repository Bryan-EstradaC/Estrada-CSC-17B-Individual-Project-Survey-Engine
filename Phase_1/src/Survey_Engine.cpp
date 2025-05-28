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

    //Enter username. 
    //If first time, it will sign up.
    //If already signed up, it will log in.
    cout << "=== Log in or sign up ===" << endl;
    cout << "Enter username: ";
    cin >> username;
    //getline(cin, username);
    //cin.ignore();
    for(auto& user : users){
        //Identify if username is in the vector.
        if(user.getUsername() == username){
            currentUser = &user;    //User using the program.
            cout << "Welcome back, " << username << "!" << endl;
            return; //Log in completed, go to the main menu.
        }
    }
    // char role;
    bool isAdmin;
    // cout << "Are you an admin? (y/n): ";
    // cin >> role;
    // if( role == 'Y' || role == 'y'){
    //     isAdmin = true;
    // }
    
    //If non user in the vector, then the first user that signed up becomes the admin.
    if(users.empty()){
        isAdmin = true;
    } else{
        isAdmin = false;
    }
    //If new user, then store it in the vector
    users.emplace_back(username, isAdmin);  //Stores user in the vector.
    currentUser = &users.back();    //User using the program
    cout << "New user created. Welcome, " << username << "!" << endl;
    if(currentUser->getIsAdmin() == true){  //If 1st user registered in the program, then becomes admin.
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
    Survey newSurvey(title);    //Create new survey

    //Enter number of questions for the survey
    int numQuestions;
    cout << "How many questions? ";
    cin >> numQuestions;
    cin.ignore();

    //Enter each question text
    for (int i = 0; i < numQuestions; i++) {
        string qText;
        cout << "\nEnter question " << i + 1 << ": ";
        getline(cin, qText);

        //Define whether question is multiple choice or not
        char choiceType;
        cout << "Is it multiple choice (y/n): ";
        cin >> choiceType;
        cin.ignore();

        //Create the question and identifies whether has multiple choices
        Question q(qText, choiceType == 'y');

        //Enter choices if question is multiplce choices
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

        newSurvey.addQuestion(q);   //Add question to the survey
    }

    surveys.push_back(newSurvey);   //Add survey to vector
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

    //Display title of the available surveys
    cout << "\nAvailable Surveys:\n";
    for (int i = 0; i < surveys.size(); i++) {
        cout << i + 1 << ". " << surveys[i].getTitle() << endl;
    }

    //Choose a survey to take
    int choice;
    cout << "Select a survey: ";
    cin >> choice;
    cin.ignore();
    if (choice < 1 || choice > surveys.size()) {
        cout << "Invalid survey selection.\n";
        return;
    }

    Survey selectedSurvey = surveys[choice - 1];    //Set the selected survey
    Response userResponse(currentUser->getUsername(), choice - 1);  //Create a map to store user's responses

    //Display the questions and ask the user to respond them
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

    //List all surveys
    cout << "\n=== Available Surveys ===\n";
    for (int i = 0; i < surveys.size(); i++) {
        cout << i + 1 << ". " << surveys[i].getTitle() << endl;
    }

    //User selects a survey
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

    //Collect users who responded to this survey
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

    //Display list of users
    cout << "\nUsers who responded to \"" << selectedSurvey.getTitle() << "\":\n";
    int idx = 1;
    map<int, const Response*> responseMap;
    for (const auto& r : matchedResponses) {
        cout << idx << ". " << r->getUser() << endl;
        responseMap[idx] = r;
        idx++;
    }

    //Let user choose which response to view
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
    loginUser();    //Let the user to log in or sign up
    int choice;
    //Display the admin menu
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
        //Display the non-admin menu
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