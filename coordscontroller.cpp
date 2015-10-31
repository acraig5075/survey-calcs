#include "coordscontroller.h"
#include "coord.h"
#include "Dialogs/editcoorddlg.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

CoordsController::CoordsController(QObject *parent) : QObject(parent)
{

}

bool CoordsController::EditCoord(QWidget *parent, const Coord &coord)
{
	Coord newCoord(coord);
	EditCoordDlg dlg(parent, newCoord);
	if (QDialog::Accepted == dlg.exec())
	{
		QString update = newCoord.GetUpdateQueryString(QString::fromStdString(coord.m_name));
		return ModifyCoordTable(update);
	}

	return false;
}

bool CoordsController::ModifyCoordTable(const QString &sql)
{
	QSqlDatabase db = QSqlDatabase::database();
	if (db.isOpen())
	{
		QSqlQuery query(db);
		query.prepare(sql);
		bool ok = query.exec();

		qDebug() << "Update query returned " << ok;
		if (!ok)
			qDebug() << query.lastError();
		return ok;
	}

	return false;
}
