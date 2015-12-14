#include <iostream>

#include "App.h"

using namespace std;
























int main()
{
	App testApp;

	testApp.init();

	while (true)
	{
		::system("cls");

		testApp.update();
		testApp.render();
	}

	testApp.release();


	return 0;
}

