#include "stationscontroller.h"
#include "Types/occupied.h"
#include "Types/observation.h"
#include "Dialogs/tabledlg.h"
#include "Models/observationsquerymodel.h"
#include <QSqlDatabase>
#include <QSqlQuery>

StationsController::StationsController(QObject *parent)
 : QObject(parent)
{

}

void StationsController::ShowObservations(QWidget *parent, const Occupied &station)
{
	QString caption = QString("Observations at %1 setup %2").arg(station.m_name).arg(station.m_setup);
	QString query = QString(ObservationsQueryModel::ModelQueryString).arg(station.m_name).arg(station.m_setup);

	QSqlDatabase db = QSqlDatabase::database();
	db.transaction();

	TableDlg<Observation, StationsController, ObservationsQueryModel> dlg(*this, caption, query, parent);

	if (dlg.exec() == QDialog::Accepted)
		db.commit();
	else
		db.rollback();
}

bool StationsController::Add(const Observation &obs)
{
	QSqlQuery query;
	query.prepare("INSERT INTO obs (station, setup, target, dirc, vert, dist, desc, prismhgt) "
				  "VALUES (:station, :setup, :target, :dirc, :vert, :dist, :desc, :prismhgt)");

	query.bindValue("station", obs.m_station);
	query.bindValue("setup", obs.m_setup);
	query.bindValue("target", "DUMMY");
	query.bindValue("dirc", 123.1234);
	query.bindValue("vert", 90.1234);
	query.bindValue("dist", 42.001);
	query.bindValue("desc", "DES");
	query.bindValue("prismhgt", "1.750");

	return query.exec();
}
