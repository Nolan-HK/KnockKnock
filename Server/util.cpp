#include "util.h"

QJsonObject converToJson(const QByteArray& data)
{
	QJsonParseError jsonError;
	QJsonObject jsonObj;
	QJsonDocument doc = QJsonDocument::fromJson(data, &jsonError);

	if (!doc.isNull() && (jsonError.error == QJsonParseError::NoError)) {
		if (doc.isObject()) {
			jsonObj = doc.object();
			return jsonObj;
		}
	}
	else
	{
		qDebug() << "解析错误类型：" << jsonError.error;
		qDebug() << "解析错误信息：" << jsonError.errorString();
		qDebug() << "错误位置：" << jsonError.offset;
	}
	return QJsonObject();
}

QByteArray converToByteArray(const QJsonObject& data)
{
	QJsonDocument doc(data);
	return doc.toJson();
}
