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

#include "runbackend.h"
#include <QDebug>
#include "mockpositionupdater.h"
#include "run.h"

RunBackend::RunBackend(QObject *parent) : QObject(parent) {
	if (false) {
		updater = new PositionUpdater(this);
	} else {
		updater = new MockPositionUpdater(this);
	}
	connect(updater, &PositionUpdater::newPosition, this, &RunBackend::positionReceived);
}

PositionUpdater *RunBackend::getUpdater() {
	return updater;
}

void RunBackend::positionReceived(const QGeoPositionInfo &info) {
	if (info.hasAttribute(QGeoPositionInfo::HorizontalAccuracy)) {
		emit ready(info.attribute(QGeoPositionInfo::HorizontalAccuracy) <= 1, info.attribute(QGeoPositionInfo::HorizontalAccuracy));
	} else {
		emit ready(false, -1);
	}
}

Run *RunBackend::startRun() {
	return new Run(this);
}
