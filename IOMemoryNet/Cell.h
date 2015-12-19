#ifndef __CELL_H__
#define __CELL_H__

#include <memory>
#include <functional>

class Linker;
class LinkerPort;
























class Cell
{
public:
	typedef std::shared_ptr<Linker> LinkerPtr;
	typedef std::shared_ptr<LinkerPort> LinkerPortPtr;


public:
	static const double POTENTIAL_REST;
	static const double POTENTIAL_HOLD;
	static const double POTENTIAL_ACTIVE;


public:
	Cell();
	virtual ~Cell();


protected:
	double m_potential;


protected:
	LinkerPortPtr m_pInLinkerPort, m_pOutLinkerPort;


private:
	int (Cell::*currFunc)(void);
	std::function<int(Cell&)> whenCellActivatedFunc;


public:
	virtual int update();

	int seq_toActive();
	int seq_toRestByDown();
	int seq_toRestByUp();


public:
	int activate();
	double getPotential() const;
	void setPotential(double potential);
	void addPotential(double deltaPotential);

	bool isActivated() const;
	void checkUpdateNecessity();
	bool isOnUpdate() const;


public:
	LinkerPortPtr getInLinkerPort();
	LinkerPortPtr getOutLinkerPort();


public:
	int setCellActivationCallback(std::function<int(Cell&)> func);
};

#endif