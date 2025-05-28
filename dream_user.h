//
// Created by Admin on 26.11.2024.
//

#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "DREAM.h"
using namespace std;

class User
{
private:
    string username;
    int userId;
    DreamManager dreamManager;

public:
    User(string name, int id, const string& fileName);

    void loadDreams(string fileName);
    void addDream(const string& date, int bedtime, int wake_uptime);
    void removeDream(const string& date);
    void printAllDreams();
    int getAssesment(int days);
    vector<Dream> getDreamsForLastDays(int days);

    string getUsername() const { return username; }
    int getUserId() const { return userId; }
};

#endif // USER_H
