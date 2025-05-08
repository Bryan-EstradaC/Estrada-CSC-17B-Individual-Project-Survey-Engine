#include "Record.hpp"

/**
 * @brief Saves a list of users to a binary file.
 * @param users A vector of User objects to save.
 * @param filename The name of the binary file to write to.
 */
void Record::saveUsers(const vector<User>& users, const string& filename) {
    ofstream out(filename, ios::binary);
    int count = users.size();
    out.write(reinterpret_cast<char*>(&count), sizeof(count));
    for (const auto& user : users)
        user.userToFile(out);
    out.close(); 
}

/**
 * @brief Loads users from a binary file.
 * @param filename The name of the binary file to read from.
 */
vector<User> Record::loadUsers(const string& filename) {
    vector<User> users;
    ifstream in(filename, ios::binary);
    if (!in) return users;

    int count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    for (int i = 0; i < count; ++i) {
        User u;
        u.userFromFile(in);
        users.push_back(u);
    }
    in.close();
    return users;
}

/**
 * @brief Saves a list of surveys and their questions/choices to a binary file.
 * @param surveys A vector of Survey objects to save.
 * @param filename The name of the binary file to write to.
 */
void Record::saveSurveys(const vector<Survey>& surveys, const string& filename) {
    ofstream out(filename, ios::binary);
    int count = surveys.size();
    out.write(reinterpret_cast<char*>(&count), sizeof(count));
    for (const auto& s : surveys) {
        int len = s.getTitle().size();
        out.write(reinterpret_cast<char*>(&len), sizeof(len));
        out.write(s.getTitle().c_str(), len);

        auto questions = s.getAllQuestions();
        int qCount = questions.size();
        out.write(reinterpret_cast<char*>(&qCount), sizeof(qCount));
        for (const auto& q : questions) {
            int qLen = q.getText().size();
            out.write(reinterpret_cast<char*>(&qLen), sizeof(qLen));
            out.write(q.getText().c_str(), qLen);
            bool isMC = q.getIsMultipleChoice();
            out.write(reinterpret_cast<char*>(&isMC), sizeof(isMC));

            auto choices = q.getChoices();
            int chCount = choices.size();
            out.write(reinterpret_cast<char*>(&chCount), sizeof(chCount));
            for (const auto& c : choices) {
                int clen = c.size();
                out.write(reinterpret_cast<char*>(&clen), sizeof(clen));
                out.write(c.c_str(), clen);
            }
        }
    }
    out.close();
}

/**
 * @brief Loads surveys and their questions and choices from a binary file.
 * @param filename The name of the binary file to read from.
 */
vector<Survey> Record::loadSurveys(const string& filename) {
    vector<Survey> surveys;
    ifstream in(filename, ios::binary);
    if (!in) return surveys;

    int count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (int i = 0; i < count; ++i) {
            int len;
            in.read(reinterpret_cast<char*>(&len), sizeof(len));
            string title(len, ' ');
            in.read(&title[0], len);
            Survey survey(title);

            int qCount;
            in.read(reinterpret_cast<char*>(&qCount), sizeof(qCount));
            for (int j = 0; j < qCount; ++j) {
                int qLen;
                in.read(reinterpret_cast<char*>(&qLen), sizeof(qLen));
                string qText(qLen, ' ');
                in.read(&qText[0], qLen);

                bool isMC;
                in.read(reinterpret_cast<char*>(&isMC), sizeof(isMC));
                Question q(qText, isMC);

                int chCount;
                in.read(reinterpret_cast<char*>(&chCount), sizeof(chCount));
                for (int k = 0; k < chCount; ++k) {
                    int clen;
                    in.read(reinterpret_cast<char*>(&clen), sizeof(clen));
                    string choice(clen, ' ');
                    in.read(&choice[0], clen);
                    q.addChoice(choice);
                }
                survey.addQuestion(q);
            }
            surveys.push_back(survey);
        }
    in.close();
    return surveys;
}

/**
 * @brief Saves a list of responses to a binary file.
 * @param responses A vector of Response objects to save.
 * @param filename The name of the binary file to write to.
 */
void Record::saveResponses(const vector<Response>& responses, const string& filename) {
    ofstream out(filename, ios::binary);
    int count = responses.size();
    out.write(reinterpret_cast<char*>(&count), sizeof(count));
    for (const auto& r : responses) {
        int nameLen = r.getUser().size();
        out.write(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        out.write(r.getUser().c_str(), nameLen);
        int sIndex = r.getSurveyIndex();
        out.write(reinterpret_cast<char*>(&sIndex), sizeof(sIndex));

        // Save answers
        map<int, string> answers = r.getAnswers(); // Add getAnswers() in Response class
        int ansCount = answers.size();
        out.write(reinterpret_cast<char*>(&ansCount), sizeof(ansCount));
        for (auto& pair : answers) {
            out.write(reinterpret_cast<const char*>(&pair.first), sizeof(pair.first));
            int aLen = pair.second.size();
            out.write(reinterpret_cast<char*>(&aLen), sizeof(aLen));
            out.write(pair.second.c_str(), aLen);
        }
    }
    out.close();
}

/**
 * @brief Loads responses from a binary file.
 * @param filename The name of the binary file to read from.
 */
vector<Response> Record::loadResponses(const string& filename) {
    vector<Response> responses;
    ifstream in(filename, ios::binary);
    if (!in) return responses;

    int count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    for (int i = 0; i < count; ++i) {
        int nameLen;
        in.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        string user(nameLen, ' ');
        in.read(&user[0], nameLen);

        int sIndex;
        in.read(reinterpret_cast<char*>(&sIndex), sizeof(sIndex));

        Response r(user, sIndex);

        int ansCount;
        in.read(reinterpret_cast<char*>(&ansCount), sizeof(ansCount));
        for (int j = 0; j < ansCount; ++j) {
            int qIndex;
            in.read(reinterpret_cast<char*>(&qIndex), sizeof(qIndex));
            int aLen;
            in.read(reinterpret_cast<char*>(&aLen), sizeof(aLen));
            string answer(aLen, ' ');
            in.read(&answer[0], aLen);
            r.recordAnswer(qIndex, answer);
        }
        responses.push_back(r);
    }
    in.close();
    return responses;
}