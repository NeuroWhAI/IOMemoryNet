/*
* Author: tlsehdgus321@naver.com

* Description: Consoleȯ�濡�� ������� ��� �޾Ƶ��̴� ����.
*/

#ifndef __CONSOLE_CONTROLLER_H__
#define __CONSOLE_CONTROLLER_H__

#include "Controller.h"






















class ConsoleController : public Controller
{
public:
	ConsoleController();
	virtual ~ConsoleController() = default;


protected:
	char m_key;


public:
	int update() override;


public:
	bool onKeyDown_Quit() override;
};

#endif