/* Copyright 2013 Yurii Litvinov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once

#include <QtCore/qglobal.h>

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
	#include <QtGui/QWidget>
	#include <QtGui/QLabel>
#else
	#include <QtWidgets/QWidget>
	#include <QtWidgets/QLabel>
#endif

#include "declSpec.h"

namespace trikControl {

class GuiWorker : public QObject
{
	Q_OBJECT

public:
	GuiWorker();

public slots:
	void showImage(QString const &fileName);
	void deleteWorker();

private:
	QWidget mImageWidget;
	QLabel mImageLabel;
};

}
