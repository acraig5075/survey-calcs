#include "calc.h"
#include "utils.h"
#include "Dialogs/editjoindlg.h"
#include "Dialogs/doublepolardlg.h"
#include <QVariant>

const QString JoinsCalc::SqlSelectQuery = "SELECT calcref, fromname, fy, fx, toname, ty, tx, dirc, dist FROM joins ORDER BY calcref";
const QString PolarsCalc::SqlSelectQuery = "SELECT calcref, fromname, fy, fx, toname, ty, tx, dirc, dist, oc FROM polars ORDER BY calcref";
const QString DpObsCalc::SqlSelectQuery = "SELECT dpobs.calcref, dpobs.trg1, dpobs.dir1, dpobs.ver1, dpobs.dis1, dpobs.y1, dpobs.x1, dpobs.trg2, dpobs.dir2, dpobs.ver2, dpobs.dis2, dpobs.y2, dpobs.x2, dpobs.aname, dpobs.ay, dpobs.ax, dpobs.adopt, dpstns.from1, dpstns.fy1, dpstns.fx1, dpstns.from2, dpstns.fy2, dpstns.fx2, dpstns.oc1, dpstns.oc2 FROM dpobs JOIN dpstns ON dpobs.calcref = dpstns.calcref ORDER BY dpobs.calcref";

Calc::Calc()
{
}

bool Calc::SortFunc(CalcPtr const& a, CalcPtr const& b)
{
	return a->m_calcref < b->m_calcref;
}

template <typename TDlg, typename TCalc>
bool EditDialog(QWidget *parent, TCalc &calc)
{
	TCalc localCopy = calc;
	TDlg dlg(parent, localCopy);
	if (dlg.exec() == QDialog::Accepted)
	{
		calc = localCopy;
		return true;
	}

	return false;
}

DpObsCalc::DpObsCalc(const QSqlRecord &record)
{
	m_calcref = record.value("calcref").toInt();
	m_trg1 = record.value("trg1").toString();
	m_dir1 = record.value("dir1").toDouble();
	m_ver1 = record.value("ver1").toDouble();
	m_dis1 = record.value("dis1").toDouble();
	m_y1 = record.value("y1").toDouble();
	m_x1 = record.value("x1").toDouble();
	m_trg2 = record.value("trg2").toString();
	m_dir2 = record.value("dir2").toDouble();
	m_ver2 = record.value("ver2").toDouble();
	m_dis2 = record.value("dis2").toDouble();
	m_y2 = record.value("y2").toDouble();
	m_x2 = record.value("x2").toDouble();
	m_aname = record.value("aname").toString();
	m_ay = record.value("ay").toDouble();
	m_ax = record.value("ax").toDouble();
	m_adopt = record.value("adopt").toString();
	m_from1 = record.value("from1").toString();
	m_fy1 = record.value("fy1").toDouble();
	m_fx1 = record.value("fx1").toDouble();
	m_from2 = record.value("from2").toString();
	m_fy2 = record.value("fy2").toDouble();
	m_fx2 = record.value("fx2").toDouble();
	m_oc1 = record.value("oc1").toDouble();
	m_oc2 = record.value("oc2").toDouble();
}

QString DpObsCalc::desc() const
{
	auto label1 = QString("\tFrom 1:\t%1\t%2\t%3")
			.arg(m_from1)
			.arg(m_fy1, 0, 'f', 2)
			.arg(m_fx1, 0, 'f', 2);
	auto label2 = QString("\t\t\t%1\t%2")
			.arg(m_dis1, 0, 'f', 2)
			.arg(Utils::Rad2Dms(m_dir1));
	auto label3 = QString("\tTarget 1:\t\t%1\t%2")
			.arg(m_y1, 0, 'f', 2)
			.arg(m_x1, 0, 'f', 2);
	auto label4 = QString("\tFrom 2:\t%1\t%2\t%3")
			.arg(m_from2)
			.arg(m_fy2, 0, 'f', 2)
			.arg(m_fx2, 0, 'f', 2);
	auto label5 = QString("\t\t\t%1\t%2")
			.arg(m_dis2, 0, 'f', 2)
			.arg(Utils::Rad2Dms(m_dir2));
	auto label6 = QString("\tTarget 2:\t\t%1\t%2")
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
	return EditDialog<DoublePolarDlg>(parent, *this);
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
//	JoinsCalc localCopy = *this;
//	EditJoinDlg dlg(parent, localCopy);
//	if (dlg.exec() == QDialog::Accepted)
//	{
//		*this = localCopy;
//		return true;
//	}

//	return false;
	return EditDialog<EditJoinDlg>(parent, *this);
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
