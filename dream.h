//
// Created by Admin on 09.10.2024.
//

#ifndef DREAM_H
#define DREAM_H
#include <iostream>
#include <sstream>
#include <QString>
#include "bios.h"
using namespace std;


class Dream
{
protected:
    string date;
    int bedtime;
    int wake_uptime;
    int duration;
    bool isNight; //true = night, false = day

public:
    Dream(string d, int b, int w, int dur, bool night);

    void countDuration();
    void countSleepType();
    virtual QString toQString() const;

    // Геттери
    string getDate() const { return date; }
    int getBedtime() const { return bedtime; }
    int getWakeUptime() const { return wake_uptime; }
    int getDuration() const { return duration; }
    int getSleepType() const { return isNight; }
};

// Похідний клас для денного сну
class DayDream : public Dream
{
public:
    DayDream(string d, int b, int w, int dur);
    QString toQString() const override;
};


class DreamManager
{
private:
    BIOS bios_;
    string serializeDream(const Dream& dream);
    Dream deserializeDream(const string& date, const string& data);
    DayDream deserializeDayDream(const string& date, const string& data);

public:
    Dream createDream(string date, int bedtime, int wake_uptime);
    void loadDreams(string fileName);
    void addDream(const Dream& dream);
    void removeDream(const string& date);
    void printAllDreams();
    vector<Dream> getDreamsForLastDays(int days);
    int averageDuration(int days);
    int sleepAssessment(int days);
    int regularity(int days);
};


#endif //DREAM_H
