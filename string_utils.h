#pragma once
#include <string>
#include <QString>

// Стандартні утиліти зі string
std::string NormalizeUkrainianName(const std::string& input);
std::string DesanitizeName(const std::string& input);

// Варіанти для переводу QString в string
std::string SanitizeQString(const QString& input);
QString DesanitizeToQString(const std::string& input);
