#include "ConsoleGraphic.h"

#include <iostream>

#include "MemoryNet.h"
#include "SignalSet.h"

using namespace std;


























int ConsoleGraphic::drawMemoryNet(const MemoryNet& net)
{
	cout << "[MemoryNet]" << endl;
	cout << "InSize: " << net.getInputSize() << endl;
	cout << "OutSize: " << net.getOutputSize() << endl;


	return 0;
}


int ConsoleGraphic::drawSignalSet(const SignalSet& set)
{
	cout << "[SignalSet]" << endl;
	for (size_t i = 0; i < set.getSignalCount(); ++i)
	{
		cout << i << " : " << set.getSignalAt(i) << endl;
	}


	return 0;
}

