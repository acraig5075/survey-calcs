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
