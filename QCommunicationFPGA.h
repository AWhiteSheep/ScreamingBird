#ifndef QCOMMUNICATIONFPGA_H
#define QCOMMUNICATIONFPGA

#include <QObject>
#include "CommunicationFPGA.h"

class QCommunicationFPGA : public CommunicationFPGA, public QObject
{
	Q_OBJECT
public slots:

};
#endif