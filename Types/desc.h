#ifndef DESC_H
#define DESC_H

#include <QSqlRecord>
#include <QWidget>

class Desc
{
public:
	Desc() = default;

	void SetFrom(const QSqlRecord &record);

	bool Add(QWidget *parent);
	bool Edit(QWidget *parent);
	bool Delete();

	QString m_name;
	QString m_description;
	static const QString SqlCreateQuery;
};

#endif // DESC_H
