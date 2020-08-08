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

import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0
import al.rend.runbackend 1.0



ColumnLayout {
	property var myRun: RunBackend.startRun()
	id: root
	signal done()
	Connections {
		target: myRun
		onUpdate: {
			distanceLabel.text = "Distance: " + distance.toFixed(1) + " m"
			timeLabel.text = "Time: " + time
			speedLabel.text = "Speed: " + speed.toFixed(1) + " km/h"
		}
	}

	RowLayout {
		Layout.preferredHeight:  parent.height
		width: parent.width

		Row {
			Label {
				id: distanceLabel
				text: "Distance: 0m"
				horizontalAlignment: Text.AlignHCenter
				Layout.preferredWidth: parent.width
				Layout.preferredHeight: 25
			}
		}
		Row {
			Label {
				id: timeLabel
				text: "Time: 0 s"
				horizontalAlignment: Text.AlignHCenter
				Layout.preferredWidth: parent.width
				Layout.preferredHeight: 25
			}
		}
		Row {
			Label {
				id: speedLabel
				text: "Speed: 0 km/h"
				horizontalAlignment: Text.AlignHCenter
				Layout.preferredWidth: parent.width
				Layout.preferredHeight: 25
			}
		}
	}
	Row {
		Button {
			text: "Stop Run"
			onClicked: {
				myRun.saveRun();
				root.done()
			}
		}
	}
}
