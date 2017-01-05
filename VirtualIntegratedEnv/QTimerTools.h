#pragma once
#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QTimer>
#include <functional>

class QTimerTools : public QObject
{
	Q_OBJECT
private:
	QTimer* qTimer;
	std::function<void(void)> functor;
public:
	QTimerTools(std::function<void(void)> tf)
	{
		qTimer = new QTimer(this);
		functor = tf;
		connect(qTimer, SIGNAL(timeout()), this, SLOT(qTimeout()));
	}
	~QTimerTools() 
	{
		
	}

	QTimer* getTimer()
	{
		return qTimer;
	}
private slots:
	void qTimeout()
	{
		functor();
	}
};