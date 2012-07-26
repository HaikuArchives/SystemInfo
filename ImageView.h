/*************************************************/
/* SystemInfoReplicant                           */
/* By Brent Miszalski (misza@ihug.com.au)		 */
/*************************************************/


#ifndef _IMAGE_VIEW_H
#define _IMAGE_VIEW_H

#include <View.h>
#include <Bitmap.h>
#include <Window.h>
#include <VolumeRoster.h>
#include <Volume.h>
#include <OS.h>
#include "CPUPercent.h"
#include "MemUsage.h"
#include <String.h>
#include <Messenger.h>
#include <MessageRunner.h>
#include <Dragger.h>
#include <Alert.h>
//#include "ColourPrefs.h"

const int UPDATE_TIME_AMOUNT = 1000;
const uint32 UPDATER = 'Init';
//const uint32 CP_CHANGE_BG = 'CPBG';
//const uint32 CP_CHANGE_FG = 'CPFG';


const rgb_color translucent = {255,255,255,128};
const rgb_color trblue = {51,61,106,64};
_EXPORT class  ImageView : public BView
{
public:
	ImageView(BRect frame);
	~ImageView();
	virtual	void	Draw(BRect updateRect);
	virtual void	AttachedToWindow();
	virtual void Pulse();
	virtual void MouseDown(BPoint point);
	virtual void MouseUp(BPoint point);
	virtual void MouseMoved(BPoint point,uint32 transit,const BMessage* msg);
	virtual void MessageReceived(BMessage* msg);
	void Render();
	// revives the app and puts it together as a replicant 
	ImageView(BMessage *data);
	// receives the revive call and calls the message only constructor
	static	BArchivable	*Instantiate(BMessage *data);
	// archives the view, starts the replicant process
	virtual	status_t	Archive(BMessage *data, bool deep = true) const;

private:
		typedef	BView inherited;
		BMessageRunner* timeKeeper;
		BMessageRunner* timeKeeper2;
		
		BView* bView;
		BBitmap* bitmap;
		MemUsage* mem;
		//StatusBar* CPU_0;
		CPU_Percent* c1;
		
		//StatusBar* CPU_1;
		CPU_Percent* c2;
		
		float gauge_1;
		float gauge_2;
		float gauge_3;
		
		BVolumeRoster theVRoster;
		BVolume boot;
		double total;
		double free;
		double used;
		
		float gauge_4;
		bigtime_t sec;// = (system_time();/1000)/1000;
		bigtime_t min;// = sec/60;
		bigtime_t hours;// = min/60;
		bigtime_t days;// = hours/24;
		BString uptime;
		bool DoWeMove;
		BPoint thePoint;
		bool Is2CPU;
		//rgb_color fgcolor;
		bool IsReplicant;
};
#endif
