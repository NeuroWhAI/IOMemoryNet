/*
* Author: tlsehdgus321@naver.com

* Description: 신호값들을 묶어 관리하고 인터페이스를 제공.
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

	int copyFrom(const SignalSet& other);
	int copyRange(const SignalSet& src, size_t begin, size_t count);
	bool isEqual(const SignalSet& other, size_t checkCount, double maxUnit) const;
	void addSignals(const SignalSet& other, double weight = 1.0);


public:
	void setSignalList(const std::vector<double>& signalList);
	void setSignalAt(size_t index, double signal);
	void addSignalAt(size_t index, double deltaSignal);

	const std::vector<double>& getSignalList() const;
	double getSignalAt(size_t index) const;

	size_t getSignalCount() const;
};

#endif