/*
* Author: tlsehdgus321@naver.com

* Description: ������� ��� �޾Ƶ��̴� ����.
*/

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
























class Controller
{
public:
	virtual int update() = 0;


public:
	virtual bool onKeyDown_Quit() = 0;
};

#endif