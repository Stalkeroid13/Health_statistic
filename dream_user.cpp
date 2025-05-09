//
// Created by Admin on 26.11.2024.
//
#include "dream_user.h"


// Конструктор

User::User(string name, int id, const string& fileName) : username(name), userId(id)
{
    // if (!bios.LoadDataFromFile(fileName))
    // {
    //     cerr << "Error: Failed to load data from file: " << fileName << endl;
    // }
    // else
    // {
    //     cout << "Data successfully loaded from file: " << fileName << endl;
    // }
}

void User::addDream(const string& date, int bedtime, int wake_uptime)
{
    Dream newDream = dreamManager.createDream(date, bedtime, wake_uptime);
    dreamManager.addDream(newDream);
    cout << "Dream successfully added for the user: " << username << endl;
}

// Видалити сон
void User::removeDream(const string& date)
{
    dreamManager.removeDream(date);
    cout << "Dreams have been deleted for the date: " << date << endl;
}

//Вивести всі сни
void User::printAllDreams()
{
    cout << "User's dreams: " << username << endl;
    dreamManager.printAllDreams();
}

int User::getAssesment(int days)
{
    return dreamManager.sleepAssessment(days);
}
