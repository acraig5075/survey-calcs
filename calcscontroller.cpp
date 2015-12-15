#include "calcscontroller.h"
#include "calcfactory.h"
#include "calctypes.h"
#include "utils.h"
#include <QSqlQuery>
#include <QDebug>

CalcsController::CalcsController(QObject *parent) : QObject(parent)
{
}

template <typename T>
void CalcsController::ReadCalc()
{
	QSqlQuery query;
	query.prepare(T::SqlSelectQuery);
	if (query.exec())
	{
		while (query.next())
		{
			m_calcList.push_back(std::make_unique<T>(query.record()));
		}
	}
}

void CalcsController::Read()
{
	ReadCalc<JoinsCalc>();
	ReadCalc<PolarsCalc>();
	ReadCalc<DpObsCalc>();

	std::sort(m_calcList.begin(), m_calcList.end(), Calc::SortFunc);
}

QStringList CalcsController::GetDescriptions() const
{
	QStringList descriptions;
	for (const auto &calc: m_calcList)
		descriptions.push_back(calc->desc());
	return descriptions;
}

QString CalcsController::GetDescriptionAt(size_t i) const
{
	if (i < m_calcList.size())
		return m_calcList.at(i)->desc();
	else
		return "";
}

size_t CalcsController::numCalcs() const
{
	return m_calcList.size();
}

void CalcsController::clear()
{
	m_calcList.clear();
}

bool CalcsController::EditCalcAt(size_t i, QWidget *parent)
{
	if (i < m_calcList.size())
	{
		auto &calc = m_calcList.at(i);
		if (calc->Edit(parent))
		{
			QString update = calc->GetUpdateQueryString();
			return Utils::ExecQuery(update);
		}
	}

	return false;
}

template <typename T>
bool CreateTableIfNotExists()
{
	return Utils::ExecQuery(T::SqlCreateQuery);
}

template <typename T>
bool CalcsController::Add(QWidget *parent)
{
	std::unique_ptr<T> calc(new T);

	if (calc->Edit(parent))
	{
		QSqlDatabase db = QSqlDatabase::database();
		db.transaction();
		bool ok;

		ok = CreateTableIfNotExists<T>();

		QSqlQuery query;
		query.prepare("INSERT INTO calcs (`type`) VALUES (:calcType)");
		query.bindValue(":calcType", T::TypeID);
		ok = ok && Utils::ExecQuery(query);

		if (ok)
		{
			int calcref = query.lastInsertId().toInt(&ok);
			if (ok)
				calc->setCalcRef(calcref);
		}

		QString insert = calc->GetInsertQueryString();
		ok = ok && Utils::ExecQuery(insert);

		if (ok)
		{
			db.commit();
			m_calcList.push_back(std::move(calc));
		}
		else
		{
			db.rollback();
		}

		return ok;
	}

	return false;
}

// explicit member function template instantiations
template bool CalcsController::Add<JoinsCalc>(QWidget *parent);
template bool CalcsController::Add<DpObsCalc>(QWidget *parent);
