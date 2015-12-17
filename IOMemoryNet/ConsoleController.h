/*
* Author: tlsehdgus321@naver.com

* Description: Console환경에서 사용자의 제어를 받아들이는 역할.
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