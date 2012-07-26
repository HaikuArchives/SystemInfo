/*************************************************/
/* SystemInfoReplicant                           */
/* By Brent Miszalski (misza@ihug.com.au)		 */
/*************************************************/


#include "ColourPrefs.h"
#include "DigitalView.h"
ColourPrefs::ColourPrefs(BMessenger thatrep,BRect r, rgb_color startclr,bool fg)
: BWindow(r,"",B_TITLED_WINDOW,B_NOT_RESIZABLE|B_NOT_ZOOMABLE|B_ASYNCHRONOUS_CONTROLS)
{	
	if(fg)
		SetTitle("Foreground Colour");
	else
		SetTitle("Background Colour");
	ThatRep = thatrep;
	
	foreground = fg;
	parent = new BView(Bounds(),"parent",B_FOLLOW_ALL,B_WILL_DRAW);
	AddChild(parent);
	parent->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	
	ctrlbox = new BColorControl(BPoint(10,10),B_CELLS_32x8,4.0,"ctrlbox",new BMessage(COLOURPREFS_UPDATE),true);
	parent->AddChild(ctrlbox);

	clrbox = new BView(BRect(287,10,339,62),"clrbox",B_FOLLOW_ALL,B_WILL_DRAW);
	parent->AddChild(clrbox);
	
	ctrlbox->SetValue(startclr);
	clrbox->SetViewColor(startclr);
	clrbox->Invalidate();
}

void ColourPrefs::MessageReceived(BMessage* msg)
{
	// drag & drop
		if( msg->WasDropped())
		{
			rgb_color*	Rgb;
			ssize_t		Size;
			// if there is RGB color
			if( (msg->FindData("RGBColor", B_RGB_COLOR_TYPE, (const void **)&Rgb, &Size) == B_OK))
			{
				ctrlbox->SetValue(*Rgb);
				clrbox->SetViewColor(*Rgb);
				clrbox->Invalidate();
			
				if(foreground)
				{	
					BMessage mymsg(CP_CHANGE_FG);
					mymsg.AddData("fgcolor",B_RGB_COLOR_TYPE,Rgb,sizeof(rgb_color));
					ThatRep.SendMessage(&mymsg);
				}
				else
				{	
					BMessage mymsg(CP_CHANGE_BG);
					mymsg.AddData("bgcolor",B_RGB_COLOR_TYPE,Rgb,sizeof(rgb_color));
					ThatRep.SendMessage(&mymsg);	
				}
			}
			return;
		}
		
		
	switch(msg->what)
	{
		case COLOURPREFS_UPDATE:
		{
			rgb_color updated_colour = ctrlbox->ValueAsColor();
			clrbox->SetViewColor(updated_colour);
			clrbox->Invalidate();
			
			if(foreground)
			{
				BMessage mymsg(CP_CHANGE_FG);
				mymsg.AddData("fgcolor",B_RGB_COLOR_TYPE,&updated_colour,sizeof(rgb_color));
				ThatRep.SendMessage(&mymsg);
			}
			else
			{
				BMessage mymsg(CP_CHANGE_BG);
				mymsg.AddData("bgcolor",B_RGB_COLOR_TYPE,&updated_colour,sizeof(rgb_color));
				ThatRep.SendMessage(&mymsg);	
			}
		}break;
		
		
		default:
		BWindow::MessageReceived(msg);
		break;
	}
	
	
	
}
