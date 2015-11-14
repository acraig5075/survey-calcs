#include "Types/polars.h"
#include "utils.h"
#include <QVariant>

PolarsCalc::PolarsCalc(const QSqlRecord &record)
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
	m_oc = record.value("oc").toDouble();
}

QString PolarsCalc::desc() const
{
	auto label1 = QString("\tFrom:\t%1\t%2\t%3")
			.arg(m_fromname)
			.arg(m_fy, 0, 'f', 2)
			.arg(m_fx, 0, 'f', 2);
	auto label2 = QString("\t     \t  \t%1\t%2")
			.arg(m_dist, 0, 'f', 2)
			.arg(Utils::Rad2Dms(m_dirc));
	auto label3 = QString("\tTo:\t%1\t%2\t%3")
			.arg(m_toname)
			.arg(m_ty, 0, 'f', 2)
			.arg(m_tx, 0, 'f', 2);
	return QString("Polar\n%1\n%2\n%3").arg(label1, label2, label3);
}

