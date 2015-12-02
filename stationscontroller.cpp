#include "stationscontroller.h"
#include "Types/occupied.h"
#include "Types/observation.h"
#include "Dialogs/tabledlg.h"
#include "Dialogs/stationdlg.h"
#include "Models/observationsquerymodel.h"
#include "utils.h"
#include <QSqlDatabase>
#include <QSqlQuery>

StationsController::StationsController(QObject *parent)
 : QObject(parent)
{

}

bool StationsController::AddStation(QWidget *parent, Occupied &station)
{
	StationDlg dlg(parent, station);
	if (QDialog::Accepted == dlg.exec())
	{
		QSqlQuery insert = station.GetInsertQueryString();
		return Utils::ExecQuery(insert);
	}

	return false;
}

bool StationsController::EditStation(QWidget *parent, const Occupied &station)
{
	Occupied newStation(station);
	StationDlg dlg(parent, newStation);
	if (QDialog::Accepted == dlg.exec())
	{
		QSqlQuery update = newStation.GetUpdateQueryString(station.m_name, station.m_setup);
		return Utils::ExecQuery(update);
	}

	return false;
}

void StationsController::ShowObservations(QWidget *parent, const Occupied &station)
{
	QString caption = QString("Observations at %1 setup %2").arg(station.m_name).arg(station.m_setup);
	QString query = QString(ObservationsQueryModel::ModelQueryString).arg(station.m_name).arg(station.m_setup);

	Observation obs;
	obs.m_station = station.m_name;
	obs.m_setup = station.m_setup;

	QSqlDatabase db = QSqlDatabase::database();
	db.transaction();

	TableDlg<Observation, ObservationsQueryModel> dlg(obs, caption, query, parent);

	if (dlg.exec() == QDialog::Accepted)
		db.commit();
	else
		db.rollback();
}
