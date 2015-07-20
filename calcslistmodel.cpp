#include "calcslistmodel.h"
#include <QDebug>

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
	if (role == Qt::DisplayRole)
	{
		if (index.isValid())
			return static_cast<QVariant>(m_stringList.at(index.row()));
	}
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
