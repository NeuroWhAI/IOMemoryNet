/*
* Author: tlsehdgus321@naver.com

* Description: ��ȣ������ ���� �����ϰ� �������̽��� ����.
*/

#ifndef __SIGNAL_SET_H__
#define __SIGNAL_SET_H__

#include <vector>























class SignalSet
{
public:
	SignalSet();
	explicit SignalSet(size_t signalCount);
	virtual ~SignalSet();


protected:
	std::vector<double> m_signalList;


public:
	int init(size_t signalCount);
	int update();


public:
	void setSignalList(const std::vector<double>& signalList);
	void setSignalAt(size_t index, double signal);

	const std::vector<double>& getSignalList() const;
	double getSignalAt(size_t index) const;

	size_t getSignalCount() const;
};

#endif