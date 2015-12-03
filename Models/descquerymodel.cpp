#include "descquerymodel.h"

const QString DescQueryModel::ModelQueryString = "SELECT desc, description FROM desc ORDER BY desc";

const QStringList DescQueryModel::HorizontalHeaderList = QStringList() << "Code" << "Description";

DescQueryModel::DescQueryModel(QObject *parent)
	: QSqlQueryModel(parent)
{
}

