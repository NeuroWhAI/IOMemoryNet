#include "PulseSignalComponent.h"



























PulseSignalComponent::PulseSignalComponent()
	: Component(1)
{

}


PulseSignalComponent::~PulseSignalComponent()
{

}

//////////////////////////////////////////////////////////////////

int PulseSignalComponent::update()
{
	if (this->onConnected())
	{
		if (this->getComSignal(0) < 0.5)
			this->setComSignal(0, 1.0);
		else
			this->setComSignal(0, 0.0);
	}


	return 0;
}

