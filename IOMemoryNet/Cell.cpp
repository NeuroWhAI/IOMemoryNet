#include "Cell.h"

#include <numeric>

#include "Linker.h"
#include "LinkerPort.h"

using LinkerPtr = Cell::LinkerPtr;
using LinkerPortPtr = Cell::LinkerPortPtr;


























const double Cell::POTENTIAL_REST = 0.0;
const double Cell::POTENTIAL_HOLD = 0.1;
const double Cell::POTENTIAL_ACTIVE = 1.0;

////////////////////////////////////////////////////////////////////

Cell::Cell()
	: m_potential(POTENTIAL_REST)

	, m_pInLinkerPort(new LinkerPort())
	, m_pOutLinkerPort(new LinkerPort())

	, currFunc(nullptr)
{

}


Cell::~Cell()
{

}

////////////////////////////////////////////////////////////////////

int Cell::update()
{
	if (currFunc != nullptr)
	{
		(this->*currFunc)();
	}


	if (this->isActivated())
	{
		whenCellActivatedFunc(*this);
	}


	return 0;
}

//---------------------------------------------------------------

int Cell::seq_toActive()
{
	double sub = POTENTIAL_ACTIVE - m_potential;

	if (sub > 0.0001)
	{
		m_potential += 1.0 / sub;
	}

	if (m_potential >= POTENTIAL_ACTIVE - 0.0001)
	{
		m_potential = POTENTIAL_ACTIVE;
		currFunc = &Cell::seq_toRestByDown;
	}


	return 0;
}


int Cell::seq_toRestByDown()
{
	m_potential += (POTENTIAL_REST - m_potential) / 4.0;

	if (m_potential <= POTENTIAL_REST + 0.0001)
	{
		m_potential = POTENTIAL_REST;
		currFunc = nullptr;
	}


	return 0;
}


int Cell::seq_toRestByUp()
{
	m_potential += (POTENTIAL_REST - m_potential) / 4.0;

	if (m_potential >= POTENTIAL_REST - 0.0001)
	{
		m_potential = POTENTIAL_REST;
		currFunc = nullptr;
	}


	return 0;
}

////////////////////////////////////////////////////////////////////

int Cell::activate()
{
	if (this->isActivated() == false)
	{
		this->setPotential(POTENTIAL_HOLD);
		currFunc = &Cell::seq_toActive;
	}


	return 0;
}


double Cell::getPotential() const
{
	return m_potential;
}


void Cell::setPotential(double potential)
{
	m_potential = potential;
}


void Cell::addPotential(double deltaPotential)
{
	this->setPotential(m_potential + deltaPotential);
}

//---------------------------------------------------------------

bool Cell::isActivated() const
{
	return (m_potential >= POTENTIAL_HOLD);
}


void Cell::checkUpdateNecessity()
{
	if (m_potential >= POTENTIAL_HOLD)
	{
		m_potential = POTENTIAL_HOLD;
		currFunc = &Cell::seq_toActive;
	}
	else
	{
		if (m_potential > POTENTIAL_REST)
		{
			currFunc = &Cell::seq_toRestByDown;
		}
		else
		{
			currFunc = &Cell::seq_toRestByUp;
		}
	}
}


bool Cell::isOnUpdate() const
{
	return (currFunc != nullptr);
}

////////////////////////////////////////////////////////////////////

LinkerPortPtr Cell::getInLinkerPort()
{
	return m_pInLinkerPort;
}


LinkerPortPtr Cell::getOutLinkerPort()
{
	return m_pOutLinkerPort;
}

////////////////////////////////////////////////////////////////////

int Cell::setCellActivationCallback(std::function<int(Cell&)> func)
{
	whenCellActivatedFunc = func;


	return 0;
}

