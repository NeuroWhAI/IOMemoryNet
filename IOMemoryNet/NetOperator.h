#ifndef __NET_OPERATOR_H__
#define __NET_OPERATOR_H__

#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <functional>

class Cell;
class Linker;
























class NetOperator
{
public:
	typedef std::shared_ptr<Cell> CellPtr;
	typedef std::shared_ptr<Linker> LinkerPtr;


public:
	NetOperator();
	virtual ~NetOperator();


protected:
	std::unordered_set<CellPtr> m_pUpdatingCellList;
	std::unordered_set<CellPtr> m_pHeadCellList;
	std::unordered_map<CellPtr, double> m_pNextStepList;


public:
	virtual int update();


public:
	bool addCell(CellPtr pCell);
	int removeCell(const CellPtr pCell);


public:
	size_t countOfUpdatingCell() const;
	size_t countOfHeadCell() const;
	size_t countOfNextCell() const;

	int foreachUpdatingCell(std::function<void(CellPtr)> func);
	int foreachHeadCell(std::function<void(CellPtr)> func);
};

#endif