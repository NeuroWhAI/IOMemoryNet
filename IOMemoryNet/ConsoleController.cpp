#include "ConsoleController.h"

#include <conio.h>
























ConsoleController::ConsoleController()
	: m_key('\0')
{

}

//////////////////////////////////////////////////////////////////

int ConsoleController::update()
{
	if (_kbhit())
	{
		m_key = static_cast<char>(_getch());
	}
	else
	{
		m_key = '\0';
	}


	return 0;
}

//////////////////////////////////////////////////////////////////

bool ConsoleController::onKeyDown_Quit()
{
	return (m_key == 'q' || m_key == 'Q');
}

