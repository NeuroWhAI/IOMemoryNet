#include "Component.h"

#include <assert.h>

#include "ComPort.h"

using ComPortPtr = Component::ComPortPtr;



























Component::Component(size_t portSize)
	: m_portSize(portSize)
	
	, m_pComPort(nullptr)
{

}


Component::~Component()
{
	disconnect();
}

//////////////////////////////////////////////////////////////////

int Component::connect(ComPortPtr pComPort)
{
#ifdef _DEBUG
	assert(pComPort && pComPort->getAssignedCount() == m_portSize
		&&
		"Component::connect");
#endif


	disconnect();

	m_pComPort = pComPort;

	// TODO: 연결 작업


	return 0;
}


int Component::disconnect()
{
	if (this->onConnected())
	{
		// TODO: 연결끊기 작업

		m_pComPort = nullptr;


		return 0;
	}


	return 1;
}

//---------------------------------------------------------------

bool Component::onConnected() const
{
	return (m_pComPort != nullptr);
}

//////////////////////////////////////////////////////////////////

double Component::getComSignal(size_t index) const
{
	if (this->onConnected())
	{
		return m_pComPort->getSignal(index);
	}


	return 0.0;
}


void Component::setComSignal(size_t index, double signal)
{
	if (this->onConnected())
	{
		m_pComPort->setSignal(index, signal);
	}
}

//////////////////////////////////////////////////////////////////

const ComPortPtr Component::getComPort() const
{
	return m_pComPort;
}

