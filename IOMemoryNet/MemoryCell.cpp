#include "MemoryCell.h"

#include "SignalSet.h"

using SignalSetPtr = MemoryCell::SignalSetPtr;



























MemoryCell::MemoryCell()
	: m_pInSignalSet(new SignalSet())
	, m_pOutSignalSet(new SignalSet())
{

}


MemoryCell::~MemoryCell()
{

}

////////////////////////////////////////////////////////////////////

int MemoryCell::update()
{
	Cell::update();


	if (this->isActivated())
	{
		whenMemoryActivatedFunc(*this);
	}


	return 0;
}

////////////////////////////////////////////////////////////////////

int MemoryCell::setMemoryActivationCallback(std::function<int(MemoryCell&)> func)
{
	whenMemoryActivatedFunc = func;


	return 0;
}

//---------------------------------------------------------------

int MemoryCell::setOutSignalCount(size_t signalCount)
{
	m_pOutSignalSet->init(signalCount);


	return 0;
}

//---------------------------------------------------------------

int MemoryCell::setInSignalSet(const SignalSetPtr& inSignalSet)
{
	m_pInSignalSet->copyFrom(*inSignalSet);


	return 0;
}


int MemoryCell::setOutSignalSet(const SignalSetPtr& outSignalSet)
{
	m_pOutSignalSet->copyFrom(*outSignalSet);


	return 0;
}

//---------------------------------------------------------------

SignalSetPtr MemoryCell::getInSignalSet()
{
	return m_pInSignalSet;
}


SignalSetPtr MemoryCell::getOutSignalSet()
{
	return m_pOutSignalSet;
}

