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

QString CalcsController::GetDescriptionAt(int i) const
{
	if (i >= 0 && i < m_calcList.size())
		return m_calcList.at(i)->desc();
	else
		return "";
}


bool CalcsController::EditCalcAt(int i, QWidget *parent)
{
	if (i >= 0 && i < m_calcList.size())
	{
		auto &calc = m_calcList.at(i);
		if (calc->Edit(parent))
		{
			QString update = calc->GetUpdateQueryString();
			return Utils::UpdateDatabase(update);
		}
	}

	return false;
}
