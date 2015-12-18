/*
* Author: tlsehdgus321@naver.com

* Description: 기억세포와 기억링커 등으로 구성된 기억망을 표현함.
*/

#ifndef __MEMORY_NET_H__
#define __MEMORY_NET_H__

#include <memory>
#include <vector>

class SignalSet;
class Component;
class ComPort;
























class MemoryNet
{
public:
	MemoryNet();
	MemoryNet(size_t inSignalCount, size_t outSignalCount);
	virtual ~MemoryNet();


protected:
	std::shared_ptr<SignalSet> m_pInSignal, m_pOutSignal;


protected:
	std::vector<std::shared_ptr<ComPort>> m_pComList;


public:
	int init(size_t inSignalCount, size_t outSignalCount);
	int release();

	int update();


public:
	size_t getInputSize() const;
	size_t getOutputSize() const;

	const std::shared_ptr<SignalSet> getInputSet() const;
	const std::shared_ptr<SignalSet> getOutputSet() const;


public:
	std::shared_ptr<ComPort> assignComPortAtInput(size_t index, size_t count);
	std::shared_ptr<ComPort> assignComPortAtOutput(size_t index, size_t count);

	int removeComPort(std::shared_ptr<ComPort> pCom);
};

#endif