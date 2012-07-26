/*
 *	SystemInfoReplicant
 *
 *	Copyright 2002 Brent Miszalski
 *	Copyright 2012 Disreali		disreali[at]users[dot]sourceforge[dot]net
 *	All rights reserved. Distributed under the terms of the MIT License.
 *
 */


#include "SIReplicant.h"

SIReplicant::SIReplicant(BRect r) : BWindow(r, "SystemInfo", B_TITLED_WINDOW, B_NOT_ZOOMABLE|B_NOT_RESIZABLE)
{	
	//SetPulseRate(UPDATE_TIME_AMOUNT);
	//parent = new BView(Bounds(),"parent",B_FOLLOW_ALL_SIDES,0);
	//parent->SetViewColor(51,61,106);	
	//parent->SetViewColor(B_TRANSPARENT_COLOR);
	//AddChild(parent);
	theImage = new ImageView(Bounds());
	//theImage->SetViewColor(51,61,106);
	AddChild(theImage);

 ///	
//  bitmap=new BBitmap(parent->Bounds(),B_RGB32,true);
//	bitmap->Lock();
//	bView =new BView(parent->Bounds(),"view",B_FOLLOW_ALL_SIDES, 0);
//	bitmap->AddChild(bView);
//	bView->SetViewColor(51,61,106);
	//Render();
//	bitmap->Unlock();

 	
 	/*
	CPU_0 = new StatusBar(BRect(60,10,190,25),"CPU 0");
	parent->AddChild(CPU_0);

	BStringView* label_1 = new BStringView(BRect(10,10,50,25),"label_1","CPU 0");
	label_1->SetHighColor(255,255,255);
	label_1->SetFont(be_bold_font);
	parent->AddChild(label_1);
	
	c1 = new CPU_Percent(0);
	c1->Update();
	CPU_0->Update(c1->Percentage());
	
	
	CPU_1 = new StatusBar(BRect(60,35,190,50),"CPU 1");
	parent->AddChild(CPU_1);
	
	BStringView* label_2 = new BStringView(BRect(10,35,50,50),"label_1","CPU 1");
	label_2->SetHighColor(255,255,255);
	label_2->SetFont(be_bold_font);
	parent->AddChild(label_2);
	
	c2 = new CPU_Percent(1);
	c2->Update();
	CPU_1->Update(c2->Percentage());
		
	*/
//	Render();
	
	//BMessenger mymsnger(this);
	//BMessage update(UPDATER);
	//updateR = new BMessageRunner(mymsnger,&update,UPDATE_TIME_AMOUNT,-1);
	

	
}
SIReplicant::~SIReplicant()
{
	BMessage msg;
	msg.AddRect("frame",Frame());
	BPath path;
    
    if(find_directory(B_USER_SETTINGS_DIRECTORY,&path) == B_OK)
    {
	    path.Append("SystemInfoReplicant",true);
    	BFile file(path.Path(),B_READ_WRITE | B_CREATE_FILE | B_ERASE_FILE);
	    msg.Flatten(&file);
	}
	
}
// Called when the user clicks on the window's close box
bool SIReplicant::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);// tell the application to quit too
	return true; // and indicate that it's okay for us to close
}
void SIReplicant :: MessageReceived(BMessage* msg)
{
	switch(msg->what)
	{
		//case UPDATER:
		//{
			//Render();
			/*	
				c1->Update();
				CPU_0->Update(c1->Percentage());
				
				c2->Update();
				CPU_1->Update(c2->Percentage());
			*/
		//}break;
		default:
			BWindow::MessageReceived(msg);
	    break;
	}
}

///void SIReplicant::Render()
//{
	//bitmap->Lock();
	//create first bar
/*	BRect r(60,10,190,25); 
	bView->SetHighColor(255,255,255);
	
	c1->Update();
	gauge_1 = c1->Percentage();
	
	length_1 = r.right-2 - r.left+2;
	
	
	bView->StrokeLine(BPoint(r.left,r.top),BPoint(r.right-1,r.top));
		bView->StrokeLine(BPoint(r.left+1,r.top+1),BPoint(r.right-1,r.top+1));
		
	bView->StrokeLine(BPoint(r.right,r.top),BPoint(r.right,r.bottom));
		bView->StrokeLine(BPoint(r.right-1,r.top+1),BPoint(r.right-1,r.bottom-1));
		
	bView->StrokeLine(BPoint(r.right,r.bottom),BPoint(r.left,r.bottom));
		bView->StrokeLine(BPoint(r.right-1,r.bottom-1),BPoint(r.left+1,r.bottom-1));
	
	bView->StrokeLine(BPoint(r.left,r.bottom),BPoint(r.left,r.top));
		bView->StrokeLine(BPoint(r.left+1,r.bottom-1),BPoint(r.left+1,r.top+1));
	
	
	if(gauge_1 != 0.0)
	{
		bView->SetDrawingMode(B_OP_ALPHA);
		bView->SetHighColor(translucent);
		bView->FillRect(BRect(r.left+2,r.top+2,gauge_1*length_1,r.bottom-2));
	}
	
		bView->Sync();
		parent->DrawBitmapAsync(bitmap,bitmap->Bounds(),parent->Bounds());
		parent->Flush();
		parent->Sync();
*/
	//bitmap->Unlock();

//}
