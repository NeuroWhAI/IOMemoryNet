/*
* Author: tlsehdgus321@naver.com

* Description: 입력장치로서 0과 1을 주기적으로 송신한다.
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