/*************************************************/
/* SystemInfoReplicant                           */
/* By Brent Miszalski (misza@ihug.com.au)		 */
/*************************************************/


#include "ImageView.h"

ImageView::ImageView(BRect frame)
	: BView(frame, "ImageView", B_FOLLOW_NONE, B_WILL_DRAW)
{
	SetViewColor(B_TRANSPARENT_COLOR);
	IsReplicant = false;
	system_info info;
	get_system_info(&info);
	if(info.cpu_count >=2)
		Is2CPU = true;
	else
		Is2CPU = false;
	
	BRect f = Frame();
	if(!Is2CPU && !((f.bottom - f.top) <= 105))
	{
		
		ResizeBy(0,-30);
		frame.bottom -= 30;
	}
	DoWeMove = false;
	//SetViewColor(B_TRANSPARENT_32_BIT);
	//SetViewColor(trblue);
	theVRoster.GetBootVolume(&boot);
	c1 = new CPU_Percent(0);
	c2 = new CPU_Percent(1);
	mem = new MemUsage;
	bitmap= new BBitmap(frame,B_RGB32,true);
	bitmap->Lock();
	bView = new BView(frame,"view",B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
	bitmap->AddChild(bView);
	bitmap->Unlock();
	
	BRect dr = Bounds();
	dr.top = dr.bottom - 7;
	dr.left = dr.right - 7;

	BDragger* dragger;
	dragger = new BDragger(dr, this, B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM, B_WILL_DRAW);
	AddChild(dragger);
	
	
}
ImageView::ImageView(BMessage *archive) : BView(archive)
{
	SetViewColor(B_TRANSPARENT_COLOR);
	IsReplicant = true;
	system_info info;
	get_system_info(&info);
	BRect frame = Bounds();
	if(info.cpu_count >=2)
		Is2CPU = true;
	else
		Is2CPU = false;

	theVRoster.GetBootVolume(&boot);
	c1 = new CPU_Percent(0);
	c2 = new CPU_Percent(1);
	mem = new MemUsage;
	
	bitmap= new BBitmap(frame,B_RGB32,true);
	bitmap->Lock();
	bView = new BView(frame,"view",B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
	bitmap->AddChild(bView);
	bitmap->Unlock();
		
	BMessenger mymsnger(this);
	BMessage increment(UPDATER);
	timeKeeper2 =  new BMessageRunner(mymsnger,&increment,UPDATE_TIME_AMOUNT,-1);
	


}
status_t ImageView::Archive(BMessage *archive, bool deep) const
{

	inherited::Archive(archive, deep);
	archive->AddString("add_on", "application/x-vnd.misza-SystemInfoReplicant");
/*	archive->AddBool("seconds",IsSecondsVisible);
	archive->AddBool("24hr",Is24HrTime);
	archive->AddBool("crazydate",IsAmericanDate);
	archive->AddBool("gmt_date",IsGMTDate);
	archive->AddBool("gmt_time",IsGMTTime);
	archive->AddBool("blinkybill",IsBlinking);
	archive->AddData("fgcolor",B_RGB_COLOR_TYPE,&fg_color,sizeof(rgb_color));
	archive->AddData("bgcolor",B_RGB_COLOR_TYPE,&bg_color,sizeof(rgb_color));
*/
	return B_OK;
}
BArchivable *ImageView::Instantiate(BMessage *data)
{
	if (!validate_instantiation(data, "ImageView"))
		return NULL;
	return new ImageView(data);
}
void
ImageView::AttachedToWindow()
{
	BRect f = Window()->Frame();
	
	if(!IsReplicant && !Is2CPU && ((f.bottom - f.top) == 135) && ((f.bottom - f.top) != 105))//!(((f.bottom - f.top)) < 105) && (f.bottom - f.top - 30 != 75))
	{
		(Window())->ResizeBy(0,-30);
	
	}
	if(!IsReplicant)
	{
		Window()->SetLook(B_NO_BORDER_WINDOW_LOOK);
		Window()->SetFeel(B_FLOATING_ALL_WINDOW_FEEL);
	}
	BMessenger mymsnger(this);
	BMessage increment(UPDATER);
	timeKeeper =  new BMessageRunner(mymsnger,&increment,UPDATE_TIME_AMOUNT,-1);
	//Invalidate();
	//Render();
}

void
ImageView::Draw(BRect updateRect)
{
	//SetViewColor(255,0,0);
	//DrawBitmapAsync(bitmap,Bounds(),Bounds());//fOffscreenImage, updateRect, updateRect);
	//Flush();
	//Sync();
	Render();
}

void ImageView::Render()
{
	//Is2CPU = false;
	bitmap->Lock();
	//create first bar
	bView->SetDrawingMode(B_OP_ALPHA);
	bView->SetHighColor(trblue);
	bView->SetLowColor(trblue);
	
	//bView->SetHighColor(51,61,106);
	//bView->SetLowColor(51,61,106);
	bView->FillRect(Bounds());
	bView->SetDrawingMode(B_OP_COPY);
	
	BRect r(60,10,164,25); 
	bView->SetHighColor(255,255,255);
	
	c1->Update();
	gauge_1 = c1->Percentage();
	
	bView->StrokeLine(BPoint(r.left,r.top),BPoint(r.right-1,r.top));
		bView->StrokeLine(BPoint(r.left+1,r.top+1),BPoint(r.right-1,r.top+1));
		
	bView->StrokeLine(BPoint(r.right,r.top),BPoint(r.right,r.bottom));
		bView->StrokeLine(BPoint(r.right-1,r.top+1),BPoint(r.right-1,r.bottom-1));
		
	bView->StrokeLine(BPoint(r.right,r.bottom),BPoint(r.left,r.bottom));
		bView->StrokeLine(BPoint(r.right-1,r.bottom-1),BPoint(r.left+1,r.bottom-1));
	
	bView->StrokeLine(BPoint(r.left,r.bottom),BPoint(r.left,r.top));
		bView->StrokeLine(BPoint(r.left+1,r.bottom-1),BPoint(r.left+1,r.top+1));
	
	bView->MovePenTo(r.left-50,r.bottom);
	bView->SetFont(be_bold_font);
	if(!Is2CPU)
		bView->DrawString("CPU: ");
	else
		bView->DrawString("CPU 0: ");
	
	if(gauge_1 != 0.0)
	{
		bView->SetDrawingMode(B_OP_ALPHA);
		bView->SetHighColor(translucent);
		bView->FillRect(BRect(r.left+2,r.top+2,r.left+2+gauge_1*100,r.bottom-2));
	}
	
	if(Is2CPU)
	{
	bView->SetDrawingMode(B_OP_COPY);
	
	//create 2nd bar
	r = BRect(60,35,164,50); 
	bView->SetHighColor(255,255,255);
	
	c2->Update();
	gauge_2 = c2->Percentage();
	
	bView->StrokeLine(BPoint(r.left,r.top),BPoint(r.right-1,r.top));
		bView->StrokeLine(BPoint(r.left+1,r.top+1),BPoint(r.right-1,r.top+1));
		
	bView->StrokeLine(BPoint(r.right,r.top),BPoint(r.right,r.bottom));
		bView->StrokeLine(BPoint(r.right-1,r.top+1),BPoint(r.right-1,r.bottom-1));
		
	bView->StrokeLine(BPoint(r.right,r.bottom),BPoint(r.left,r.bottom));
		bView->StrokeLine(BPoint(r.right-1,r.bottom-1),BPoint(r.left+1,r.bottom-1));
	
	bView->StrokeLine(BPoint(r.left,r.bottom),BPoint(r.left,r.top));
		bView->StrokeLine(BPoint(r.left+1,r.bottom-1),BPoint(r.left+1,r.top+1));
	
	bView->MovePenTo(r.left-50,r.bottom);
	bView->DrawString("CPU 1: ");
	
	if(gauge_2 != 0.0)
	{
		bView->SetDrawingMode(B_OP_ALPHA);
		bView->SetHighColor(translucent);
		bView->FillRect(BRect(r.left+2,r.top+2,r.left+2+gauge_2*100,r.bottom-2));
	}
	}
	bView->SetDrawingMode(B_OP_COPY);
	
	//create 3rd bar (MEM USAGE)
	if(!Is2CPU)
		r = BRect(60,35,164,50);
	else
		r = BRect(60,60,164,75); 
	
	bView->SetHighColor(255,255,255);
	mem->Update();
	gauge_3 = (mem->Used()) / (mem->Total());

	bView->StrokeLine(BPoint(r.left,r.top),BPoint(r.right-1,r.top));
		bView->StrokeLine(BPoint(r.left+1,r.top+1),BPoint(r.right-1,r.top+1));
		
	bView->StrokeLine(BPoint(r.right,r.top),BPoint(r.right,r.bottom));
		bView->StrokeLine(BPoint(r.right-1,r.top+1),BPoint(r.right-1,r.bottom-1));
		
	bView->StrokeLine(BPoint(r.right,r.bottom),BPoint(r.left,r.bottom));
		bView->StrokeLine(BPoint(r.right-1,r.bottom-1),BPoint(r.left+1,r.bottom-1));
	
	bView->StrokeLine(BPoint(r.left,r.bottom),BPoint(r.left,r.top));
		bView->StrokeLine(BPoint(r.left+1,r.bottom-1),BPoint(r.left+1,r.top+1));
	
	bView->MovePenTo(r.left-50,r.bottom);
	bView->DrawString("MEM: ");
	
	
	if(gauge_3 != 0.0)
	{
		bView->SetDrawingMode(B_OP_ALPHA);
		bView->SetHighColor(translucent);
		bView->FillRect(BRect(r.left+2,r.top+2,r.left+2+gauge_3*100,r.bottom-2));
	}	
	
	bView->SetDrawingMode(B_OP_COPY);
	
	//create DISK CAPACITY
	if(!Is2CPU)
		r = BRect(60,60,164,75);
	else
		r = BRect(60,85,164,100); 
	
	
	//r = BRect(60,85,164,100); 
	bView->SetHighColor(255,255,255);
	
	total = (boot.Capacity())/(1024*1024);
	free = (boot.FreeBytes())/(1024*1024);
	used = total - free;
	
	
	gauge_4 = used/total;

	bView->StrokeLine(BPoint(r.left,r.top),BPoint(r.right-1,r.top));
		bView->StrokeLine(BPoint(r.left+1,r.top+1),BPoint(r.right-1,r.top+1));
		
	bView->StrokeLine(BPoint(r.right,r.top),BPoint(r.right,r.bottom));
		bView->StrokeLine(BPoint(r.right-1,r.top+1),BPoint(r.right-1,r.bottom-1));
		
	bView->StrokeLine(BPoint(r.right,r.bottom),BPoint(r.left,r.bottom));
		bView->StrokeLine(BPoint(r.right-1,r.bottom-1),BPoint(r.left+1,r.bottom-1));
	
	bView->StrokeLine(BPoint(r.left,r.bottom),BPoint(r.left,r.top));
		bView->StrokeLine(BPoint(r.left+1,r.bottom-1),BPoint(r.left+1,r.top+1));
	
	bView->MovePenTo(r.left-50,r.bottom);
	char buffer[B_FILE_NAME_LENGTH];
	boot.GetName(buffer);
	bView->DrawString(buffer);
	
	
	if(gauge_4 != 0.0)
	{
		bView->SetDrawingMode(B_OP_ALPHA);
		bView->SetHighColor(translucent);
		bView->FillRect(BRect(r.left+2,r.top+2,r.left+2+gauge_4*100,r.bottom-2));
	}
	
	//uptime
	if(!Is2CPU)
		r = BRect(60,85,164,100);
	else
		r = BRect(60,110,164,125); 
	
	//r = BRect(60,110,164,125);
	
	sec = (system_time()/1000)/1000;
	min = sec/60;
	hours = min/60;
	days = hours/24;
	
	uptime = "";
	
	//if(hours % 24)	
	hours %= 24;
	//if(min % 60)	
	min %= 60;
	sec %=60;
	
	if(days == 0 && hours == 0 && min == 0)
		uptime << sec << "s";
	else if (days == 0 && hours == 0)
		uptime << min << "m " << sec << "s";
	else if(days == 0)
		uptime << hours << "h " 
	<< min << "m " << sec << "s";
	else 
		uptime << days << "d " << hours << "h " 
	<< min << "m " << sec << "s";
	
	bView->SetDrawingMode(B_OP_COPY);
	
	bView->MovePenTo(r.left-50,r.bottom);
	bView->DrawString("Uptime: ");
	bView->SetDrawingMode(B_OP_ALPHA);
	bView->MovePenTo(r.left,r.bottom);
	bView->DrawString(uptime.String());
	
		bView->SetDrawingMode(B_OP_ALPHA);
		bView->Sync();
		DrawBitmapAsync(bitmap,Bounds(),Bounds());
		Flush();
		Sync();

	bitmap->Unlock();

}

void ImageView::Pulse()
{
	Render();
}

ImageView::~ImageView()
{
}

void ImageView::MouseDown(BPoint point)
{
	if(!IsReplicant)
	{
	uint32 buttons;
	GetMouse(&point,&buttons);
	
	if(buttons == B_PRIMARY_MOUSE_BUTTON)
	{
		DoWeMove = true;
		ConvertToScreen(&point);
		thePoint = point;
	}
	}
	
}
void ImageView::MouseUp(BPoint point)
{
	if(!IsReplicant)
		DoWeMove = false;
	
}
void ImageView::MouseMoved(BPoint point,uint32 transit,const BMessage* msg)
{
	if(!IsReplicant)
	{
	BPoint cursor;
	uint32 buttons;
	
	GetMouse(&cursor,&buttons);
		
	if(DoWeMove && buttons == B_PRIMARY_MOUSE_BUTTON)
	{
		ConvertToScreen(&point);
		Window()->MoveBy(point.x - thePoint.x,point.y - thePoint.y );
		thePoint = point;
	}
	
	}
}

void ImageView::MessageReceived(BMessage* msg)
{

	switch(msg->what)
	{
	case UPDATER:
	{
		Render();
	}break;
	
	case B_ABOUT_REQUESTED:
	{
	BAlert *about = new BAlert("about", "SystemInfo b2.0\nBy Brent Miszalski\nmisza@ihug.com.au", "I Love BeOS!");
		about->Go();
		
	
	}break;
	default:
		BView::MessageReceived(msg);
	break;
		
	}
}















