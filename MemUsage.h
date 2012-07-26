/*
 *	SystemInfoReplicant
 *
 *	Copyright 2002 Brent Miszalski
 *	Copyright 2012 Disreali		disreali[at]users[dot]sourceforge[dot]net
 *	All rights reserved. Distributed under the terms of the MIT License.
 *
 */


#ifndef _MEM_USAGE_H
#define _MEM_USAGE_H

#include <iostream>
#include <OS.h>
#include <stdio.h>

class MemUsage
{
	public:
		MemUsage();
		void Update();
		double Total();
		double Used();
		double Free();
	private:
		double total;
		double used;
		double free;
		double last_used;
};
#endif
