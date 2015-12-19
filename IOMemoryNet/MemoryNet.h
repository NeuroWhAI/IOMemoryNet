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
class Cell;
class Linker;
class MemoryCell;
class MemoryLinker;
class MemNetOperator;
























class MemoryNet
{
public:
	typedef std::shared_ptr<SignalSet> SignalSetPtr;
	typedef std::shared_ptr<ComPort> ComPortPtr;
	typedef std::shared_ptr<Cell> CellPtr;
	typedef std::shared_ptr<Linker> LinkerPtr;
	typedef std::shared_ptr<MemoryCell> MemoryCellPtr;
	typedef std::shared_ptr<MemoryLinker> MemoryLinkerPtr;
	typedef std::shared_ptr<MemNetOperator> MemNetOperatorPtr;


public:
	MemoryNet();
	MemoryNet(size_t inSignalCount, size_t outSignalCount);
	virtual ~MemoryNet();


protected:
	double m_maxSignalUnit; // 이 값이 작을수록 미세한 입력값의 변화로 새로운 기억을 생성함.
	SignalSetPtr m_pInSignalSet, m_pOutSignalSet;


protected:
	std::vector<ComPortPtr> m_pComList;


protected:
	std::vector<MemoryCellPtr> m_pCellList;
	std::vector<MemoryLinkerPtr> m_pLinkerList;

	MemNetOperatorPtr m_pNetOperator;


public:
	int init(size_t inSignalCount, size_t outSignalCount);
	int release();

	int update();


public:
	size_t getInputSize() const;
	size_t getOutputSize() const;

	const SignalSetPtr getInputSet() const;
	const SignalSetPtr getOutputSet() const;


public:
	ComPortPtr assignComPortAtInput(size_t index, size_t count);
	ComPortPtr assignComPortAtOutput(size_t index, size_t count);

	int removeComPort(ComPortPtr pCom);


protected:
	int addMemoryCell(MemoryCellPtr pCell);
	int removeMemoryCell(const MemoryCellPtr pCell);

	int addMemoryLinker(MemoryLinkerPtr pLinker);
	int removeMemoryLinker(const MemoryLinkerPtr pLinker);


public:
	const std::vector<MemoryCellPtr>& getMemoryCellList() const;
	const std::vector<MemoryLinkerPtr>& getMemoryLinkerList() const;
	const MemNetOperatorPtr getMemNetOperator() const;


protected:
	int whenActivateCell(Cell& cell);
	int whenActivateMemoryCell(MemoryCell& memoryCell);
};

#endif