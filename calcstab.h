#ifndef CALCSTAB_H
#define CALCSTAB_H

#include <QWidget>
#include <Types/calc.h>

class CalcsListModel;
class CalcsController;

namespace Ui {
class CalcsTab;
}

class CalcsTab : public QWidget
{
	Q_OBJECT

public:
	explicit CalcsTab(CalcsController &calcsController, QWidget *parent = 0);
	~CalcsTab();

	QString GetStatus() const;

private:
	template <typename T>
	void Add(QWidget *parent);

public slots:
	void onClear();
	void onLoad();

signals:
	void calcsCountChanged();

private slots:
	void on_w_listView_doubleClicked(const QModelIndex &index);
	void onAddJoin();
	void onAddDPolar();

private:
	Ui::CalcsTab *ui;
	CalcsListModel *m_pModel;
	CalcsController &m_calcsController;
};

#endif // CALCSTAB_H
