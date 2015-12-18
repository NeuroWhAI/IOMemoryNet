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
	virtual bool onKeyDown(int key) = 0;
	virtual bool onKeyDown_Quit() = 0;
	virtual bool onKeyDown_Enter() = 0;
};

#endif