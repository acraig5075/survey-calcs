#include "stationsquerymodel.h"
#include "utils.h"

const QString StationsQueryModel::ModelQueryString = "SELECT station AS Name, setupno AS Setup, oc AS Correction, insthgt AS `Instr. hgt`, date AS Date FROM occupied ORDER BY station, setupno";

StationsQueryModel::StationsQueryModel(QObject *parent)
	: QSqlQueryModel(parent)
{
}

QVariant StationsQueryModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::TextAlignmentRole)
	{
		switch(index.column())
		{
		case 2:
		case 3:
			return Qt::AlignRight + Qt::AlignVCenter;
		default:
			break;
		}
	}
	else if (role == Qt::DisplayRole)
	{
		switch(index.column())
		{
		case 2:
		{
			QVariant d = QSqlQueryModel::data(index, role);
			return static_cast<QVariant>(Utils::Rad2Dms(d.toDouble(), ':'));
		}
		case 3:
		{
			QVariant d = QSqlQueryModel::data(index, role);
			return static_cast<QVariant>(QString::number(d.toDouble(), 'f', 2));
		}
		default:
			break;
		}
	}

	return QSqlQueryModel::data(index, role);
}
