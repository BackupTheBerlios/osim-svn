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
#include <Window.h>
#include <Menu.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include <Alert.h>
#include <image.h>
#include <Path.h>
#include <Roster.h>
#include <Directory.h>
#include <String.h>
#include <stdio.h>
#include <Point.h>

#include "OSimWindow.h"
#include "OSimView.h"
#include "Constants.h"
#include "Messages.h"
#include "TextDetails.h"


OSimWindow::OSimWindow(BRect frame)
			: BWindow(frame, "OSim", B_TITLED_WINDOW, B_QUIT_ON_WINDOW_CLOSE | B_WILL_ACCEPT_FIRST_CLICK) {
	
		
	//create MenuBar
	BRect menuBarRect;
	BMenuBar *menuBar;
	
	//Set the Boundaries of the MenuBar
	menuBarRect = Bounds();
	menuBarRect.bottom = MENU_BAR_HEIGHT;
	
	menuBar = new BMenuBar(menuBarRect, "MenuBar");
	
	AddChild(menuBar);
	
	//create the "File" Menu
	BMenu *menu;
	
	menu = new BMenu("File");
	
	// Use menuItem to Set marked options
	BMenuItem *menuItem;
	
	//add the "File" Menu to the Menu Bar
	menuBar->AddItem(menu);
	
	//Add items to the "File" Menu
	menu->AddItem(new BMenuItem("Quit",new BMessage(B_QUIT_REQUESTED)));	
	
	menu = new BMenu("View");
	
	//add the "View" Menu to the Menu Bar
	menuBar->AddItem(menu);
	
	menu->AddItem(new BMenuItem("Text Information...", new BMessage(MENU_VIEW_TEXT)));

	menu->AddItem(menuItemRelationship = new BMenuItem("Relationships", new BMessage(MENU_VIEW_RELATIONSHIP)));
	menuItemRelationship->SetMarked(false);
	showRelationshipFlag = false;
	
	//Create the settings menu 
	menu = new BMenu("Settings"); 
	menuBar->AddItem(menu);
	BMenu *subMenu;
	
	//Create the Customize Color Menu Option
	subMenu = new BMenu("Customize Colors");
	menu->AddItem(subMenu);
	
	BMenu *categoryMenu;
	BMenu *relateMenu;
	ColorMenuItem *colorItem;
	
	// Set the Color for relationships
	categoryMenu = new BMenu("Relationships");
	subMenu->AddItem(categoryMenu);
	
	relateMenu = new BMenu("Application:Library");
	categoryMenu->AddItem(relateMenu);
	relateMenu->SetRadioMode(true);
	
	BMessage *menuMsg;	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",255);
	menuMsg->AddInt8("green",0);
	menuMsg->AddInt8("blue",0);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	colorItem->SetMarked(true);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",0);
	menuMsg->AddInt8("green",255);
	menuMsg->AddInt8("blue",0);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",0);
	menuMsg->AddInt8("green",0);
	menuMsg->AddInt8("blue",255);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",255);
	menuMsg->AddInt8("green",0);
	menuMsg->AddInt8("blue",255);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",0);
	menuMsg->AddInt8("green",255);
	menuMsg->AddInt8("blue",255);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",255);
	menuMsg->AddInt8("green",255);
	menuMsg->AddInt8("blue",0);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	relateMenu = new BMenu("Application:System Library");
	categoryMenu->AddItem(relateMenu);
	relateMenu->SetRadioMode(true);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",255);
	menuMsg->AddInt8("green",0);
	menuMsg->AddInt8("blue",0);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	colorItem->SetMarked(true);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",0);
	menuMsg->AddInt8("green",255);
	menuMsg->AddInt8("blue",0);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",0);
	menuMsg->AddInt8("green",0);
	menuMsg->AddInt8("blue",255);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",255);
	menuMsg->AddInt8("green",0);
	menuMsg->AddInt8("blue",255);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",0);
	menuMsg->AddInt8("green",255);
	menuMsg->AddInt8("blue",255);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",255);
	menuMsg->AddInt8("green",255);
	menuMsg->AddInt8("blue",0);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	relateMenu = new BMenu("Kernel:System Library");
	categoryMenu->AddItem(relateMenu);
	relateMenu->SetRadioMode(true);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",255);
	menuMsg->AddInt8("green",0);
	menuMsg->AddInt8("blue",0);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	colorItem->SetMarked(true);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",0);
	menuMsg->AddInt8("green",255);
	menuMsg->AddInt8("blue",0);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",0);
	menuMsg->AddInt8("green",0);
	menuMsg->AddInt8("blue",255);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",255);
	menuMsg->AddInt8("green",0);
	menuMsg->AddInt8("blue",255);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",0);
	menuMsg->AddInt8("green",255);
	menuMsg->AddInt8("blue",255);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",255);
	menuMsg->AddInt8("green",255);
	menuMsg->AddInt8("blue",0);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	relateMenu = new BMenu("Kernel:Module");
	categoryMenu->AddItem(relateMenu);
	relateMenu->SetRadioMode(true);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",255);
	menuMsg->AddInt8("green",0);
	menuMsg->AddInt8("blue",0);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	colorItem->SetMarked(true);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",0);
	menuMsg->AddInt8("green",255);
	menuMsg->AddInt8("blue",0);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",0);
	menuMsg->AddInt8("green",0);
	menuMsg->AddInt8("blue",255);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",255);
	menuMsg->AddInt8("green",0);
	menuMsg->AddInt8("blue",255);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",0);
	menuMsg->AddInt8("green",255);
	menuMsg->AddInt8("blue",255);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	menuMsg = new BMessage(MENU_SET_COLOR_RELATE);
	menuMsg->AddInt8("red",255);
	menuMsg->AddInt8("green",255);
	menuMsg->AddInt8("blue",0);
	
	colorItem = new ColorMenuItem(menuMsg);
	relateMenu->AddItem(colorItem);
	
	//Set the Color for background
	categoryMenu = new BMenu("Background");
	subMenu->AddItem(categoryMenu);
	
	//Sets the color for the inside view and line draw
	categoryMenu = new BMenu("Focus");
	subMenu->AddItem(categoryMenu);
			
	//Create Refresh Rate Settings
	subMenu = new BMenu("Update Interval");
	menu->AddItem(subMenu);
		
	int8 refreshRate = 15; 
	menuMsg = new BMessage(MENU_SETTINGS_REFRESH);
	menuMsg->AddInt8("refreshRate",refreshRate);
	subMenu->AddItem(new BMenuItem("15 Seconds",menuMsg));
	refreshRate = 10;
	menuMsg->ReplaceInt8("refreshRate",refreshRate);
	subMenu->AddItem(new BMenuItem("10 Seconds",menuMsg));
	refreshRate = 5;
	menuMsg->ReplaceInt8("refreshRate",refreshRate);
	subMenu->AddItem(new BMenuItem("5 Seconds",menuMsg));
	refreshRate = 3;
	menuMsg->ReplaceInt8("refreshRate",refreshRate);
	subMenu->AddItem(menuItem = new BMenuItem("3 Seconds",menuMsg));
	menuItem->SetMarked(true);
	refreshRate = 0;
	menuMsg->ReplaceInt8("refreshRate",refreshRate);
	subMenu->AddItem(new BMenuItem("Disabled",menuMsg));
	subMenu->SetRadioMode(true);
	
	//Create the Software Component Update
	subMenu = new BMenu("Update OS Components");
	menu->AddItem(subMenu);
	
	//Create the help menu
	menu = new BMenu("Help");
	
	//add the "Help" Menu to the Menu Bar
	menuBar->AddItem(menu);
	
	//Add items to the "Help" Menu
	//BMenuItem *menuItem;
	
	menu->AddItem(new BMenuItem("About",new BMessage(B_ABOUT_REQUESTED)));
	//Create a View
	//viewRect = Bounds();
	//viewRect.top = MENU_BAR_HEIGHT + 1;
	//viewRect.InsetBy(10.0,10.0);
	
	//create a view within the main view inset by 10.0
	//viewRect.Set(15.0,frame.Height()*0.25,frame.Width()-30,frame.Height()-60);
	//set deault pluginRect based off of viewRect
    viewRect = Bounds();
	viewRect.top = MENU_BAR_HEIGHT + 1;
	//set a black background for the whole window
	BView *blackBackView = new BView(viewRect,"BlackView",B_FOLLOW_ALL_SIDES, B_FULL_UPDATE_ON_RESIZE);
	blackBackView->SetViewColor(0,0,0);
	AddChild(blackBackView);
	   
	
	BRect oRect;
	oRect.left = 10.0;
	oRect.right = viewRect.right - viewRect.left - 10.0;
	oRect.top = 10.0;
	oRect.bottom = viewRect.bottom - viewRect.top - 10.0;
	oView = new OSimView(oRect,"OSimView");
	oView->SetViewColor(0,0,0);
	//oView->SetHighColor(0,0,0);
	//oView->SetLowColor(255,255,255);
	blackBackView->AddChild(oView); 
	oView->MakeFocus();
	Show(); 
}

OSimWindow::~OSimWindow() {
	
}

void OSimWindow::MessageReceived(BMessage *message)
{
	status_t result;
	status_t error;
	//printf("OSimWindow Message Received\n");
	BPoint appPoint;
	BPoint libPoint;
	switch (message->what) {
		case OSIMAGE_SELECTED:
			
			break;
		case MENU_VIEW_TEXT:
			//open detailed text information in new window
			result = textDetails();
			break;
		case B_ABOUT_REQUESTED:
			be_app->AboutRequested();
			break;
		case MENU_VIEW_IM_ENABLE:
		
			break;
		case MENU_VIEW_IM_DISABLE:
			
			break;
		case DRAW_LINE:
		//	BPoint appPoint;
		//	BPoint libPoint;
			if (showRelationshipFlag) {
				int8 red, green, blue;
				error = message->FindPoint("appPoint",&appPoint);
				error = message->FindPoint("libPoint",&libPoint);
				error = message->FindInt8("red",&red);
				error = message->FindInt8("green",&green);
				error = message->FindInt8("blue",&blue);
				oView->SetHighColor((uint8)red,(uint8)green,(uint8)blue);
				oView->StrokeLine(appPoint, libPoint);
				oView->SetHighColor(0,0,0);
		//		printf("Draw Line\n");
			}
			
			//delete message;
			break;
		case MENU_VIEW_RELATIONSHIP:
			
			showRelationshipFlag = !(showRelationshipFlag);
			if (!(showRelationshipFlag)) {
				menuItemRelationship->SetMarked(false);
				oView->Invalidate();		
			} else {
				menuItemRelationship->SetMarked(true);
			}	
			
			//delete message;
			break;
		case MENU_SETTINGS_REFRESH:
			int8 refreshRate;
			uint32 rate;
			error = message->FindInt8("refreshRate",&refreshRate);
			if (!(error)) {
				rate = refreshRate * 1000000;
				SetPulseRate(rate);
			}
			break;
		default: 
			//pluginView->MessageReceived(message);
			BWindow::MessageReceived(message);
			break;
	}
}
