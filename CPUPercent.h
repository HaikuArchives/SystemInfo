/*
 *	SystemInfoReplicant
 *
 *	Copyright 2002 Brent Miszalski
 *	Copyright 2012 Disreali		disreali[at]users[dot]sourceforge[dot]net
 *	All rights reserved. Distributed under the terms of the MIT License.
 *
 */


#ifndef _CPU_PERCENT_H
#define _CPU_PERCENT_H

#include <iostream>
#include <OS.h>
#include <stdio.h>
//#include <String.h>

class CPU_Percent
{
	public:
		CPU_Percent(int cpu);
		void Update();
		double Percentage();
			
	private:
		int theCPU;
		double delta_cpu;
		double delta_system;
		double percent;
		double lastpercent;
		double last_active_cpu_time;
		double last_system_time;
};
#endif
