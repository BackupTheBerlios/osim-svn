/*
Copyright (c) 2004 Bart Upchurch

Permission is hereby granted, free of charge, to any person 
obtaining a copy of this software and associated documentation 
files (the "Software"), to deal in the Software without 
restriction, including without limitation the rights to use, 
copy, modify, merge, publish, distribute, sublicense, and/or 
sell copies of the Software, and to permit persons to whom 
the Software is furnished to do so, subject to the 
following conditions:

The above copyright notice and this permission notice shall 
be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR 
THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <Application.h>
#include <View.h>
#include <Rect.h>
#include <Control.h>
#include <Window.h>
#include <TabView.h>
#include <String.h>
#include <string.h>
#include <image.h>
#include <AppFileInfo.h>
#include <File.h>
#include <Roster.h>
#include <Directory.h>
#include <Path.h>
#include <Drivers.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <Input.h>
#include <Alert.h>
#include <Input.h>
#include <Screen.h>

#include "InTextView.h"
#include "Messages.h"
#include "TOCView.h"
#include "UnitView.h"

InTextView::InTextView(BRect rect, char *name) 
		: BView(rect, name, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE | B_FRAME_EVENTS |B_SUBPIXEL_PRECISE)
{

	BRect r;
	BTabView *tabView;
	BTab *tab;
	TOCView *tocView;
	
	r = Bounds();
	//r.InsetBy(5,5);
	
	tabView = new BTabView(r, "tab_view");
	tabView->SetViewColor(216,216,216,0);
	
	r = tabView->Bounds();
	r.InsetBy(5,5);
	r.bottom -= tabView->TabHeight();
	tab = new BTab();
	tocView = new TOCView(r, "TOC_View");
	tabView->AddTab(tocView, tab);
	tab->SetLabel("Table of Contents");
	tab = new BTab();
	unitView = new UnitView(r,"Unit_View");
	tabView->AddTab(unitView, tab);
	tab->SetLabel("Lesson"); 
	
	
	AddChild(tabView);
	
}


void InTextView::MessageReceived(BMessage *message)
{
	status_t result;
	//printf("OSimView Message Received\n");
	switch (message->what) {
		case UNIT_CHANGED:
			unitView->MessageReceived(message);
			break;
		case PREVIOUS_BUTTON:
			unitView->MessageReceived(message);
			break;
		case NEXT_BUTTON:
			unitView->MessageReceived(message);
			break;
		default: 
			BView::MessageReceived(message);
			break;
	}
}



void InTextView::AttachedToWindow()
{
	
}


