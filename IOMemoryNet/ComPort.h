/*
* Author: tlsehdgus321@naver.com

* Description: SignalSet과의 값 전달 인터페이스 제공.
*/

#ifndef __COM_PORT_H__
#define __COM_PORT_H__

#include <memory>

class SignalSet;
























class ComPort
{
public:
	ComPort();
	virtual ~ComPort();


protected:
	std::shared_ptr<SignalSet> m_pConnectedSignalList;
	size_t m_connectedIndex, m_assignedCount;


public:
	int connect(std::shared_ptr<SignalSet> pSignalList,
		size_t index, size_t count);


public:
	double getSignal(size_t index) const;
	void setSignal(size_t index, double signal);

	std::shared_ptr<SignalSet> getSignalList() const;
};

#endif