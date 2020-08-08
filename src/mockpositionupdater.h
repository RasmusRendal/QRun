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

#pragma once

#include "positionupdater.h"
#include <QGeoPositionInfo>

class MockPositionUpdater : public PositionUpdater {
	Q_OBJECT
	public:
		MockPositionUpdater(QObject *parent = 0);
	private:
		double lastX = 20;
		double lastY = 20;
		double delta = 0.00001;
		int runs = 0;
};
