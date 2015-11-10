#include "stationsquerymodel.h"

const QString StationsQueryModel::ModelQueryString = "SELECT station AS Name, setupno AS Setup, oc AS Correction, insthgt AS `Instr. hgt`, date AS Date FROM occupied ORDER BY station, setupno";

StationsQueryModel::StationsQueryModel(QObject *parent)
	: QSqlQueryModel(parent)
{
}

