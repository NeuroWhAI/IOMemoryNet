#include "MemoryCell.h"

#include "SignalSet.h"
#include "ConditionScore.h"

using SignalSetPtr = MemoryCell::SignalSetPtr;
using ConditionScorePtr = MemoryCell::ConditionScorePtr;



























MemoryCell::MemoryCell()
	: m_pInSignalSet(new SignalSet())
	, m_pOutSignalSet(new SignalSet())
	, m_pConditionScore(new ConditionScore())
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

//---------------------------------------------------------------

int MemoryCell::setConditionScore(const ConditionScore& score)
{
	*m_pConditionScore = score;


	return 0;
}


int MemoryCell::addConditionScore(const ConditionScore& score, double weight)
{
	m_pConditionScore->addConditionScore(score, weight);


	return 0;
}


const ConditionScore& MemoryCell::getConditionScore() const
{
	return *m_pConditionScore;
}

