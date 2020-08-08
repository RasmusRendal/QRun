/*
 * Copyright (C) 2020  Rasmus Rendal
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * qRun is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "positionupdater.h"
#include <QDebug>

PositionUpdater::PositionUpdater(QObject *parent) : QObject(parent) {
	QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);
	if (source) {
		source->setUpdateInterval(1000);
		source->setPreferredPositioningMethods(QGeoPositionInfoSource::AllPositioningMethods);
		connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
				this, SLOT(positionUpdated(QGeoPositionInfo)));
		source->startUpdates();
	}
}

void PositionUpdater::positionUpdated(const QGeoPositionInfo &info) {
	qDebug() << "Position updated:" << info;
	emit newPosition(info);
}
