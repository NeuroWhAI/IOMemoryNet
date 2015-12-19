#ifndef __LINKER_H__
#define __LINKER_H__

#include <memory>

class Cell;
























class Linker
{
public:
	typedef std::shared_ptr<Cell> CellPtr;


public:
	Linker();
	Linker(CellPtr pInCell, CellPtr pOutCell);
	virtual ~Linker();


protected:
	CellPtr m_pInCell, m_pOutCell;
	double m_weight;


public:
	void setInCell(CellPtr pInCell);
	void setOutCell(CellPtr pOutCell);

	CellPtr getInCell();
	CellPtr getOutCell();
	const CellPtr getInCell() const;
	const CellPtr getOutCell() const;

	void setWeight(double weight);
	double getWeight() const;
};

#endif