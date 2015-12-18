#include <iostream>
#include <Windows.h>

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

		Sleep(16UL);
	}

	testApp.release();


	return 0;
}

