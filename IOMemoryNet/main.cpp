#include <iostream>

#include "App.h"

using namespace std;
























int main()
{
	App testApp;

	testApp.init();

	while (testApp.isOnRun())
	{
		::system("cls");

		testApp.update();
		testApp.render();
	}

	testApp.release();


	return 0;
}

