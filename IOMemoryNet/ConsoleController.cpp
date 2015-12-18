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

bool ConsoleController::onKeyDown(int key)
{
	if (key >= 'a' && key <= 'z'
		&&
		m_key >= 'A' && m_key <= 'Z')
	{
		return (m_key == key - ('a' - 'A'));
	}
	else if (key >= 'A' && key <= 'Z'
		&&
		m_key >= 'a' && m_key <= 'z')
	{
		return (m_key - ('a' - 'A') == key);
	}

	return (m_key == key);
}


bool ConsoleController::onKeyDown_Quit()
{
	return (m_key == 'q' || m_key == 'Q');
}


bool ConsoleController::onKeyDown_Enter()
{
	return (m_key == ' ');
}

