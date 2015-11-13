#ifndef OBSERVATIONSQUERYMODEL_H
#define OBSERVATIONSQUERYMODEL_H

#include <QtSql/QSqlQueryModel>

class ObservationsQueryModel : public QSqlQueryModel
{
public:
	explicit ObservationsQueryModel(QObject *parent = 0);

	QVariant data(const QModelIndex& index, int role) const override;

	static const QString ModelQueryString;
};

#endif // OBSERVATIONSQUERYMODEL_H
