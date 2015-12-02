#ifndef STATIONSTAB_H
#define STATIONSTAB_H

#include <QWidget>

class StationsQueryModel;
class StationsController;

namespace Ui {
class StationsTab;
}

class StationsTab : public QWidget
{
	Q_OBJECT

public:
	explicit StationsTab(StationsController &controller, QWidget *parent = 0);
	~StationsTab();

	QString GetStatus() const;

private slots:
	void onClear();
	void onLoad();
	void on_obsButton_clicked();
	void on_addButton_clicked();

signals:
	void stationCountChanged();

public slots:
	void on_w_loadButton_clicked();
	void onDoubleClick(const QModelIndex &index);

private:
	Ui::StationsTab *ui;
	StationsQueryModel *m_pModel;
	StationsController &m_stationsController;
};

#endif // STATIONSTAB_H
