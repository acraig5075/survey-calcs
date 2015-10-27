#include "coordscontroller.h"
#include "coord.h"
#include "Dialogs/editcoorddlg.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

CoordsController::CoordsController(QObject *parent) : QObject(parent)
{

}

void CoordsController::EditCoord(QWidget *parent, const Coord &coord)
{
	Coord newCoord(coord);
	EditCoordDlg dlg(parent, newCoord, *this);
	if (QDialog::Accepted == dlg.exec())
	{
	}
}

QStringList CoordsController::GetClassificationList() const
{
	return GetMnemonicList("SELECT `class` FROM class ORDER BY `order`");
}

QStringList CoordsController::GetDescriptionList() const
{
	return GetMnemonicList("SELECT `desc` FROM desc ORDER BY `desc`");
}

QStringList CoordsController::GetMnemonicList(const QString &select) const
{
	QStringList descList;

	QSqlDatabase db = QSqlDatabase::database();
	if (db.isOpen())
	{
		QSqlQuery query(db);
		query.prepare(select);
		query.exec();

		while (query.next())
			descList.push_back(query.value(0).toString());
	}

	return descList;
}
