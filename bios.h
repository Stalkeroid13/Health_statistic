#ifndef TOGETHER_PROJECT_BIOS_H
#define TOGETHER_PROJECT_BIOS_H

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class BIOS
{
public:
    unordered_multimap<string, string> general_map_;

    bool LoadDataFromFile(const string& file_name);

    bool WriteDataToFile(const string& file_name);

    BIOS();

    // Додати новий запис у хеш-таблицю
    void AddEntry(const string& key, const string& value);

    // Видалити запис за ключем (видаляє ВСІ записи з таким ключем)
    void RemoveEntry(const string& key);

    // Видалити запис за ключем (видаляє ПЕВНИЙ запис з таким ключем)
    bool RemoveSpecificEntry(const string& key, const string& value);

    // Отримати значення для певного ключа (повертає ВСІ записи з таким ключем)
    vector<string> GetValues(const string& key) const;

    // Отримати значення для певного ключа (повертає ПЕВНИЙ запис з таким ключем)
    vector<string> GetSpecificValues(const string& key, const string& keyword) const;

    // Оновити значення для певного ключа
    bool UpdateEntry(const string& key, const string& old_value, const string& new_value);

    // Вивести всі дані хеш-таблиці (для тестування)
    void DisplayAll() const;

    // Знайти дату останього запису у хеш-таблицю
    string findLatestDate();

    ~BIOS();
};

#endif
