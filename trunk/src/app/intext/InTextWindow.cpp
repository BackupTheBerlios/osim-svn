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

#include "InTextView.h"
#include "InTextWindow.h"
#include "Constants.h"
#include "Messages.h"
#include "UnitView.h"


InTextWindow::InTextWindow(BRect frame)
			: BWindow(frame, "Interactive Textbook", B_TITLED_WINDOW, B_QUIT_ON_WINDOW_CLOSE | B_WILL_ACCEPT_FIRST_CLICK | B_NOT_RESIZABLE) {
	

	
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
	mainView = new InTextView(viewRect,"MainView");
	AddChild(mainView);
	
	Show(); 
}

InTextWindow::~InTextWindow() {
	
}

void InTextWindow::MessageReceived(BMessage *message)
{
	status_t result;
	status_t error;
	//printf("OSimWindow Message Received\n");
	BPoint appPoint;
	BPoint libPoint;
	switch (message->what) {
		case UNIT_CHANGED:
			PostMessage(message,mainView);
			break;
		case PREVIOUS_BUTTON:
			PostMessage(message,mainView);
			break;
		case NEXT_BUTTON:
			PostMessage(message,mainView);
			break;
		default: 
			BWindow::MessageReceived(message);
			break;
	}
}
