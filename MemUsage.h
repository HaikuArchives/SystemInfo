/*************************************************/
/* SystemInfoReplicant                           */
/* By Brent Miszalski (misza@ihug.com.au)		 */
/*************************************************/


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
