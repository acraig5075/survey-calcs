#ifndef CALCSTAB_H
#define CALCSTAB_H

#include <QWidget>

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

public slots:
	void onClear();
	void onLoad();

private slots:
	void on_w_loadButton_clicked();

	void on_w_listView_doubleClicked(const QModelIndex &index);

private:
	Ui::CalcsTab *ui;
	CalcsListModel *m_pModel;
	CalcsController &m_calcsController;
};

#endif // CALCSTAB_H
