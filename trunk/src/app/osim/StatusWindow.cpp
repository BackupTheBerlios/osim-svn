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
#include <Rect.h>
#include <stdio.h>
#include <StatusBar.h>


#include "StatusWindow.h"

void StatusWindow::MessageReceived(BMessage *message)
{
	//status_t result;
	
	//printf("OSimWindow Message Received\n");
	
	switch (message->what) {
		case STATUS_MAX:
			float max;
			printf("Set Max\n");
			message->FindFloat("max",&max);
			statusView->SetMaxValue(max);
			break;
		case STATUS_UPDATE:
			float delta;
			printf("Update delta\n");
			message->FindFloat("delta",&delta);
			statusView->Update(delta);
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}

StatusWindow::StatusWindow(BRect frame)
			: BWindow(frame, "StatusWindow", B_BORDERED_WINDOW, B_MODAL_ALL_WINDOW_FEEL) {
	
	BRect statusRect = Bounds();
	statusView = new BStatusBar(statusRect,"statusView","Searching For Devices");
	AddChild(statusView); 
	//statusView->MakeFocus();
	Show(); 
}