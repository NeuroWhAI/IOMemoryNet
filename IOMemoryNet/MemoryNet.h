/*
* Author: tlsehdgus321@naver.com

* Description: 기억세포와 기억링커 등으로 구성된 기억망을 표현함.
*/

#ifndef __MEMORY_NET_H__
#define __MEMORY_NET_H__
























class MemoryNet
{
public:
	MemoryNet();
	virtual ~MemoryNet();


public:
	int init();
	int release();

	int update();
};

#endif