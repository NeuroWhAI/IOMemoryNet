#ifndef __LINKER_PORT_H__
#define __LINKER_PORT_H__

#include <memory>
#include <unordered_map>
#include <functional>

class Linker;
class Cell;
























class LinkerPort
{
public:
	typedef std::shared_ptr<Linker> LinkerPtr;
	typedef std::shared_ptr<Cell> CellPtr;


public:
	LinkerPort();
	virtual ~LinkerPort();


protected:
	std::unordered_map<const Cell*, LinkerPtr> m_pLinkerList;


public:
	bool addLinker(LinkerPtr pLinker, const CellPtr pOtherSideCell);
	int removeLinker(const CellPtr pOtherSideCell);


public:
	int foreach(std::function<void(LinkerPtr)> Func);
	bool checkOverlap(const CellPtr pOtherSideCell) const;
};

#endif