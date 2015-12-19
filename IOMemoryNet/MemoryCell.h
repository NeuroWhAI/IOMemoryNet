#ifndef __MEMORY_CELL_H__
#define __MEMORY_CELL_H__

#include <memory>

#include "Cell.h"

class SignalSet;
























class MemoryCell : public Cell
{
public:
	typedef std::shared_ptr<SignalSet> SignalSetPtr;


public:
	MemoryCell();
	virtual ~MemoryCell();


protected:
	SignalSetPtr m_pInSignalSet, m_pOutSignalSet;


protected:
	std::function<int(MemoryCell&)> whenMemoryActivatedFunc;


public:
	int update() override;


public:
	int setMemoryActivationCallback(std::function<int(MemoryCell&)> func);

	int setOutSignalCount(size_t signalCount);
	
	int setInSignalSet(const SignalSetPtr& inSignalSet);
	int setOutSignalSet(const SignalSetPtr& outSignalSet);

	SignalSetPtr getInSignalSet();
	SignalSetPtr getOutSignalSet();
};

#endif