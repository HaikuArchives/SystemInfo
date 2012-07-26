/*************************************************/
/* SystemInfoReplicant                           */
/* By Brent Miszalski (misza@ihug.com.au)		 */
/*************************************************/


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
	
	delta_system = (double)system_time() - last_system_time;
	delta_cpu = double(info.cpu_infos[theCPU].active_time) - last_active_cpu_time;
	
	percent = (delta_cpu/delta_system);
	if(percent < 0) percent = 0.00;
	if(percent > 1) percent = 1.00;
	
	lastpercent = percent;
	last_active_cpu_time = (double)info.cpu_infos[theCPU].active_time;
	last_system_time = (double)system_time();
}

double CPU_Percent::Percentage()
{
	return percent;
}

