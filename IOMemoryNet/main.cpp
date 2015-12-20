#include <iostream>
#include <Windows.h>
#include <time.h>

#include "App.h"

using namespace std;
























int main()
{
	srand((unsigned)time(NULL));


	App testApp;

	testApp.init();

	while (testApp.isOnRun())
	{
		testApp.update();

		::system("cls");
		testApp.render();

		Sleep(16UL);
	}

	testApp.release();


	return 0;
}

