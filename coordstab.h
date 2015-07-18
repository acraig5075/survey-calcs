#ifndef COORDSTAB_H
#define COORDSTAB_H

#include <QWidget>

class CoordQueryModel;

namespace Ui {
class CoordsTab;
}

class CoordsTab : public QWidget
{
	Q_OBJECT

public:
	explicit CoordsTab(QWidget *parent = 0);
	~CoordsTab();

	QString GetStatus() const;

public slots:
	void onClear();
	void onLoad();

private slots:
	void on_w_loadButton_clicked();
	void onCustomContextMenuRequested(QPoint pos);
	void onTogglePlot();

signals:
	void coordPlotChanged();

private:
	Ui::CoordsTab *ui;
	CoordQueryModel *m_pModel;
};

#endif // COORDSTAB_H
