#ifndef __LINK_HELPER_H__
#define __LINK_HELPER_H__

#include <memory>

class Cell;
class Linker;
























template <typename TCell, typename TLinker>
class LinkHelper
{
private:
	LinkHelper() = delete;


public:
	static bool connect(std::shared_ptr<TCell> pInCell, std::shared_ptr<TLinker> pLinker);
	static bool connect(std::shared_ptr<TLinker> pLinker, std::shared_ptr<TCell> pOutCell);
	static std::shared_ptr<TLinker> connect(std::shared_ptr<TCell> pInCell, std::shared_ptr<TCell> pOutCell);
};

#include "LinkHelper.inl"

#endif