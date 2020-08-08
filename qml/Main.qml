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

ApplicationWindow {
	id: root
	objectName: 'mainView'
	title: "QRun"
	visible: true
	StackView {
		id: stack
		anchors.fill: parent
		initialItem: startColumn

		ColumnLayout {
			id: startColumn
			Layout.fillHeight: true
			width: parent.width
			Layout.alignment: Qt.AlignVCenter
			Layout.topMargin: 25

			Label {
				id: accuracyLabel
				text: "Waiting for accurate position"
				horizontalAlignment: Text.AlignHCenter
				Layout.preferredWidth: parent.width
				Layout.preferredHeight: 25
			}
			Button {
				text: "Start Run"
				id: startRunButton
				enabled: false
				onClicked: {
					var component = Qt.createComponent("Running.qml");
					var window = component.createObject(root);
					window.done.connect(closeShit);
					stack.push(window);
					//window.show();
				}
			}
		}
	}

	function closeShit() {
		stack.pop();
	}

	Connections {
		target: RunBackend
		onReady: {
			if (ready) {
				accuracyLabel.text = "Ready!";
			} else {
				if (accuracy != -1) {
					accuracyLabel.text = "Waiting for accurate position (Current accuracy: " + accuracy + " m)";
				} else {
					accuracyLabel.text = "Waiting for accurate position";
				}
			}
			startRunButton.enabled = ready;
		}
	}

}
