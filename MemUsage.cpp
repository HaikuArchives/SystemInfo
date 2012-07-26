/*************************************************/
/* SystemInfoReplicant                           */
/* By Brent Miszalski (misza@ihug.com.au)		 */
/*************************************************/


#include "MemUsage.h"

MemUsage::MemUsage()
{
	Update();
}

void MemUsage::Update()
{
	system_info info; 
	get_system_info(&info);

	total = (info.max_pages*B_PAGE_SIZE)/(1024*1024);//
	used = (info.used_pages*B_PAGE_SIZE)/(1024*1024);
	free = total - used;
	last_used = used;	
}

double MemUsage::Total()
{
	return total;	
}
double MemUsage::Used()
{
	return used;
}
double MemUsage::Free()
{
	return free;
}

	
