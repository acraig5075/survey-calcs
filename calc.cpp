#include "calc.h"
#include "utils.h"
#include "Dialogs/editjoindlg.h"
#include <QVariant>

const QString JoinsCalc::SqlSelectQuery = "SELECT calcref, fromname, fy, fx, toname, ty, tx, dirc, dist FROM joins ORDER BY calcref";
const QString PolarsCalc::SqlSelectQuery = "SELECT calcref, fromname, fy, fx, toname, ty, tx, dirc, dist, oc FROM polars ORDER BY calcref";

Calc::Calc()
{
}

bool Calc::SortFunc(CalcPtr const& a, CalcPtr const& b)
{
	return a->m_calcref < b->m_calcref;
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
	auto label1 = QString("\tFrom:\t%1\t%2\t%3")
			.arg(m_fromname)
			.arg(m_fy, 0, 'f', 2)
			.arg(m_fx, 0, 'f', 2);
	auto label2 = QString("\tTo:\t%1\t%2\t%3")
			.arg(m_toname)
			.arg(m_ty, 0, 'f', 2)
			.arg(m_tx, 0, 'f', 2);
	auto label3 = QString("\t\t\t%1\t%2")
			.arg(m_dist, 0, 'f', 2)
			.arg(Utils::Rad2Dms(m_dirc));
	return QString("Join\n%1\n%2\n%3").arg(label1, label2, label3);
}

bool JoinsCalc::Edit(QWidget *parent)
{
	JoinsCalc localCopy = *this;
	EditJoinDlg dlg(parent, localCopy);
	if (dlg.exec() == QDialog::Accepted)
	{
		*this = localCopy;
		return true;
	}

	return false;
}

QString JoinsCalc::GetUpdateQueryString() const
{
	return QString("UPDATE joins SET `fromname`='%1', `fy`=%2, `fx`=%3, `toname`='%4', `ty`=%5, `tx`=%6, `dirc`=%7, `dist`='%8' WHERE `calcref`='%9'")
			.arg(m_fromname)
			.arg(QString::number(m_fy, 'f', 6))
			.arg(QString::number(m_fx, 'f', 6))
			.arg(m_toname)
			.arg(QString::number(m_ty, 'f', 6))
			.arg(QString::number(m_tx, 'f', 6))
			.arg(m_dirc)
			.arg(m_dist)
			.arg(m_calcref);
}

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
