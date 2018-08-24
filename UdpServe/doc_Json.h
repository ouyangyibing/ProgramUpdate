#ifndef JSON_H
#define JSON_H

#include <QJsonObject>
#include <QJsonDocument>

namespace JS {
bool donToJsObj(const QByteArray &doc, QJsonObject &jsonObj);
QByteArray jsonToDoc(const QJsonObject & jsonObj,  QJsonDocument::JsonFormat format = QJsonDocument::Indented);
}

#endif // JSON_H
