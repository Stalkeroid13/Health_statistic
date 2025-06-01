#include "string_utils.h"
#include <QString>
#include <algorithm>

std::string NormalizeUkrainianName(const std::string& input)
{
    QString qstr = QString::fromStdString(input).trimmed().toLower().replace(" ", "_");
    return qstr.toStdString();
}

std::string DesanitizeName(const std::string& input)
{
    std::string result = input;
    std::replace(result.begin(), result.end(), '_', ' ');
    return result;
}

std::string SanitizeQString(const QString& input)
{
    return input.trimmed().replace(" ", "_").toStdString();
}

QString DesanitizeToQString(const std::string& input)
{
    QString result = QString::fromStdString(input);
    return result.replace("_", " ");
}
