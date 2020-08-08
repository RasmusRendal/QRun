#pragma once

#include "runbackend.h"

class Run : public QObject {
	Q_OBJECT
	public:
		Run(RunBackend *parent);
		Run() : QObject(nullptr) {}
		double getDistance();
		int getTime();
	public slots:
		void saveRun();
	private:
		std::vector<QGeoPositionInfo> positions;
		RunBackend *parent;
		double distance = 0;
		QDateTime start;
	private slots:
		void newPosition(const QGeoPositionInfo &info);
	signals:
		void update(double distance, int time, double speed);
};

