#ifndef STATIONSQUERYMODEL_H
#define STATIONSQUERYMODEL_H

#include <QtSql/QSqlQueryModel>

class StationsQueryModel : public QSqlQueryModel
{
public:
	explicit StationsQueryModel(QObject *parent = 0);

	QVariant data(const QModelIndex& index, int role) const override;

	static const QString ModelQueryString;
};

#endif // STATIONSQUERYMODEL_H
