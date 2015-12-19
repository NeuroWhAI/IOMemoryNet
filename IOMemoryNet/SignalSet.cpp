#include "SignalSet.h"

#include <numeric>
#include <assert.h>


























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
	m_signalList.clear();
	m_signalList.resize(signalCount, 0.0);


	return 0;
}


int SignalSet::update()
{
	for (auto& signal : m_signalList)
	{
		/*if (abs(signal) > std::numeric_limits<double>::epsilon())
		{
		signal -= signal / 4.0;
		}
		else
		{
		signal = 0.0;
		}*/
		signal = 0.0;
	}


	return 0;
}

//---------------------------------------------------------------

int SignalSet::copyFrom(const SignalSet& other)
{
	m_signalList = other.m_signalList;


	return 0;
}


int SignalSet::copyRange(const SignalSet& src, size_t begin, size_t count)
{
	size_t end = begin + count;

#ifdef _DEBUG
	assert(end <= m_signalList.size() && count <= src.m_signalList.size()
		&&
		"SignalSet::copyRange");
#endif

	for (size_t i = begin; i < end; ++i)
	{
		m_signalList[i] = src.m_signalList[i - begin];
	}


	return 0;
}


bool SignalSet::isEqual(const SignalSet& other, size_t checkCount, double maxUnit) const
{
	if (m_signalList.size() < checkCount
		||
		other.m_signalList.size() < checkCount)
	{
		return false;
	}

	for (size_t i = 0; i < checkCount; ++i)
	{
		if (abs(m_signalList[i] - other.m_signalList[i]) >= maxUnit)
			return false;
	}


	return true;
}


void SignalSet::addSignals(const SignalSet& other, double weight)
{
#ifdef _DEBUG
	assert(m_signalList.size() == other.m_signalList.size()
		&&
		"SignalSet::addSignals");
#endif

	const size_t listCnt = m_signalList.size();
	for (size_t i = 0; i < listCnt; ++i)
	{
		m_signalList[i] += other.m_signalList[i] * weight;
	}
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

