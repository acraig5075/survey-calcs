#include "calcslistmodel.h"
#include <QDebug>
#include <QFont>

CalcsListModel::CalcsListModel(QObject *parent)
	: QAbstractListModel(parent)
{}

int CalcsListModel::rowCount(const QModelIndex & parent) const
{
	if (parent.isValid())
		return 0;
	else
		return m_stringList.size();
}

QVariant CalcsListModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == Qt::DisplayRole)
		return static_cast<QVariant>(m_stringList.at(index.row()));
	else if (role == Qt::FontRole)
		return QVariant::fromValue(QFont("Courier", 9, QFont::Normal | QFont::Courier));

	return QVariant();
}

void CalcsListModel::addDesc(const QStringList &descList)
{
	int row = m_stringList.size();
	for (auto desc : descList)
	{
		beginInsertRows(QModelIndex(), row, row);
		m_stringList.push_back(desc);
		endInsertRows();
		++row;
	}
}

void CalcsListModel::clear()
{
	m_stringList.clear();
}

void CalcsListModel::editDesc(int i, const QString &desc)
{
	m_stringList.replace(i, desc);
	emit dataChanged(index(i), index(i));
}
