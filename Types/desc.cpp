#include "desc.h"
#include "utils.h"
#include "Dialogs/descdlg.h"
#include <QVariant>
#include <QSqlQuery>

const QString Desc::SqlCreateQuery = "CREATE TABLE `desc` ("
		"`desc` VARCHAR(8),"
		"`description` VARCHAR(60),"
		"`select` VARCHAR(1)"
		")";

void Desc::SetFrom(const QSqlRecord &record)
{
	m_name = record.value("desc").toString();
	m_description = record.value("description").toString();
}

bool Desc::Add(QWidget *parent)
{
	Desc original = *this;

	DescDlg *dlg = new DescDlg(parent, original);
	if (dlg->exec() == QDialog::Accepted)
	{
		*this = original;

		QSqlQuery query;
		query.prepare("INSERT INTO desc (desc, description) "
					  "VALUES (:desc, :description)");

		query.bindValue(":desc", m_name);
		query.bindValue(":description", m_description);

		return Utils::ExecQuery(query);
	}

	return false;
}

bool Desc::Edit(QWidget *parent)
{
	Desc original = *this;

	DescDlg *dlg = new DescDlg(parent, original);
	if (dlg->exec() == QDialog::Accepted)
	{
		*this = original;

		QSqlQuery query;
		query.prepare("UPDATE desc "
					  "SET desc = :desc"
					  ", description = :description"
					  " WHERE desc = :desc0");

		query.bindValue(":desc", m_name);
		query.bindValue(":description", m_description);
		query.bindValue(":desc0", original.m_name);

		return Utils::ExecQuery(query);
	}

	return false;
}

bool Desc::Delete()
{
	QSqlQuery query;
	query.prepare("DELETE FROM desc WHERE desc = :desc");
	query.bindValue(":desc", m_name);

	return Utils::ExecQuery(query);
}

