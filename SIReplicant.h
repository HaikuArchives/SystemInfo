/*
 *	SystemInfoReplicant
 *
 *	Copyright 2002 Brent Miszalski
 *	Copyright 2012 Disreali		disreali[at]users[dot]sourceforge[dot]net
 *	All rights reserved. Distributed under the terms of the MIT License.
 *
 */


#ifndef _SYSTEM_INFO_REPLICANT_H
#define _SYSTEM_INFO_REPLICANT_H

#include <View.h>
#include <Rect.h>
#include <Window.h>
#include <Application.h>
#include <Path.h>
#include <Entry.h>
#include <FindDirectory.h>
#include <Directory.h>
#include <File.h>
#include <StringView.h>
#include <MessageRunner.h>
#include <Messenger.h>
#include <Bitmap.h>
#include "ImageView.h"

//#include "StatusBar.h"
//#include "CPUPercent.h"

//const int UPDATE_TIME_AMOUNT = 100000;
//const uint32 UPDATER = 'Init';
//const rgb_color translucent = {255,255,255,128};

class SIReplicant : public BWindow
{
	public:
		SIReplicant(BRect r);
		~SIReplicant();
		virtual bool QuitRequested();
		virtual void MessageReceived(BMessage* msg);
		//void Render();
	private:
		//BView* theView;
		//BBitmap* bitmap;
		BView* parent;
		ImageView* theImage;
	//	BView* bView;
		//StatusBar* CPU_0;
		//CPU_Percent* c1;
		
		//StatusBar* CPU_1;
		//CPU_Percent* c2;
		
		//BMessageRunner* updateR;
		
		//float gauge_1;
	//	double length_1;
		
	//	float gauge_2;
	//	double length_2;
};
#endif	//_SYSTEM_INFO_REPLICANT_H
