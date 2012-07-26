/*************************************************/
/* SystemInfoReplicant                           */
/* By Brent Miszalski (misza@ihug.com.au)		 */
/*************************************************/


#include "SIReplicant.h"
#include <Application.h>
#include <Window.h>

int main(int argc, char ** argv)
{
	BApplication app("application/x-vnd.misza-SystemInfoReplicant");
	
	BRect temp,r;
	
	BPath path;
  	find_directory(B_USER_SETTINGS_DIRECTORY,&path);
  	path.Append("SystemInfoReplicant",true);
  	
  	BFile file(path.Path(),B_READ_ONLY);
  	if(file.InitCheck() == B_OK)
  	{
		BMessage msg;
  		msg.Unflatten(&file);
		if(msg.FindRect("frame",&temp) == B_OK)
			r = temp;
	
	}
	else
		r = BRect(250,250,424,385);
	
	
	BWindow* window = new SIReplicant(r);
	window->Show();
	app.Run();
	return 0;
}

