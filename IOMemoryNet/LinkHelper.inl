#ifndef __LINK_HELPER_INL__
#define __LINK_HELPER_INL__

#include "LinkHelper.h"

#include "Cell.h"
#include "Linker.h"

#include "LinkerPort.h"



























template <typename TCell, typename TLinker>
bool LinkHelper<TCell, TLinker>::connect(std::shared_ptr<TCell> pInCell, std::shared_ptr<TLinker> pLinker)
{
	if (pInCell->getOutLinkerPort()->addLinker(pLinker, pLinker->getOutCell()))
	{
		pLinker->setInCell(pInCell);

		return true;
	}

	return false;
}


template <typename TCell, typename TLinker>
bool LinkHelper<TCell, TLinker>::connect(std::shared_ptr<TLinker> pLinker, std::shared_ptr<TCell> pOutCell)
{
	if (pOutCell->getInLinkerPort()->addLinker(pLinker, pLinker->getInCell()))
	{
		pLinker->setOutCell(pOutCell);

		return true;
	}

	return false;
}


template <typename TCell, typename TLinker>
std::shared_ptr<TLinker> LinkHelper<TCell, TLinker>::connect(std::shared_ptr<TCell> pInCell, std::shared_ptr<TCell> pOutCell)
{
	std::shared_ptr<TLinker> pNewLinker(new TLinker());

	if (pInCell->getOutLinkerPort()->addLinker(pNewLinker, pOutCell))
	{
		if (pOutCell->getInLinkerPort()->addLinker(pNewLinker, pInCell))
		{
			pNewLinker->setInCell(pInCell);
			pNewLinker->setOutCell(pOutCell);

			return pNewLinker;
		}
		else
		{
			pInCell->getOutLinkerPort()->removeLinker(pOutCell);

			return nullptr;
		}
	}

	return nullptr;
}

#endif