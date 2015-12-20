#include "ConditionScore.h"

#include <memory>
#include <numeric>



























ConditionScore::ConditionScore()
	: m_pn(0.0)
{

}


ConditionScore::~ConditionScore()
{

}

//////////////////////////////////////////////////////////////////

int ConditionScore::update()
{
	if (abs(m_pn) < std::numeric_limits<double>::epsilon())
	{
		m_pn = 0.0;
	}
	else
	{
		m_pn -= m_pn / 4.0;
	}


	return 0;
}

//////////////////////////////////////////////////////////////////

ConditionScore& ConditionScore::operator= (const ConditionScore& rhs)
{
	if (this == &rhs) return *this;


	m_pn = rhs.m_pn;


	return *this;
}


int ConditionScore::addConditionScore(const ConditionScore& rhs, double weight)
{
	this->addPN(rhs.m_pn * weight);


	return 0;
}

//////////////////////////////////////////////////////////////////

double ConditionScore::getPN() const
{
	return m_pn;
}


void ConditionScore::addPN(double deltaPN)
{
	if (abs(m_pn) < 10.0)
	{
		m_pn += deltaPN;

		if (abs(m_pn) > 10.0)
		{
			if (m_pn < 0.0) m_pn = -10.0;
			else m_pn = 10.0;
		}
	}
}

