#ifndef SELECTCOORDDLG_H
#define SELECTCOORDDLG_H

#include <QDialog>
#include "ui_selectcoorddlg.h"
#include <QSqlRecord>
#include <QSqlQueryModel>

class QSqlQueryModel;

namespace Ui {
class SelectCoordDlg;
}



class SelectCoordDlg : public QDialog
{
	Q_OBJECT

public:
	SelectCoordDlg(QWidget *parent, const QString &title, bool multiSelection) :
		QDialog(parent),
		ui(new Ui::SelectCoordDlg)
	{
		ui->setupUi(this);

		setWindowTitle(title);

		ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
		if (multiSelection)
			ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
		else
			ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	}

	~SelectCoordDlg()
	{
		delete ui;
	}


private:
	virtual void AddToSelection(const QSqlRecord &record) = 0;
	virtual void ClearSelection() = 0;

private slots:
	void on_SelectCoordDlg_accepted()
	{
		// Get selected point names
		QItemSelectionModel *selection = ui->tableView->selectionModel();
		if (selection)
		{
			QModelIndexList selRows = selection->selectedRows();
			for (QModelIndex index : selRows)
			{
				QSqlRecord record = m_pModel->record(index.row());
				AddToSelection(record);
			}
		}
	}

	void on_SelectCoordDlg_rejected()
	{
		ClearSelection();
	}

protected:
	Ui::SelectCoordDlg *ui;
	QSqlQueryModel *m_pModel = nullptr;
};



template <typename T, typename U>
class SelectionDlg : public SelectCoordDlg
{
public:
	SelectionDlg(QWidget *parent, const QString title, bool multiSelection, const QString &query, const QVector<int> &hiddenColumns)
		: SelectCoordDlg(parent, title, multiSelection)
	{
		m_pModel = new U(this);
		m_pModel->setQuery(query);

		int column = 0;
		for (auto label: U::HorizontalHeaderList)
			m_pModel->setHeaderData(column++, Qt::Horizontal, label);

		ui->tableView->setModel(m_pModel);
		for (auto col: hiddenColumns)
			ui->tableView->setColumnHidden(col, true);
	}

	T GetSingleSelection() const
	{
		if (m_selection.isEmpty())
			return T();
		else
			return m_selection.at(0);
	}

	QVector<T> GetMultiSelection() const
	{
		return m_selection;
	}

private:
	virtual void AddToSelection(const QSqlRecord &record) override
	{
		m_selection.push_back(T(record));
	}

	virtual void ClearSelection() override
	{
		m_selection.clear();
	}

private:
	QVector<T> m_selection;
};

#endif // SELECTCOORDDLG_H
