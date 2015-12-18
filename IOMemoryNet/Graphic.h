/*
* Author: tlsehdgus321@naver.com

* Description: Model을 사용자에게 보여주는 역할.
*/

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

class MemoryNet;
class SignalSet;
























class Graphic
{
public:
	virtual int drawMemoryNet(const MemoryNet& net) = 0;
	virtual int drawSignalSet(const SignalSet& set) = 0;
};

#endif