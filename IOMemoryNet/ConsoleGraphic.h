/*
* Author: tlsehdgus321@naver.com

* Description: Consoleȯ�濡�� Model�� ����ڿ��� �����ִ� ����.
*/

#ifndef __CONSOLE_GRAPHIC_H__
#define __CONSOLE_GRAPHIC_H__

#include "Graphic.h"






















class ConsoleGraphic : public Graphic
{
public:
	virtual ~ConsoleGraphic() = default;


public:
	int drawMemoryNet(const MemoryNet& net) override;
	int drawSignalSet(const SignalSet& set) override;
};

#endif