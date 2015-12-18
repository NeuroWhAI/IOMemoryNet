#include "MemoryNet.h"

#include "SignalSet.h"
#include "ComPort.h"


























MemoryNet::MemoryNet()
	: m_pInSignal(new SignalSet())
	, m_pOutSignal(new SignalSet())
{

}


MemoryNet::MemoryNet(size_t inSignalCount, size_t outSignalCount)
	: m_pInSignal(new SignalSet())
	, m_pOutSignal(new SignalSet())
{
	this->init(inSignalCount, outSignalCount);
}


MemoryNet::~MemoryNet()
{

}

//////////////////////////////////////////////////////////////////

int MemoryNet::init(size_t inSignalCount, size_t outSignalCount)
{
	m_pInSignal->init(inSignalCount);
	m_pOutSignal->init(outSignalCount);


	return 0;
}


int MemoryNet::release()
{



	return 0;
}

//---------------------------------------------------------------

int MemoryNet::update()
{
	m_pInSignal->update();
	m_pOutSignal->update();


	return 0;
}

//////////////////////////////////////////////////////////////////

size_t MemoryNet::getInputSize() const
{
	return m_pInSignal->getSignalCount();
}


size_t MemoryNet::getOutputSize() const
{
	return m_pOutSignal->getSignalCount();
}

//---------------------------------------------------------------

const std::shared_ptr<SignalSet> MemoryNet::getInputSet() const
{
	return m_pInSignal;
}


const std::shared_ptr<SignalSet> MemoryNet::getOutputSet() const
{
	return m_pOutSignal;
}

//////////////////////////////////////////////////////////////////

std::shared_ptr<ComPort> MemoryNet::assignComPortAtInput(size_t index, size_t count)
{
	std::shared_ptr<ComPort> pCom(new ComPort());
	pCom->connect(m_pInSignal, index, count);

	m_pComList.emplace_back(pCom);


	return pCom;
}


std::shared_ptr<ComPort> MemoryNet::assignComPortAtOutput(size_t index, size_t count)
{
	std::shared_ptr<ComPort> pCom(new ComPort());
	pCom->connect(m_pOutSignal, index, count);

	m_pComList.emplace_back(pCom);


	return pCom;
}

//---------------------------------------------------------------

int MemoryNet::removeComPort(std::shared_ptr<ComPort> pCom)
{
	const size_t listSize = m_pComList.size();
	for (size_t i = 0; i < listSize; ++i)
	{
		if (m_pComList[i] == pCom)
		{
			m_pComList.erase(m_pComList.begin() + i);


			return 0;
		}
	}


	return -1;
}

