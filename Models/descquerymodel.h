#ifndef DESCQUERYMODEL_H
#define DESCQUERYMODEL_H

#include <QSqlQueryModel>

class DescQueryModel : public QSqlQueryModel
{
public:
	explicit DescQueryModel(QObject *parent = 0);

	static const QString ModelQueryString;
	static const QStringList HorizontalHeaderList;
};

#endif // DESCQUERYMODEL_H
