#ifndef __MEM_NET_OPERATOR_H__
#define __MEM_NET_OPERATOR_H__

#include "NetOperator.h"
























class MemNetOperator : public NetOperator
{
public:
	MemNetOperator();
	virtual ~MemNetOperator();


public:
	int update() override;
};

#endif