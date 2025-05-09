//
// Created by Admin on 09.10.2024.
//
#include "DREAM.h"
#include <sstream>
#include <algorithm>
#include <math.h>

using namespace std;


// int convertTimeToMinutes(string time)
// {
//     int hours = stoi(time.substr(0, 2));
//     int minutes = stoi(time.substr(3, 2));
//
//     return hours * 60 + minutes;
// }


Dream::Dream(string d, int b, int w, int dur, bool night)
    : date(d), bedtime(b), wake_uptime(w), duration(dur), isNight(night)
{
    if (duration == 0)
    {
        countDuration();
    }
    countSleepType();
}


DayDream::DayDream(string d, int b, int w, int dur)
    : Dream(d, b, w, dur, false)
{
}

void Dream::print()
{
    cout << "Date: " << date << endl;
    cout << "Bedtime: " << bedtime << " minutes" << endl;
    cout << "Wake-up time: " << wake_uptime << " minutes" << endl;
    cout << "Duration: " << duration << " minutes" << endl;
    cout << "Type: Night dream" << endl;
}


void DayDream::print()
{
    cout << "Date: " << date << endl;
    cout << "Bedtime: " << bedtime << " minutes" << endl;
    cout << "Wake-up time: " << wake_uptime << " minutes" << endl;
    cout << "Duration: " << duration << " minutes" << endl;
    cout << "Type: Day dream" << endl;
}

void Dream::countDuration()
{
    if (wake_uptime >= bedtime)
    {
        // Якщо час пробудження пізніше або одночасно з часом засинання
        duration = wake_uptime - bedtime;
    }
    else
    {
        // 1440 хв = 24 год
        duration = (1440 - bedtime) + wake_uptime;
    }
}

void Dream::countSleepType()
{
    int day_start = 390; // 6:30 у хвилинах
    int day_end = 1200; // 20:00 у хвилинах

    if (bedtime >= day_start && bedtime < day_end && wake_uptime > day_start && wake_uptime <= day_end)
    {
        isNight = false; // Денний сон
    }
    else
    {
        isNight = true; // Нічний сон
    }
}


Dream DreamManager::createDream(string date, int bedtime, int wake_uptime)
{
    // Часові межі для денного сну
    int day_start = 390; // 6:30 у хвилинах
    int day_end = 1200; // 20:00 у хвилинах

    if (bedtime >= day_start && bedtime < day_end &&
        wake_uptime > day_start && wake_uptime <= day_end)
    {
        return DayDream(date, bedtime, wake_uptime, 0);
    }
    else
    {
        return Dream(date, bedtime, wake_uptime, 0, true);
    }
}

string convertDateToISO(const string& date)
{
    if (date.size() != 10 || date[2] != '/' || date[5] != '/')
    {
        cerr << "Invalid date format: " << date << endl;
        return "";
    }

    string day = date.substr(0, 2);
    string month = date.substr(3, 2);
    string year = date.substr(6, 4);

    return year + "-" + month + "-" + day;
}

// Перетворення Dream на string для зберігання в BIOS
string DreamManager::serializeDream(const Dream& dream)
{
    return to_string(dream.getBedtime()) + " " +
        to_string(dream.getWakeUptime()) + " " +
        to_string(dream.getDuration()) + " " +
        to_string(dream.getSleepType()); // 1 або 0
}

// Перетворення string на об'єкт Dream для отримання з BIOS
Dream DreamManager::deserializeDream(const string& date, const string& data)
{
    stringstream ss(data);
    int bedtime, wake_uptime, duration, isNight;

    ss >> bedtime >> wake_uptime >> duration >> isNight;

    if (isNight == 0)
    {
        return Dream("", 0, 0, 0, true);
    }

    return Dream(date, bedtime, wake_uptime, duration, true);
}

DayDream DreamManager::deserializeDayDream(const string& date, const string& data)
{
    stringstream ss(data);
    int bedtime, wake_uptime, duration;

    ss >> bedtime >> wake_uptime >> duration;

    return DayDream(date, bedtime, wake_uptime, duration);
}


void DreamManager::addDream(const Dream& dream)
{
    string serialized = serializeDream(dream);
    bios_.AddEntry(dream.getDate(), serialized);
}

// Видалити всі сни за певну дату
void DreamManager::removeDream(const string& date)
{
    bios_.RemoveEntry(date);
}

void DreamManager::printAllDreams()
{
    bios_.DisplayAll();
}

string calculateStartDateAsString(const string& latest_date, int days)
{
    // Перевірка формату дати DD/MM/YYYY
    if (latest_date.size() != 10 || latest_date[2] != '/' || latest_date[5] != '/')
    {
        cerr << "Invalid date format: " << latest_date << endl;
        return "";
    }

    // Розбиваємо дату
    string day_str = latest_date.substr(0, 2);
    string month_str = latest_date.substr(3, 2);
    string year_str = latest_date.substr(6, 4);

    // Перевіряємо, чи всі символи є цифрами
    if (!isdigit(day_str[0]) || !isdigit(day_str[1]) ||
        !isdigit(month_str[0]) || !isdigit(month_str[1]) ||
        !isdigit(year_str[0]) || !isdigit(year_str[1]) ||
        !isdigit(year_str[2]) || !isdigit(year_str[3]))
    {
        cerr << "Date contains invalid characters: " << latest_date << endl;
        return "";
    }

    // Конвертуємо день, місяць, рік у числа
    int year = stoi(year_str);
    int month = stoi(month_str);
    int day = stoi(day_str);

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        days_in_month[1] = 29;
    }

    day -= days;
    while (day <= 0)
    {
        month--;
        if (month == 0)
        {
            month = 12;
            year--;
        }
        day += days_in_month[month - 1];
    }

    char buffer[11];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d", year, month, day);
    return string(buffer);
}

vector<Dream> DreamManager::getDreamsForLastDays(int days)
{
    vector<Dream> dreams;

    // Отримуємо останню дату
    string latest_date = bios_.findLatestDate();
    if (latest_date.empty())
    {
        cerr << "No latest date found in BIOS." << endl;
        return dreams;
    }

    string start_date = calculateStartDateAsString(latest_date, days);

    for (const auto& entry : bios_.general_map_)
    {
        string entry_date_iso = convertDateToISO(entry.first);

        // Пропускаємо записи, якщо дата не у форматі ISO
        if (entry_date_iso.empty())
        {
            continue;
        }

        // Пропускаємо записи, дата яких поза діапазоном
        if (entry_date_iso <= start_date || entry_date_iso > latest_date)
        {
            continue;
        }

        Dream dream = deserializeDream(entry.first, entry.second);

        if (!dream.getDate().empty() && dream.getSleepType())
        {
            dreams.push_back(dream);
        }
    }

    sort(dreams.begin(), dreams.end(), [](const Dream& a, const Dream& b)
    {
        return a.getDate() < b.getDate();
    });

    return dreams;
}


int DreamManager::averageDuration(int days)
{
    vector<Dream> dreams = getDreamsForLastDays(days);

    if (dreams.empty())
    {
        return 0;
    }

    int total_duration = 0;

    for (const auto& dream : dreams)
    {
        if (dream.getSleepType() == true)
        {
            total_duration += dream.getDuration();
        }
    }

    return total_duration / days;
}

int DreamManager::regularity(int days)
{
    vector<Dream> dreams = getDreamsForLastDays(days);

    if (dreams.empty() || dreams.size() == 1)
    {
        return 1; // Якщо немає даних або лише один запис, регулярність дотримана
    }

    // Обчислення середнього часу засинання
    int sum_bedtime = 0;
    for (const auto& dream : dreams)
    {
        sum_bedtime += dream.getBedtime();
    }
    double mean_bedtime = static_cast<double>(sum_bedtime) / dreams.size();

    // Обчислення стандартного відхилення
    double variance = 0.0;
    for (const auto& dream : dreams)
    {
        double diff = static_cast<double>(dream.getBedtime()) - mean_bedtime;
        variance += diff * diff;
    }
    variance /= dreams.size();
    double std_deviation = sqrt(variance);

    // Регулярність дотримана, якщо стандартне відхилення <= порогу
    const double tolerance = 30.0; // Поріг у хвилинах
    return std_deviation <= tolerance ? 1 : 0;
}


int DreamManager::sleepAssessment(int days)
{
    // Оцінка починається зі 100 балів
    int score = 100;

    // 1. Оцінка середньої тривалості сну
    int avg_duration = averageDuration(days); // У хвилинах
    const int recommended_duration = 7 * 60; // 7 годин = 420 хвилин
    if (avg_duration < recommended_duration)
    {
        int deficit = recommended_duration - avg_duration;
        score -= deficit / 10; // Кожні 10 хвилин дефіциту знижують бал
    }

    // 2. Оцінка регулярності
    int is_regular = regularity(days);
    if (!is_regular)
    {
        score -= 20; // Нерегулярність знижує бал на 20
    }

    // 3. Перевірка наявності денного сну
    vector<Dream> dreams = getDreamsForLastDays(days);
    int day_sleep_duration = 0;
    for (const auto& dream : dreams)
    {
        if (!dream.getSleepType())
        {
            day_sleep_duration += dream.getDuration();
        }
    }
    if (day_sleep_duration > 30)
    {
        score -= 10; // Якщо денний сон перевищує 30 хвилин, знижується бал
    }

    // Оцінка не може бути менше 0 і більше 100
    if (score < 0) score = 0;
    if (score > 100) score = 100;

    return score;
}
