#include "ConsoleGraphic.h"

#include <iostream>
#include <vector>

#include "MemoryNet.h"
#include "SignalSet.h"

#include "MemoryCell.h"
#include "MemoryLinker.h"
#include "MemNetOperator.h"

using namespace std;


























int ConsoleGraphic::drawMemoryNet(const MemoryNet& net)
{
	cout << "[MemoryNet]" << endl;
	cout << "InSize: " << net.getInputSize() << endl;
	cout << "OutSize: " << net.getOutputSize() << endl;
	cout << endl;

	cout << "(NetOperator)" << endl;
	auto pOp = net.getMemNetOperator();
	cout << "Updating: " << pOp->countOfUpdatingCell() << endl;
	cout << "Head: " << pOp->countOfHeadCell() << endl;
	cout << "Next: " << pOp->countOfNextCell() << endl;
	cout << endl;

	int cnt = 0;
	auto& cellList = net.getMemoryCellList();
	for (auto& cellPtr : cellList)
	{
		cout << "(Cell_" << cnt << ") : ";
		double potential = cellPtr->getPotential();
		int width = static_cast<int>(potential*60.0);
		if (width > 20) width = 20;
		for (int w = 0; w < width; ++w)
		{
			cout << "|";
		}
		cout << endl;

		cout << "InSignalSet: [ ";
		for (const auto& signal : cellPtr->getInSignalSet()->getSignalList())
		{
			cout << signal << " ";
		}
		cout << "]" << endl;

		cout << "OutSignalSet: [ ";
		for (const auto& signal : cellPtr->getOutSignalSet()->getSignalList())
		{
			cout << signal << " ";
		}
		cout << "]" << endl;

		++cnt;
	}
	cout << endl;

	auto getCellIdx = [&cellList](std::shared_ptr<Cell> pCell) -> int {
		
		int idx = 0;
		for (auto& cellPtr : cellList)
		{
			if (cellPtr == pCell) return idx;

			++idx;
		}

		return -1;
	};

	cnt = 0;
	auto& linkerList = net.getMemoryLinkerList();
	for (auto& linkerPtr : linkerList)
	{
		/*cout << "(Linker_" << cnt << ") <";
		cout << getCellIdx(linkerPtr->getInCell()) << "-(";
		cout << linkerPtr->getWeight() << ")->";
		cout << getCellIdx(linkerPtr->getOutCell()) << endl;*/

		++cnt;
	}
	cout << "LinkerCount: " << cnt << endl;
	cout << endl;


	return 0;
}


int ConsoleGraphic::drawSignalSet(const SignalSet& set)
{
	cout << "[SignalSet]" << endl;
	for (size_t i = 0; i < set.getSignalCount(); ++i)
	{
		cout << i << " : " << set.getSignalAt(i) << endl;
	}
	cout << endl;


	return 0;
}

