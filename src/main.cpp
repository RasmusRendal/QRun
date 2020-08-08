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

#include <QGuiApplication>
#include <QCoreApplication>
#include <QUrl>
#include <QString>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include "runbackend.h"
#include <QQmlEngine>
#include <QJSEngine>
#include <QList>
#include "run.h"

int main(int argc, char *argv[])
{
	QGuiApplication *app = new QGuiApplication(argc, (char**)argv);
	app->setApplicationName("qrun.rend.al");

	qmlRegisterType<Run>("al.rend.runbackend", 1, 0, "Run");
	qmlRegisterSingletonType<RunBackend>("al.rend.runbackend", 1, 0, "RunBackend", [](QQmlEngine*, QJSEngine*) -> QObject * {
			return new RunBackend();
			});

	QQmlApplicationEngine engine("qrc:/qml/Main.qml");

	return app->exec();
}
