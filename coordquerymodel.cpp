#include "coordquerymodel.h"

CoordQueryModel::CoordQueryModel(QObject *parent)
	: QSqlQueryModel(parent)
{}

QVariant CoordQueryModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::TextAlignmentRole)
	{
		switch(index.column())
		{
		case 1:
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
		case 1:
		case 2:
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
