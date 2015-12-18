#include "ComPort.h"

#include "SignalSet.h"



























ComPort::ComPort()
	: m_pConnectedSignalList(nullptr)
	, m_connectedIndex(0)
	, m_assignedCount(0)
{

}


ComPort::~ComPort()
{

}

//////////////////////////////////////////////////////////////////

int ComPort::connect(std::shared_ptr<SignalSet> pSignalList,
	size_t index, size_t count)
{
	m_pConnectedSignalList = pSignalList;
	m_connectedIndex = index;
	m_assignedCount = count;


	return 0;
}

//////////////////////////////////////////////////////////////////

double ComPort::getSignal(size_t index) const
{
	return m_pConnectedSignalList->getSignalAt(m_connectedIndex + index);
}


void ComPort::setSignal(size_t index, double signal)
{
	m_pConnectedSignalList->setSignalAt(m_connectedIndex + index, signal);
}

//---------------------------------------------------------------

std::shared_ptr<SignalSet> ComPort::getSignalList() const
{
	std::shared_ptr<SignalSet> pSet(new SignalSet(m_assignedCount));
	
	for (size_t i = 0; i < m_assignedCount; ++i)
	{
		pSet->setSignalAt(0, this->getSignal(i));
	}


	return pSet;
}

