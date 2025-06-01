#pragma once

#include <string>
#include <QString>

// Нормалізація українського рядка (нижній регістр, пробіли на _)
std::string NormalizeUkrainianName(const std::string& input);

// Зворотна операція: _ на пробіли
std::string DesanitizeName(const std::string& input);

// Нормалізація з QString на string
std::string SanitizeQString(const QString& input);

// Зворотна операція з string на QString
QString DesanitizeToQString(const std::string& input);
