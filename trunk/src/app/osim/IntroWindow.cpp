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
#include <Button.h>
#include <CheckBox.h>
#include <TextView.h>
#include <ScrollView.h>

#include "LogoView.h"
#include "IntroWindow.h"

IntroWindow::IntroWindow(BRect frame)
			: BWindow(frame, "IntroWindow", B_BORDERED_WINDOW, B_MODAL_ALL_WINDOW_FEEL | B_WILL_ACCEPT_FIRST_CLICK) {
	
	//Create a top View to set the Background Color of the Window
	topView = new BView(Bounds(),"topView",B_FOLLOW_ALL_SIDES,B_WILL_DRAW);
	topView->SetViewColor(222,222,222);
	AddChild(topView);
	
	//Create the Logo -- User the Logo View
	viewRect.Set(15.0,15.0,frame.Width()-15,frame.Height()*0.25-15);
	logoView = new LogoView(viewRect,"LogoView");
	topView->AddChild(logoView);
	
	//Create the Text Box
	viewRect.Set(15.0,frame.Height()*0.25,frame.Width()-30,frame.Height()-60);
	textRect.left = TEXT_INSET;
	textRect.right = viewRect.right - viewRect.left - TEXT_INSET;
	textRect.top = TEXT_INSET;
	textRect.bottom = viewRect.bottom - viewRect.top - TEXT_INSET;
	introTextView = new BTextView(viewRect,"IntroText",textRect,B_FOLLOW_ALL_SIDES,B_WILL_DRAW);
	BFont font;
	font.SetSize(20.0);
	introTextView->SetFontAndColor(&font);
	introTextView->Insert(INTRO_TEXT);
	textScrollView = new BScrollView("TextScrollView",introTextView,
		B_FOLLOW_LEFT | B_FOLLOW_TOP, 0, false, true);
	topView->AddChild(textScrollView);
	
	// Create the Button
	viewRect.Set(frame.Width()-100,frame.Height()-50,frame.Width()-15,frame.Height()-15);
	okButton = new BButton(viewRect,"OKButton","OK",new BMessage(INTRO_OK_BUTTON));
	topView->AddChild(okButton);
	
	// Create the CheckBox
	viewRect.Set(frame.Width()-225,frame.Height()-45,frame.Width()-125,frame.Height()-15);
	startupCheckBox = new BCheckBox(viewRect,"StartupCheck","Show at Startup",new BMessage(INTRO_CHECKBOX));
	topView->AddChild(startupCheckBox);
	Show(); 
}

void IntroWindow::MessageReceived(BMessage *message)
{
		
	switch (message->what) {
		case INTRO_OK_BUTTON:
			Lock();
			Quit();
			break;
		case INTRO_CHECKBOX:
			
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}

