#ifndef COORDSTAB_H
#define COORDSTAB_H

#include <QWidget>

class CoordQueryModel;
class CoordsController;

namespace Ui {
class CoordsTab;
}

class CoordsTab : public QWidget
{
	Q_OBJECT

public:
	explicit CoordsTab(CoordsController &coordsController, QWidget *parent = 0);
	~CoordsTab();

	QString GetStatus() const;

public slots:
	void onClear();
	void onLoad();

private slots:
	void on_w_loadButton_clicked();
	void onCustomContextMenuRequested(QPoint pos);
	void onTogglePlot();
	void onDoubleClick(const QModelIndex &index);

signals:
	void coordPlotChanged();

private:
	Ui::CoordsTab *ui;
	CoordQueryModel *m_pModel;
	CoordsController &m_coordsController;
};

#endif // COORDSTAB_H
