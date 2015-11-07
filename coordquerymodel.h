#ifndef COORDQUERYMODEL_H
#define COORDQUERYMODEL_H

#include <QSqlQueryModel>

class CoordQueryModel : public QSqlQueryModel
{
public:
	CoordQueryModel(QObject *parent = 0);

	QVariant data(const QModelIndex& index, int role) const override;

	static const QString CoordQueryModel::ModelQueryString;
};


#endif // COORDQUERYMODEL_H

