#include "string_utils.h"

#include <QString>
#include <algorithm>

// Нормалізація українського рядка (нижній регістр, пробіли на _)
std::string NormalizeUkrainianName(const std::string& input)
{
    QString qstr = QString::fromStdString(input).trimmed().toLower().replace(" ", "_");
    return qstr.toStdString();
}

// Зворотна операція: _ на пробіли
std::string DesanitizeName(const std::string& input)
{
    std::string result = input;
    std::replace(result.begin(), result.end(), '_', ' ');
    return result;
}

// Нормалізація з QString на string
std::string SanitizeQString(const QString& input)
{
    return input.trimmed().replace(" ", "_").toStdString();
}

// Зворотна операція з string на QString
QString DesanitizeToQString(const std::string& input)
{
    QString result = QString::fromStdString(input);
    return result.replace("_", " ");
}
