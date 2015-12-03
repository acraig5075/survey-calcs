#ifndef COORDQUERYMODEL_H
#define COORDQUERYMODEL_H

#include <QSqlQueryModel>


class CoordQueryModel : public QSqlQueryModel
{
public:
	explicit CoordQueryModel(QObject *parent = 0);

	QVariant data(const QModelIndex& index, int role) const override;

	static const QString ModelQueryString;
	static const QStringList HorizontalHeaderList;
};


#endif // COORDQUERYMODEL_H

