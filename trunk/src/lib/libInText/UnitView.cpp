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
#include <Button.h>
#include <ScrollView.h>

#include "UnitView.h"
#include "Messages.h"
#include "XMLView.h"

UnitView::UnitView(BRect rect, char *name) 
		: BView(rect, name, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE | B_FRAME_EVENTS |B_SUBPIXEL_PRECISE)
{
	fCurrentPage = 1;
	fMaxPages = 1;
	
	SetViewColor(216,216,216);
	//Place a previous and back button at the bottom
	BRect buttonRect;
	buttonRect = Bounds();
	buttonRect.left = 15;
	buttonRect.right = 75;
	buttonRect.top = buttonRect.bottom - 40;
	buttonRect.bottom = buttonRect.bottom - 20;
	fPreviousButton = new BButton(buttonRect,"previous","<-Previous", new BMessage(PREVIOUS_BUTTON));
	AddChild(fPreviousButton);
	
	buttonRect = Bounds();
	buttonRect.left = buttonRect.right - 75;
	buttonRect.right = buttonRect.right - 15;
	buttonRect.top = buttonRect.bottom - 40;
	buttonRect.bottom = buttonRect.bottom - 20;
	fNextButton = new BButton(buttonRect,"next","Next->", new BMessage(NEXT_BUTTON));
	AddChild(fNextButton);
	
	xmlView = NULL;	
	
	if (fCurrentPage == 1) {
		fPreviousButton->SetEnabled(false);
	} else {
		fPreviousButton->SetEnabled(true);
	}
	
	if (fCurrentPage == fMaxPages) {
		fNextButton->SetEnabled(false);
	} else {
		fNextButton->SetEnabled(true);
	}
}

void UnitView::Draw(BRect updateRect) {
	BRect buttonRect;
	buttonRect = Bounds();
	MovePenTo(80,buttonRect.bottom - 45);
	
	BString pages;
	pages << fCurrentPage;
	pages << " of " << fMaxPages;
	
	DrawString(pages.String());
}

void UnitView::MessageReceived(BMessage *message)
{
	status_t result;
	//printf("OSimView Message Received\n");
	BRect viewRect;
	entry_ref entry;
	BEntry currentEntry;
	switch (message->what) {
		case UNIT_CHANGED:
			//change unit file view
			printf("Unit Changed\n");
			if (xmlView == NULL) {
				viewRect = Bounds();
				viewRect.InsetBy(5.0,5.0);
				viewRect.bottom = viewRect.bottom - 60;
				viewRect.right -= 15;
				xmlView = new XMLView(viewRect,"XMLView");
				fScrollView = new BScrollView("xml_scroll",xmlView, B_FOLLOW_ALL_SIDES, 0, false, true);
				AddChild(fScrollView);
			}
			message->FindRef("entry",&entry);
			currentEntry.SetTo(&entry);
			xmlView->SetRef(&currentEntry);
			xmlView->CurrentPage(&fCurrentPage);
			xmlView->PageCount(&fMaxPages);
			if (fCurrentPage == 1) {
				fPreviousButton->SetEnabled(false);
			} else {
				fPreviousButton->SetEnabled(true);
			}
			if (fCurrentPage == fMaxPages) {
				fNextButton->SetEnabled(false);
			} else {
				fNextButton->SetEnabled(true);
			}
			break;
		case PREVIOUS_BUTTON:
			if (xmlView != NULL) {
				xmlView->PreviousButton();
				xmlView->CurrentPage(&fCurrentPage);
				
			}
			
			fNextButton->SetEnabled(true);
			
			if (fCurrentPage == 1) {
				fPreviousButton->SetEnabled(false);
			} else {
				fPreviousButton->SetEnabled(true);
			}
			Invalidate();
			break;
		case NEXT_BUTTON:
			if (xmlView != NULL) {
				xmlView->NextButton();
				xmlView->CurrentPage(&fCurrentPage);
				
			}
			
			fPreviousButton->SetEnabled(true);
			
			if (fCurrentPage == fMaxPages) {
				fNextButton->SetEnabled(false);
			} else {
				fNextButton->SetEnabled(true);
			}
			Invalidate();
			break;		
		default: 
			BView::MessageReceived(message);
			break;
	}
}



