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

#include "servoMotor.h"

#include <QtCore/QDebug>

using namespace trikControl;

ServoMotor::ServoMotor(int min, int max, int zero, int stop, QString const& deviceFile, bool invert)
	: mControlFile(deviceFile)
	, mMin(min)
	, mMax(max)
	, mZero(zero)
	, mStop(stop)
	, mInvert(invert)
	, mCurrentPower(0)
{
}

void ServoMotor::setPower(int power)
{
	if (!mControlFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Unbuffered | QIODevice::Text)) {
		qDebug() << "Can't open motor control file " << mControlFile.fileName();
		return;
	}

	if (power > 100) {
		power = 100;
	} else if (power < -100) {
		power = -100;
	}

	mCurrentPower = power;

	power = mInvert ? -power : power;

	int const range = power <= 0 ? mZero - mMin : mMax - mZero;
	qreal const powerFactor = static_cast<qreal>(range) / 100;
	QString const command = QString::number(static_cast<int>(mZero + power * powerFactor));

	mControlFile.write(command.toLatin1());
	mControlFile.close();
}

int ServoMotor::power() const
{
	return mCurrentPower;
}

void ServoMotor::powerOff()
{
	if (!mControlFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Unbuffered | QIODevice::Text)) {
		qDebug() << "Can't open motor control file " << mControlFile.fileName();
		return;
	}

	mControlFile.write(QString::number(mStop).toLatin1());
	mControlFile.close();

	mCurrentPower = 0;
}
