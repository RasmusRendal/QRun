#include "run.h"
#include <QDir>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>

Run::Run(RunBackend *parent) : QObject(parent), parent(parent) {
	connect(parent->getUpdater(), &PositionUpdater::newPosition, this, &Run::newPosition);
}

void Run::newPosition(const QGeoPositionInfo &info) {
	// Ignore inaccurate data
	if (!info.hasAttribute(QGeoPositionInfo::HorizontalAccuracy) || info.attribute(QGeoPositionInfo::HorizontalAccuracy) > 10) {
		qDebug() << "Ignored accuracy " << info.attribute(QGeoPositionInfo::HorizontalAccuracy);
		return;
	}

	positions.push_back(QGeoPositionInfo(info));
	if (positions.size() > 2) {
		const QGeoPositionInfo &last = positions[positions.size()-2];
		double extraDistance = info.coordinate().distanceTo(last.coordinate());
		distance += extraDistance;

		double extraTime = last.timestamp().msecsTo(info.timestamp());
		double speed = 3600 * extraDistance / extraTime;

		emit update(distance, getTime(), speed);
	} else {
		start = info.timestamp();
	}
}

double Run::getDistance() {
	return distance;
}

int Run::getTime() {
	auto lastTimestamp = positions.back().timestamp();
	return start.secsTo(lastTimestamp);
}

void Run::saveRun() {
	const QString tracksDir = QDir::homePath() + "/QRun Tracks/";
	if (!QDir(tracksDir).exists()) {
		QDir().mkdir(tracksDir);
	}
	QFile file(tracksDir + start.toString(Qt::DateFormat::ISODate) + ".gpx");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		throw std::runtime_error("Could not write to file");
	}
	QTextStream in(&file);
	in << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<gpx version=\"1.0\">\n<trk><name>Run</name><number>1</number><trkseg>\n";
	for (const auto &loc : positions) {
		const auto &coord = loc.coordinate();
		in << "<trkpt lat=\""
			<< QString::number(coord.latitude(), 'f', 8)
			<< "\" lon=\""
			<< QString::number(coord.longitude(), 'f', 8)
			<< "\">";

		in << "<time>"
			<< loc.timestamp().toString(Qt::DateFormat::ISODate)
			<< "</time>";
		in << "<accuracy>"
			<< loc.attribute(QGeoPositionInfo::HorizontalAccuracy)
			<< "</accuracy>";
		in <<"</trkpt>\n";
	}
	in << "</trkseg></trk>\n</gpx>\n";
	file.close();
	disconnect(parent->getUpdater(), &PositionUpdater::newPosition, this, &Run::newPosition);
}
