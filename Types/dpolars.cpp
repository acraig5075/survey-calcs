#include "utils.h"
#include "Types/dpolars.h"
#include "Dialogs/doublepolardlg.h"
#include <QVariant>

DpObsCalc::DpObsCalc(const QSqlRecord &record)
{
	m_calcref = record.value("calcref").toInt();
	m_obs[0].m_target = record.value("trg1").toString();
	m_obs[0].m_dirc = record.value("dir1").toDouble();
	m_obs[0].m_vert = record.value("ver1").toDouble();
	m_obs[0].m_dist = record.value("dis1").toDouble();
	m_y1 = record.value("y1").toDouble();
	m_x1 = record.value("x1").toDouble();
	m_obs[1].m_target = record.value("trg2").toString();
	m_obs[1].m_dirc = record.value("dir2").toDouble();
	m_obs[1].m_vert = record.value("ver2").toDouble();
	m_obs[1].m_dist = record.value("dis2").toDouble();
	m_y2 = record.value("y2").toDouble();
	m_x2 = record.value("x2").toDouble();
	m_aname = record.value("aname").toString();
	m_ay = record.value("ay").toDouble();
	m_ax = record.value("ax").toDouble();
	m_adopt = record.value("adopt").toString();
	m_stn[0].m_name = record.value("from1").toString();
	m_stn[0].m_setup = record.value("setup1").toInt();
	m_fy1 = record.value("fy1").toDouble();
	m_fx1 = record.value("fx1").toDouble();
	m_fy2 = record.value("fy2").toDouble();
	m_fx2 = record.value("fx2").toDouble();
	m_stn[1].m_name = record.value("from2").toString();
	m_stn[1].m_setup = record.value("setup1").toInt();
	m_stn[0].m_oc = record.value("oc1").toDouble();
	m_stn[1].m_oc = record.value("oc2").toDouble();
}

QString DpObsCalc::desc() const
{
	auto label1 = QString("\tFrom 1:\t%1\t%2\t%3")
			.arg(m_stn[0].m_name)
			.arg(m_fy1, 0, 'f', 2)
			.arg(m_fx1, 0, 'f', 2);
	auto label2 = QString("\t\t\t%1\t%2")
			.arg(m_obs[0].m_dist, 0, 'f', 2)
			.arg(Utils::Rad2Dms(m_obs[0].m_dirc));
	auto label3 = QString("\t(1)\t\t%1\t%2")
			.arg(m_y1, 0, 'f', 2)
			.arg(m_x1, 0, 'f', 2);
	auto label4 = QString("\tFrom 2:\t%1\t%2\t%3")
			.arg(m_stn[1].m_name)
			.arg(m_fy2, 0, 'f', 2)
			.arg(m_fx2, 0, 'f', 2);
	auto label5 = QString("\t\t\t%1\t%2")
			.arg(m_obs[1].m_dist, 0, 'f', 2)
			.arg(Utils::Rad2Dms(m_obs[1].m_dirc));
	auto label6 = QString("\t(2)\t\t%1\t%2")
			.arg(m_y2, 0, 'f', 2)
			.arg(m_x2, 0, 'f', 2);
	auto label7 = QString("\tAdopt (%1):\t%2\t%3\t%4")
			.arg(m_adopt)
			.arg(m_aname)
			.arg(m_ay, 0, 'f', 2)
			.arg(m_ax, 0, 'f', 2);
	return QString("Double Polar\n%1\n%2\n%3\n%4\n%5\n%6\n%7")
			.arg(label1, label2, label4, label5, label3, label6, label7);
}

bool DpObsCalc::Edit(QWidget *parent)
{
	return Utils::EditDialog<DoublePolarDlg>(parent, *this);
}

