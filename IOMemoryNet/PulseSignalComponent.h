/*
* Author: tlsehdgus321@naver.com

* Description: �Է���ġ�μ� 0�� 1�� �ֱ������� �۽��Ѵ�.
*/

#ifndef __PULSE_SIGNAL_COMPONENT_H__
#define __PULSE_SIGNAL_COMPONENT_H__

#include "Component.h"
























class PulseSignalComponent : public Component
{
public:
	PulseSignalComponent();
	virtual ~PulseSignalComponent();


public:
	int update() override;
};

#endif