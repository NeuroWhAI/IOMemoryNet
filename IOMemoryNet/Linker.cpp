#include "Linker.h"

#include "Cell.h"

using CellPtr = Linker::CellPtr;



























Linker::Linker()
	: m_pInCell(nullptr)
	, m_pOutCell(nullptr)

	, m_weight(0.1)
{

}


Linker::Linker(CellPtr pInCell, CellPtr pOutCell)
	: m_pInCell(pInCell)
	, m_pOutCell(pOutCell)

	, m_weight(0.1)
{

}


Linker::~Linker()
{

}

////////////////////////////////////////////////////////////////////

void Linker::setInCell(CellPtr pInCell)
{
	m_pInCell = pInCell;
}


void Linker::setOutCell(CellPtr pOutCell)
{
	m_pOutCell = pOutCell;
}



CellPtr Linker::getInCell()
{
	return m_pInCell;
}


CellPtr Linker::getOutCell()
{
	return m_pOutCell;
}


const CellPtr Linker::getInCell() const
{
	return m_pInCell;
}


const CellPtr Linker::getOutCell() const
{
	return m_pOutCell;
}



void Linker::setWeight(double weight)
{
	m_weight = weight;
}


double Linker::getWeight() const
{
	return m_weight;
}

