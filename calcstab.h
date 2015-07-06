#ifndef CALCSTAB_H
#define CALCSTAB_H

#include <QWidget>

class CalcsListModel;

namespace Ui {
class CalcsTab;
}

class CalcsTab : public QWidget
{
	Q_OBJECT

public:
	explicit CalcsTab(QWidget *parent = 0);
	~CalcsTab();

	QString GetStatus() const;

public slots:
	void onClear();
	void onLoad();

private slots:
	void on_w_loadButton_clicked();

private:
	Ui::CalcsTab *ui;
	CalcsListModel *m_pModel;
};

#endif // CALCSTAB_H
