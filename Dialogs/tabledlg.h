#ifndef TABLEDLG_H
#define TABLEDLG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlRecord>

namespace Ui {
class TableBaseDlg;
}

class TableBaseDlg : public QDialog
{
	Q_OBJECT

public:
	explicit TableBaseDlg(const QString &caption, const QString &query, bool stretch, QWidget *parent);
	~TableBaseDlg();

private:
	virtual bool AddRow() = 0;
	virtual bool EditRow(QSqlRecord &record) = 0;
	virtual bool DeleteRow(QSqlRecord &record) = 0;

protected:
	Ui::TableBaseDlg *ui;
	QSqlQueryModel *m_pModel = nullptr;
	QString m_query;

private slots:
	void on_addButton_clicked();
	void on_tableView_doubleClicked(const QModelIndex &index);
	void on_tableView_customContextMenuRequested(const QPoint &pos);
	void onDelete();
};

template <typename Type, typename Model>
class TableDlg : public TableBaseDlg
{
public:
	TableDlg(const Type &type, const QString &caption, const QString &query, bool stretch, QWidget *parent);

private:
	virtual bool AddRow() override;
	virtual bool EditRow(QSqlRecord &record) override;
	virtual bool DeleteRow(QSqlRecord &record) override;

private:
	const Type &m_type;
};

#endif // TABLEDLG_H
