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
	typedef std::shared_ptr<SignalSet> SignalSetPtr;


public:
	ComPort();
	virtual ~ComPort();


protected:
	SignalSetPtr m_pConnectedSignalList;
	size_t m_connectedIndex, m_assignedCount;


public:
	int connect(SignalSetPtr pSignalList,
		size_t index, size_t count);


public:
	double getSignal(size_t index) const;
	void setSignal(size_t index, double signal);

	SignalSetPtr getSignalList() const;
	// * 점유한 신호의 수
	size_t getAssignedCount() const;
};

#endif