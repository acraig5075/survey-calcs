#include "observationsquerymodel.h"
#include "utils.h"

const QString ObservationsQueryModel::ModelQueryString = "SELECT target, dirc, vert, dist, desc, prismhgt FROM obs WHERE station = '%1' AND setup = %2 ORDER BY `order`";

const QStringList ObservationsQueryModel::HorizontalHeaderList = QStringList() << "Target" << "Angle" << "Azimuth" << "Slope dist." << "Descr." << "Target hgt.";

ObservationsQueryModel::ObservationsQueryModel(QObject *parent)
	: QSqlQueryModel(parent)
{
}

QVariant ObservationsQueryModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::TextAlignmentRole)
	{
		switch(index.column())
		{
		case 0:
		case 4:
			return Qt::AlignLeft + Qt::AlignVCenter;
		default:
			return Qt::AlignRight + Qt::AlignVCenter;
		}
	}
	else if (role == Qt::DisplayRole)
	{
		switch(index.column())
		{
		case 1:
		case 2:
		{
			QVariant d = QSqlQueryModel::data(index, role);
			return static_cast<QVariant>(Utils::Rad2Dms(d.toDouble(), ':'));
		}
		case 3:
		case 5:
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
