/*
* Author: tlsehdgus321@naver.com

* Description: �����ġ�μ� 0�Ǵ� 1�� ǥ���ϴ� ����.
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