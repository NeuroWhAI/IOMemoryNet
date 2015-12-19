#include "LinkerPort.h"

#include "Linker.h"
#include "Cell.h"

using LinkerPtr = LinkerPort::LinkerPtr;
using CellPtr = LinkerPort::CellPtr;



























LinkerPort::LinkerPort()
{

}


LinkerPort::~LinkerPort()
{

}

////////////////////////////////////////////////////////////////////

bool LinkerPort::addLinker(LinkerPtr pLinker, const CellPtr pOtherSideCell)
{
	auto result = m_pLinkerList.insert(
		std::make_pair(pOtherSideCell.get(), pLinker));


	// 삽입 성공여부 반환
	return result.second;
}


int LinkerPort::removeLinker(const CellPtr pOtherSideCell)
{
	m_pLinkerList.erase(pOtherSideCell.get());


	return 0;
}

////////////////////////////////////////////////////////////////////

int LinkerPort::foreach(std::function<void(LinkerPtr)> Func)
{
	for (auto& item : m_pLinkerList)
	{
		Func(item.second);
	}


	return 0;
}


bool LinkerPort::checkOverlap(const CellPtr pOtherSideCell) const
{
	return (m_pLinkerList.find(pOtherSideCell.get()) != m_pLinkerList.cend());
}

