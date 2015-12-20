#include "LampComponent.h"



























LampComponent::LampComponent()
	: Component(1)
	
	, m_voltage(0.0)
	, m_bIsOn(false)
{

}


LampComponent::~LampComponent()
{

}

//////////////////////////////////////////////////////////////////

int LampComponent::update()
{
	m_voltage += (this->getComSignal(0) - m_voltage)/4.0;
	m_bIsOn = (m_voltage > 0.1);


	return 0;
}

//////////////////////////////////////////////////////////////////

bool LampComponent::getLight() const
{
	return m_bIsOn;
}

