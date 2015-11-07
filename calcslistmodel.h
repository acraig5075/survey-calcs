#ifndef CALCLISTMODEL_H
#define CALCLISTMODEL_H

#include <QAbstractListModel>

class CalcsListModel : public QAbstractListModel
{
public:
	CalcsListModel(QObject *parent = 0);

	int rowCount(const QModelIndex & parent = QModelIndex()) const override;

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

	void addDesc(const QStringList &descList);

	void clear();

	void editDesc(int i, const QString &desc);

private:
	QStringList m_stringList;
};

#endif // CALCLISTMODEL_H

