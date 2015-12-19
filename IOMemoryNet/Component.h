/*
* Author: tlsehdgus321@naver.com

* Description: ComPort�� ��ȣ�� �����ų� ComPort�κ��� ��ȣ�� ������ ����ϴ� ��ġ.
*/

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <memory>

class ComPort;
























class Component
{
public:
	typedef std::shared_ptr<ComPort> ComPortPtr;


public:
	Component();
	virtual ~Component();


protected:
	ComPortPtr m_pComPort;


public:
	virtual int update() = 0;


public:
	int connect(ComPortPtr pComPort);
	int disconnect();

	bool onConnected() const;


public:
	double getComSignal(size_t index) const;
	void setComSignal(size_t index, double signal);


public:
	const ComPortPtr getComPort() const;
};

#endif