#include "calc.h"
#include <QVariant>

const QString JoinsCalc::SqlSelectQuery = "SELECT calcref, fromname, fy, fx, toname, ty, tx, dirc, dist FROM joins ORDER BY calcref";

Calc::Calc()
{
}

JoinsCalc::JoinsCalc(const QSqlRecord &record)
{
	m_calcref = record.value("calcref").toInt();
	m_fromname = record.value("fromname").toString();
	m_toname = record.value("toname").toString();
	m_fy = record.value("fy").toDouble();
	m_fx = record.value("fx").toDouble();
	m_ty = record.value("ty").toDouble();
	m_tx = record.value("tx").toDouble();
	m_dirc = record.value("dirc").toDouble();
	m_dist = record.value("dist").toDouble();
}

QString JoinsCalc::desc() const
{
	auto label1 = QString("\tFrom:\t%1\t%2\t%3").arg(m_fromname).arg(m_fy, 0, 'f', 2).arg(m_fx, 0, 'f', 2);
	auto label2 = QString("\tTo:\t%1\t%2\t%3").arg(m_toname).arg(m_ty, 0, 'f', 2).arg(m_tx, 0, 'f', 2);
	auto label3 = QString("\t\t\t%1\t%2").arg(m_dist, 0, 'f', 2).arg(m_dirc, 0, 'f', 4);
	return QString("Join\n%1\n%2\n%3").arg(label1, label2, label3);
}
