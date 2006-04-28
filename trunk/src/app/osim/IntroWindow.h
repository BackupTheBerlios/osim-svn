/*
Copyright (c) 2004 Bart Upchurch

Permission is hereby granted, free of charge, to any person 
obtaining a copy of this software and associated documentation 
files (the "Software"), to deal in the Software without 
restriction, including without limitation the rights to use, 
copy, modify, merge, publish, distribute, sublicense, and/or 
sell copies of the Software, and to permit persons to whom 
the Software is furnished to do so, subject to the following conditions:

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

#ifndef __INTROWINDOW_H__
#define __INTROWINDOW_H__

#include <Window.h>

#include "LogoView.h"

#define TEXT_INSET 3.0
#define INTRO_TEXT "Welcome to OSim, the Operating System Simulator. \
The software's goal is to teach generic operating system (OS) concepts. Every \
box drawn on the screen represents an OS component. The components are \
organized into layers.  Components with a common purpose are placed in the \
same layer. Instructional modules, accessible through Interactive Textbook, provide \
information on the operating system components and how they interact. The simulator \
displays OS parts in realtime. If an aplication is open or closed, the simulator \
will update OSim's window.  Start with the Introduction to OSim in the Interactive \
Textbook. Then click through the Introduction to Operating Systems for a walkthrough \
of the simulator."

#define INTRO_OK_BUTTON  		'iokb'
#define INTRO_CHECKBOX  		'ichk'

class IntroWindow : public BWindow {
	public:
						IntroWindow(BRect frame);
		virtual void	MessageReceived(BMessage *message);
	
	
	private:
		BView *topView;
		BRect viewRect, textRect;
		BButton *okButton;
		BCheckBox *startupCheckBox;
		BTextView *introTextView;
		BScrollView *textScrollView;
		LogoView *logoView;
};

#endif