#include "doc_Json.h"
#include <QJsonParseError>
#include <QJsonObject>
#include <QDebug>

bool JS::donToJsObj(const QByteArray &doc, QJsonObject &jsonObj)
{
    QJsonParseError jsonError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(doc, &jsonError);
    if ((jsonDocument.isNull()) || (jsonError.error != QJsonParseError::NoError)) {
        qWarning()<< "UdpSocket::documentToJsonObj() json 字串解析错误" << endl;
        return false;
    }
    if (!jsonDocument.isObject()) {
        qWarning()<< "UdpSocket::documentToJsonObj() 这不是一个 json 对象" << endl;
        return false;
    }
    jsonObj = jsonDocument.object();
    return true;
}

QByteArray JS::jsonToDoc(const QJsonObject & jsonObj, QJsonDocument::JsonFormat format)
{
    QJsonDocument document;
    document.setObject(jsonObj);
    return document.toJson(format);
}

