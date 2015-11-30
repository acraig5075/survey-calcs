#ifndef COORDSTAB_H
#define COORDSTAB_H

#include <QWidget>
#include <functional>

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
	void onDelete();
	void onDoubleClick(const QModelIndex &index);

	void on_addButton_clicked();

signals:
	void coordPlotChanged();
	void coordCountChanged();

private:
	Ui::CoordsTab *ui;
	CoordQueryModel *m_pModel;
	CoordsController &m_coordsController;

	void OperateOnSelection(std::function<QString(const QStringList &)> operationQuery, const QString &confirmMsg = "");

};

#endif // COORDSTAB_H
