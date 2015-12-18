/*
* Author: tlsehdgus321@naver.com

* Description: Console환경에서 Model을 사용자에게 보여주는 역할.
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