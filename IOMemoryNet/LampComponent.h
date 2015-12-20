/*
* Author: tlsehdgus321@naver.com

* Description: 출력장치로서 0또는 1을 표시하는 램프.
*/

#ifndef __LAMP_COMPONENT_H__
#define __LAMP_COMPONENT_H__

#include "Component.h"
























class LampComponent : public Component
{
public:
	LampComponent();
	virtual ~LampComponent();


protected:
	double m_voltage;
	bool m_bIsOn;


public:
	int update() override;


public:
	bool getLight() const;
};

#endif