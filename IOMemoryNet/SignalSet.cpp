#include "SignalSet.h"

#include <numeric>


























SignalSet::SignalSet()
{

}


SignalSet::SignalSet(size_t signalCount)
{
	this->init(signalCount);
}


SignalSet::~SignalSet()
{

}

//////////////////////////////////////////////////////////////////

int SignalSet::init(size_t signalCount)
{
	m_signalList.resize(signalCount, 0.0);


	return 0;
}


int SignalSet::update()
{
	for (auto& signal : m_signalList)
	{
		if (abs(signal) > std::numeric_limits<double>::epsilon())
		{
			signal -= signal / 4.0;
		}
		else
		{
			signal = 0.0;
		}
	}


	return 0;
}

//////////////////////////////////////////////////////////////////

void SignalSet::setSignalList(const std::vector<double>& signalList)
{
	m_signalList = signalList;
}


void SignalSet::setSignalAt(size_t index, double signal)
{
#ifdef _DEBUG
	m_signalList.at(index) = signal;
#else
	m_signalList[index] = signal;
#endif
}

//---------------------------------------------------------------

const std::vector<double>& SignalSet::getSignalList() const
{
	return m_signalList;
}


double SignalSet::getSignalAt(size_t index) const
{
#ifdef _DEBUG
	return m_signalList.at(index);
#else
	return m_signalList[index];
#endif
}

//---------------------------------------------------------------

size_t SignalSet::getSignalCount() const
{
	return m_signalList.size();
}

