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

#include "mockpositionupdater.h"
#include <QTimer>
#include <QDateTime>

MockPositionUpdater::MockPositionUpdater(QObject *parent) : PositionUpdater(parent) {
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, [this]() {
			lastX += delta;
			lastY += delta;
			QGeoCoordinate coord(lastX, lastY);
			QDateTime time = QDateTime::currentDateTime();
			QGeoPositionInfo info(coord, time);
			info.setAttribute(QGeoPositionInfo::HorizontalAccuracy, 1);
			emit newPosition(info);
	});
	timer->start(1000);

}
