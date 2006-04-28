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
#include <Alert.h>
#include <Screen.h>

#include "OSimApp.h"
#include "OSimWindow.h"
#include "IntroWindow.h"


const char *APP_SIGNATURE = "application/x-vnd.BU-OSim";

void OSimApp::AboutRequested() {
	
	BAlert *alert;
	status_t result;
	
	alert = new BAlert("About","OSim created by Bart Upchurch","OK");	
	result = alert->Go();
}

OSimApp::OSimApp()
			: BApplication(APP_SIGNATURE) {
	
	BRect windowRect;
	BScreen osimScreen;

	//Get the size of the screen to set the Window Size
	windowRect = osimScreen.Frame();
	windowRect.InsetBy(4.0,20.0);
	windowRect.left = 210.0;
	OSimWindow *mWindow = new OSimWindow(windowRect);		
	
	//Check the preferences to see if the Intro Window is checked to be displayed
	//If there is not a preference file then create one
	windowRect = osimScreen.Frame();
	windowRect.Set(windowRect.Width()/2-windowRect.Height()/2,40,
					windowRect.Width()/2+windowRect.Height()/2,windowRect.Height()-40);
	IntroWindow *iWindow = new IntroWindow(windowRect);	
	
	iWindow->Activate();
	
}


int main(void)
{
	new OSimApp;
	be_app->Run();
	delete be_app;
	return(B_OK);
}  
