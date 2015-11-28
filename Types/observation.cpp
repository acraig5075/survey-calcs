#include "observation.h"
#include "utils.h"
#include "Dialogs/obsdlg.h"
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


Observation::Observation(const QSqlRecord &record)
{
	// Remove() is relying on this not setting station or setup.
	m_target = record.value("target").toString();
	m_dirc = record.value("dirc").toDouble();
	m_vert = record.value("vert").toDouble();
	m_dist = record.value("dist").toDouble();
	m_desc = record.value("desc").toString();
	m_prismHgt = record.value("prismhgt").toDouble();
}

void Observation::SetFrom(const QSqlRecord &record)
{
	Observation rhs(record);
	m_target = rhs.m_target;
	m_dirc = rhs.m_dirc;
	m_vert = rhs.m_vert;
	m_dist = rhs.m_dist;
	m_desc = rhs.m_desc;
	m_prismHgt = rhs.m_prismHgt;
}

bool Observation::Add(QWidget *parent)
{
	Observation original = *this;

	ObsDlg *dlg = new ObsDlg(parent, original);
	if (dlg->exec() == QDialog::Accepted)
	{
		*this = original;

		AddDescIfNotExist();

		QSqlQuery query;
		query.prepare("INSERT INTO obs (station, setup, target, dirc, vert, dist, desc, prismhgt) "
					  "VALUES (:station, :setup, :target, :dirc, :vert, :dist, :desc, :prismhgt)");

		query.bindValue(":station", m_station);
		query.bindValue(":setup", m_setup);
		query.bindValue(":target", m_target);
		query.bindValue(":dirc", m_dirc);
		query.bindValue(":vert", m_vert);
		query.bindValue(":dist", m_dist);
		query.bindValue(":desc", m_desc);
		query.bindValue(":prismhgt", m_prismHgt);

		return Utils::ExecQuery(query);
	}

	return false;
}

bool Observation::Edit(QWidget *parent)
{
	double radians = Utils::Dms2Rad("210.4059");
	QString dms = Utils::Rad2Dms(radians, ':');

	radians = Utils::Dms2Rad("89.3359");
	dms = Utils::Rad2Dms(radians, ':');

	radians = Utils::Dms2Rad("89.3959");
	dms = Utils::Rad2Dms(radians, ':');

	radians = Utils::Dms2Rad("89.3900");
	dms = Utils::Rad2Dms(radians, ':');

	radians = Utils::Dms2Rad("89.3901");
	dms = Utils::Rad2Dms(radians, ':');

	radians = Utils::Dms2Rad("89.0001");
	dms = Utils::Rad2Dms(radians, ':');

	radians = Utils::Dms2Rad("89.0000");
	dms = Utils::Rad2Dms(radians, ':');

	radians = Utils::Dms2Rad("89.0100");
	dms = Utils::Rad2Dms(radians, ':');

	Observation original = *this;

	ObsDlg *dlg = new ObsDlg(parent, original);
	if (dlg->exec() == QDialog::Accepted)
	{
		*this = original;

		AddDescIfNotExist();

		QSqlQuery query;
		query.prepare("UPDATE obs "
					  "SET target = :target"
					  ", dirc = :dirc"
					  ", vert = :vert"
					  ", dist = :dist"
					  ", prismHgt = :prismhgt"
					  ", desc = :desc"
					  " WHERE station = :station AND setup = :setup AND target = :target0");

		query.bindValue(":target", m_target);
		query.bindValue(":dirc", m_dirc);
		query.bindValue(":vert", m_vert);
		query.bindValue(":dist", m_dist);
		query.bindValue(":prismhgt", m_prismHgt);
		query.bindValue(":desc", m_desc);
		query.bindValue(":station", original.m_station);
		query.bindValue(":setup", original.m_setup);
		query.bindValue(":target0", original.m_target);

		return Utils::ExecQuery(query);
	}

	return false;
}

bool Observation::Delete()
{
	QSqlQuery query;
	query.prepare("DELETE FROM obs "
				  "WHERE station = :station"
				  " AND setup = :setup"
				  " AND target = :target");

	query.bindValue(":station", m_station);
	query.bindValue(":setup", m_setup);
	query.bindValue(":target", m_target);

	return Utils::ExecQuery(query);
}

void Observation::AddDescIfNotExist()
{
	QSqlQuery query;
	query.prepare("INSERT INTO desc (desc) VALUES(:desc)");
	query.bindValue(":desc", m_desc);

	Utils::ExecQuery(query);
}
