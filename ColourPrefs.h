/*************************************************/
/* SystemInfoReplicant                           */
/* By Brent Miszalski (misza@ihug.com.au)		 */
/*************************************************/


#ifndef _COLOUR_PREFS_
#define _COLOUR_PREFS_

#include <View.h>
#include <ColorControl.h>
#include <Window.h>
#include <Messenger.h>

const uint32 COLOURPREFS_UPDATE = 'ClrP';

class ColourPrefs : public BWindow
{
	public:
		ColourPrefs(BMessenger thatrep,BRect r, rgb_color startclr,bool fg);
		virtual void MessageReceived(BMessage* msg);
	private:
		BView* parent;
		BView* clrbox;
		BColorControl* ctrlbox;
		bool foreground;
		BMessenger ThatRep;
};
#endif

