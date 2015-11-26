#ifndef TABLEDLG_H
#define TABLEDLG_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class TableBaseDlg;
}

class TableBaseDlg : public QDialog
{
	Q_OBJECT

public:
	explicit TableBaseDlg(const QString &caption, QWidget *parent = 0);
	~TableBaseDlg();

private:
	virtual bool AddRow() = 0;

protected:
	Ui::TableBaseDlg *ui;
	QSqlQueryModel *m_pModel = nullptr;

private slots:
	void on_addButton_clicked();
};

template <typename Type, typename Controller, typename Model>
class TableDlg : public TableBaseDlg
{
public:
	TableDlg(Controller &controller, const QString &caption, const QString &query, QWidget *parent = 0);

private:
	virtual bool AddRow() override;

private:
	Controller &m_controller;
};

#endif // TABLEDLG_H
