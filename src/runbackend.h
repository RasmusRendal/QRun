#pragma once

#include <QObject>
#include <QVector>
#include <QString>
#include <vector>
#include <QQmlListProperty>
#include <QVariant>
#include "positionupdater.h"

class Run;
class RunBackend : public QObject {
	Q_OBJECT
	public:
		RunBackend(QObject *parent=nullptr);
		PositionUpdater *getUpdater();
	public slots:
		Run *startRun();
	private:
		PositionUpdater *updater;
	private slots:
		void positionReceived(const QGeoPositionInfo &info);
	signals:
		void ready(bool ready, double accuracy);
};
