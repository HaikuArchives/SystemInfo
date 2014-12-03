/*
 *	SystemInfoReplicant
 *
 *	Copyright 2002 Brent Miszalski
 *	Copyright 2012 Disreali		disreali[at]users[dot]sourceforge[dot]net
 *	All rights reserved. Distributed under the terms of the MIT License.
 *
 */


#include "CPUPercent.h"
CPU_Percent::CPU_Percent(int cpu)
{
	theCPU = cpu;
	Update();
}

void CPU_Percent::Update()
{
	system_info info;
	get_system_info(&info);

	cpu_info* cpuInfos = new cpu_info[info.cpu_count];
	get_cpu_info(0, info.cpu_count, cpuInfos);
	
	delta_system = (double)system_time() - last_system_time;
	delta_cpu = double(cpuInfos[theCPU].active_time) - last_active_cpu_time;
	
	percent = (delta_cpu/delta_system);
	if(percent < 0) percent = 0.00;
	if(percent > 1) percent = 1.00;
	
	lastpercent = percent;
	last_active_cpu_time = (double)cpuInfos[theCPU].active_time;
	last_system_time = (double)system_time();

	delete[] cpuInfos;
}

double CPU_Percent::Percentage()
{
	return percent;
}

