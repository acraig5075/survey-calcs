#ifndef STATIONSQUERYMODEL_H
#define STATIONSQUERYMODEL_H

#include <QtSql/QSqlQueryModel>

class StationsQueryModel : public QSqlQueryModel
{
public:
	StationsQueryModel(QObject *parent = 0);
	static const QString ModelQueryString;
};

#endif // STATIONSQUERYMODEL_H
