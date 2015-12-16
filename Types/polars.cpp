#include "Types/polars.h"
#include "utils.h"
#include "Dialogs/polardlg.h"
#include <QVariant>

const QString PolarsCalc::SqlCreateQuery = "CREATE TABLE IF NOT EXISTS `polars` ("
		"`calcref` BIGINT, "
		"`fromname` VARCHAR(8), "
		"`setup` SMALLINT, "
		"`fy` FLOAT, "
		"`fx` FLOAT, "
		"`toname` VARCHAR(8), "
		"`dirc` FLOAT, "
		"`dist` FLOAT, "
		"`ty` FLOAT, "
		"`tx` FLOAT, "
		"`fbp` SMALLINT, "
		"`rdirc` FLOAT, "
		"`rvert` FLOAT, "
		"`rdist` FLOAT, "
		"`oc` FLOAT, "
		"`zero` SMALLINT, "
		"`scale` SMALLINT, "
		"`hamsl` SMALLINT, "
		"`proj` VARCHAR(1), "
		"`edmoffset` SMALLINT, "
		"`prismoffset` SMALLINT "
		")";

PolarsCalc::PolarsCalc(const QSqlRecord &record)
{
	m_calcref = record.value("calcref").toInt();
	m_obs.m_station = record.value("fromname").toString();
	m_obs.m_target = record.value("toname").toString();
	m_fy = record.value("fy").toDouble();
	m_fx = record.value("fx").toDouble();
	m_ty = record.value("ty").toDouble();
	m_tx = record.value("tx").toDouble();
	m_obs.m_dirc = record.value("dirc").toDouble();
	m_obs.m_dist = record.value("dist").toDouble();
	m_stn.m_oc = record.value("oc").toDouble();
	m_stn.m_name = m_obs.m_station;
}

QString PolarsCalc::desc() const
{
	auto label1 = QString("\tFrom:\t%1\t%2\t%3")
			.arg(m_stn.m_name)
			.arg(m_fy, 0, 'f', 2)
			.arg(m_fx, 0, 'f', 2);
	auto label2 = QString("\t     \t  \t%1\t%2")
			.arg(m_obs.m_dist, 0, 'f', 2)
			.arg(Utils::Rad2Dms(m_obs.m_dirc, ':'));
	auto label3 = QString("\tTo:\t%1\t%2\t%3")
			.arg(m_obs.m_target)
			.arg(m_ty, 0, 'f', 2)
			.arg(m_tx, 0, 'f', 2);
	return QString("Polar\n%1\n%2\n%3").arg(label1, label2, label3);
}

bool PolarsCalc::Edit(QWidget *parent)
{
	return Utils::EditDialog<PolarDlg>(parent, *this);
}

QString PolarsCalc::GetUpdateQueryString() const
{
	return QString("UPDATE `polars` SET `fromname`='%1', `setup`=%2, `fy`=%3, `fx`=%4, `toname`='%4', `dirc`=%5, `dist`=%6, `ty`=%7, `tx`=%8 WHERE `calcref`='%9'")
			.arg(m_stn.m_name)
			.arg(QString::number(m_stn.m_setup))
			.arg(QString::number(m_fy, 'f', 6))
			.arg(QString::number(m_fx, 'f', 6))
			.arg(m_obs.m_target)
			.arg(QString::number(m_obs.m_dirc))
			.arg(QString::number(m_obs.m_dist))
			.arg(QString::number(m_ty, 'f', 6))
			.arg(QString::number(m_tx, 'f', 6))
			.arg(m_calcref);
}

QString PolarsCalc::GetInsertQueryString() const
{
	return "";
}
