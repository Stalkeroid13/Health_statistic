#include "bios.h"
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

bool BIOS::LoadDataFromFile(const string& file_name)
{
    ifstream file(file_name);

    if (!file.is_open())
    {
        cerr << "Failed to open the file!" << endl;
        return false;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string date;
        string object;

        // Зчитуємо дату
        ss >> date;

        // Зчитуємо всі інші частини рядка як єдиний об'єкт
        string rest_of_line;
        getline(ss, rest_of_line);

        // Видаляємо зайвий пробіл на початку rest_of_line, якщо є
        if (!rest_of_line.empty() && rest_of_line[0] == ' ')
            rest_of_line.erase(0, 1);

        // Додаємо до таблиці
        AddEntry(date, rest_of_line);
    }

    file.close();
    return true;
}

bool BIOS::WriteDataToFile(const string& file_name)
{
    // Крок 1: Зчитати існуючі дані з файлу у набір (set)
    set<string> existingEntries;
    ifstream file_in(file_name);

    if (file_in.is_open())
    {
        string line;
        while (getline(file_in, line))
        {
            existingEntries.insert(line); // Додаємо рядок до набору
        }
        file_in.close();
    }

    // Крок 2: Відкрити файл у режимі "додати до кінця"
    ofstream file_out(file_name, ios::app);

    if (!file_out.is_open())
    {
        cerr << "Failed to open the file for writing!" << endl;
        return false;
    }

    // Крок 3: Перебрати дані з хеш-таблиці
    for (const auto& entry : general_map_)
    {
        string line = entry.first + " " + entry.second; // Формуємо рядок: "дата об'єкти"

        // Якщо такого запису ще немає у файлі, записуємо його
        if (existingEntries.find(line) == existingEntries.end())
        {
            file_out << line << endl;
        }
    }

    file_out.close();
    return true;
}

BIOS::BIOS()
{
    LoadDataFromFile("Exercise.txt");
}

// Додати новий запис у хеш-таблицю
void BIOS::AddEntry(const string& key, const string& value)
{
    general_map_.emplace(key, value);
}

// Видалити запис за ключем (видаляє ВСІ записи з таким ключем)
void BIOS::RemoveEntry(const string& key)
{
    general_map_.erase(key);
}

// Видалити запис за ключем (видаляє ПЕВНИЙ запис з таким ключем)
bool BIOS::RemoveSpecificEntry(const string& key, const string& value)
{
    auto range = general_map_.equal_range(key);

    for (auto it = range.first; it != range.second; ++it)
    {
        if (it->second == value)
        {
            general_map_.erase(it);
            return true;
        }
    }

    return false;
}

// Отримати значення для певного ключа (повертає ВСІ записи з таким ключем)
vector<string> BIOS::GetValues(const string& key) const
{
    vector<string> values;
    auto range = general_map_.equal_range(key);
    for (auto it = range.first; it != range.second; ++it)
        values.push_back(it->second);

    return values;
}

// Отримати значення для певного ключа (повертає ПЕВНИЙ запис з таким ключем)
vector<string> BIOS::GetSpecificValues(const string& key, const string& keyword) const
{
    vector<string> values;
    auto range = general_map_.equal_range(key);

    // Ітерація по діапазону з ключем
    for (auto it = range.first; it != range.second; ++it)
    {
        // Якщо значення містить ключове слово, додаємо його до результату
        if (it->second.find(keyword) != string::npos)
            values.push_back(it->second);
    }

    return values; // Повертаємо вектор знайдених значень
}

// Оновити значення для певного ключа
bool BIOS::UpdateEntry(const string& key, const string& old_value, const string& new_value)
{
    auto range = general_map_.equal_range(key);
    for (auto it = range.first; it != range.second; ++it)
        if (it->second == old_value)
        {
            it->second = new_value;
            return true;
        }

    return false;
}

// Вивести всі дані хеш-таблиці (для тестування)
void BIOS::DisplayAll() const
{
    for (const auto& entry : general_map_)
        cout << "Key: " << entry.first << ", Value: " << entry.second << endl;
}

string BIOS::findLatestDate()
{
    if (general_map_.empty())
    {
        return ""; // Якщо таблиця порожня
    }

    // Ініціалізуємо останню дату першим елементом таблиці
    string latest_date = general_map_.begin()->first;

    // Ітеруємо через всі елементи таблиці
    for (const auto& entry : general_map_)
    {
        if (entry.first > latest_date)
        {
            latest_date = entry.first; // Оновлюємо, якщо знайшли новішу дату
        }
    }

    return latest_date; // Повертаємо найновішу дату
}

BIOS::~BIOS()
{
    WriteDataToFile("Exercise.txt");
    general_map_.clear();
}
