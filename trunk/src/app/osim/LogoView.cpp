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

#include <Window.h>
#include <View.h>
#include <Message.h>

#include "LogoView.h"

LogoView::LogoView(BRect frame, char *name, bool animation, int32 animationTime) 
		:BView(frame, name, B_FOLLOW_ALL_SIDES, B_WILL_DRAW |B_FULL_UPDATE_ON_RESIZE |B_FRAME_EVENTS) {

	SetViewColor(0,0,0);
	SetHighColor(255,255,255);
	SetLowColor(0,0,0);
	showAnimation = animation;	
	aTime = animationTime;
}
/*
	The logo consists of spelling OSim in a view simular to the program
	Each letter has 13 layers, 7 box layers and 6 line layers
	
	Note:Everything must be based off of percentages
*/
void LogoView::Draw(BRect updateRect) {	
	
	//SetViewColor(0,0,0);
	SetHighColor(255,255,255);
	SetLowColor(0,0,0);
	
	BRect letterRect;
	BRect partRect;
	BPoint topPoint, bottomPoint;
	//width of each square
	float width = (Bounds()).Width()/4*0.08;
	
	//Draw the O
	letterRect = Bounds();
	letterRect.Set(letterRect.left,letterRect.top,letterRect.Width()/4,letterRect.Height());
	StrokeRect(letterRect);
	//letterRect.InsetBy(3.0,3.0);
	//StrokeRect(letterRect);
		
	//Stroke each layer at a time
	partRect.Set(letterRect.Width()/2-width,letterRect.top,
				 letterRect.Width()/2+width,letterRect.Height()/13*1);
	StrokeRect(partRect);
	topPoint.Set(letterRect.Width()/2,letterRect.Height()/13*1);
		
	partRect.Set(letterRect.Width()/9*3-width,letterRect.Height()/13*2,
				letterRect.Width()/9*3+width,letterRect.Height()/13*3);
	StrokeRect(partRect);
	bottomPoint.Set(letterRect.Width()/9*3,letterRect.Height()/13*2);
	//StrokeLine(topPoint,bottomPoint);
		
	partRect.Set(letterRect.Width()/9*6-width,letterRect.Height()/13*2,
				letterRect.Width()/9*6+width,letterRect.Height()/13*3);
	StrokeRect(partRect);
	bottomPoint.Set(letterRect.Width()/9*6,letterRect.Height()/13*2);
	//StrokeLine(topPoint,bottomPoint);
	
	partRect.Set(letterRect.Width()/10*2-width,letterRect.Height()/13*4,
				letterRect.Width()/10*2+width,letterRect.Height()/13*5);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()/10*8-width,letterRect.Height()/13*4,
				letterRect.Width()/10*8+width,letterRect.Height()/13*5);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.left,letterRect.Height()/13*6,
				letterRect.left+2*width,letterRect.Height()/13*7);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.right-2*width,letterRect.Height()/13*6,
				letterRect.right,letterRect.Height()/13*7);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()/10*2-width,letterRect.Height()/13*8,
				letterRect.Width()/10*2+width,letterRect.Height()/13*9);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()/10*8-width,letterRect.Height()/13*8,
				letterRect.Width()/10*8+width,letterRect.Height()/13*9);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()/9*3-width,letterRect.Height()/13*10,
				letterRect.Width()/9*3+width,letterRect.Height()/13*11);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()/9*6-width,letterRect.Height()/13*10,
				letterRect.Width()/9*6+width,letterRect.Height()/13*11);
	StrokeRect(partRect);
		
	partRect.Set(letterRect.Width()/2-width,letterRect.Height()/13*12,
				 letterRect.Width()/2+width,letterRect.Height()/13*13);
	StrokeRect(partRect);
	
	
	//Draw the S
	letterRect = Bounds();
	letterRect.Set(letterRect.Width()/4,letterRect.top,letterRect.Width()/4*2,letterRect.Height());
	StrokeRect(letterRect);
	//letterRect.InsetBy(3.0,3.0);
	//StrokeRect(letterRect);
	//Stroke each Layer
	partRect.Set(letterRect.right-2*width,letterRect.top,
				letterRect.right,letterRect.Height()/13*1);
	StrokeRect(partRect);
	topPoint.Set(letterRect.right-width,letterRect.Height()/13*1);
	
	partRect.Set(letterRect.Width()+letterRect.Width()/2-width,letterRect.top,
				letterRect.Width()+letterRect.Width()/2+width,letterRect.Height()/13*1);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.left,letterRect.Height()/13*2,
				letterRect.left+2*width,letterRect.Height()/13*3);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.left,letterRect.Height()/13*4,
				letterRect.left+2*width,letterRect.Height()/13*5);
	StrokeRect(partRect);
	bottomPoint.Set(letterRect.left+width,letterRect.Height()/13*4);
	//StrokeLine(topPoint,bottomPoint);
	topPoint.Set(letterRect.left+width,letterRect.Height()/13*5);
	
	partRect.Set(letterRect.Width()+letterRect.Width()/2-width,letterRect.Height()/13*6,
				letterRect.Width()+letterRect.Width()/2+width,letterRect.Height()/13*7);
	StrokeRect(partRect);
	bottomPoint.Set(letterRect.Width()+letterRect.Width()/2,letterRect.Height()/13*6);
	//StrokeLine(topPoint,bottomPoint);
	topPoint.Set(letterRect.Width()+letterRect.Width()/2,letterRect.Height()/13*7);
	
	partRect.Set(letterRect.right-2*width,letterRect.Height()/13*8,
				letterRect.right,letterRect.Height()/13*9);
	StrokeRect(partRect);
	bottomPoint.Set(letterRect.right-width,letterRect.Height()/13*8);
	//StrokeLine(topPoint,bottomPoint);
	topPoint.Set(letterRect.right-width,letterRect.Height()/13*9);
	
	partRect.Set(letterRect.right-2*width,letterRect.Height()/13*10,
				letterRect.right,letterRect.Height()/13*11);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()+letterRect.Width()/2-width,letterRect.Height()/13*12,
				letterRect.Width()+letterRect.Width()/2+width,letterRect.Height()/13*13);
	StrokeRect(partRect);
	bottomPoint.Set(letterRect.Width()+letterRect.Width()/2,letterRect.Height()/13*10);
	//StrokeLine(topPoint,bottomPoint);
	topPoint.Set(letterRect.Width()+letterRect.Width()/2,letterRect.Height()/13*11);
	
	partRect.Set(letterRect.left,letterRect.Height()/13*12,
				letterRect.left+2*width,letterRect.Height()/13*13);
	StrokeRect(partRect);
	bottomPoint.Set(letterRect.left+width,letterRect.Height()/13*12);
	//StrokeLine(topPoint,bottomPoint);
	
	//Draw the i
	letterRect = Bounds();
	letterRect.Set(letterRect.Width()/4*2,letterRect.top,letterRect.Width()/4*3,letterRect.Height());
	StrokeRect(letterRect);
	//letterRect.InsetBy(3.0,3.0);
	
	//Stroke each layer
	partRect.Set(letterRect.Width()*2+letterRect.Width()/2-width,letterRect.Height()/13*2,
				letterRect.Width()*2+letterRect.Width()/2+width,letterRect.Height()/13*3);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()*2+letterRect.Width()/2-width,letterRect.Height()/13*6,
				letterRect.Width()*2+letterRect.Width()/2+width,letterRect.Height()/13*7);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()*2+letterRect.Width()/2-width,letterRect.Height()/13*8,
				letterRect.Width()*2+letterRect.Width()/2+width,letterRect.Height()/13*9);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()*2+letterRect.Width()/2-width,letterRect.Height()/13*10,
				letterRect.Width()*2+letterRect.Width()/2+width,letterRect.Height()/13*11);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()*2+letterRect.Width()/2-width,letterRect.Height()/13*12,
				letterRect.Width()*2+letterRect.Width()/2+width,letterRect.Height()/13*13);
	StrokeRect(partRect);
		
	//Draw the m
	letterRect = Bounds();
	letterRect.Set(letterRect.Width()/4*3,letterRect.top,letterRect.Width(),letterRect.Height());
	StrokeRect(letterRect);
	//letterRect.InsetBy(3.0,3.0);
	
	//Stroke each layer
	partRect.Set(letterRect.Width()*3,letterRect.Height()/13*6,
				letterRect.Width()*3+2*width,letterRect.Height()/13*7);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()*3,letterRect.Height()/13*8,
				letterRect.Width()*3+2*width,letterRect.Height()/13*9);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()*3,letterRect.Height()/13*10,
				letterRect.Width()*3+2*width,letterRect.Height()/13*11);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()*3,letterRect.Height()/13*12,
				letterRect.Width()*3+2*width,letterRect.Height()/13*13);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()*3+letterRect.Width()/6*2-width,letterRect.Height()/13*6,
				letterRect.Width()*3+letterRect.Width()/6*2+width,letterRect.Height()/13*7);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()*3+letterRect.Width()/2-width,letterRect.Height()/13*8,
				letterRect.Width()*3+letterRect.Width()/2+width,letterRect.Height()/13*9);
	StrokeRect(partRect);
		
	partRect.Set(letterRect.Width()*3+letterRect.Width()/6*4-width,letterRect.Height()/13*6,
				letterRect.Width()*3+letterRect.Width()/6*4+width,letterRect.Height()/13*7);
	StrokeRect(partRect);
		
	partRect.Set(letterRect.Width()*4-2*width,letterRect.Height()/13*6,
				letterRect.Width()*4,letterRect.Height()/13*7);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()*4-2*width,letterRect.Height()/13*8,
				letterRect.Width()*4,letterRect.Height()/13*9);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()*4-2*width,letterRect.Height()/13*10,
				letterRect.Width()*4,letterRect.Height()/13*11);
	StrokeRect(partRect);
	
	partRect.Set(letterRect.Width()*4-2*width,letterRect.Height()/13*12,
				letterRect.Width()*4,letterRect.Height()/13*13);
	StrokeRect(partRect); 
}
/*
void LogoView::WindowActivated(bool active) {
	
	int8 red,green,blue;
	
	if (active) {
		BRect letterRect;
		BRect partRect;
		BPoint topPoint, bottomPoint;
		//width of each square
		float width = (Bounds()).Width()/4*0.08;
	
		BMessage *msgLine = new BMessage(DRAW_LOGO_LINE);
		BMessage *msgRect = new BMessage(DRAW_LOGO_RECT);
		//Draw the O
		letterRect = Bounds();
		letterRect.Set(letterRect.left,letterRect.top,letterRect.Width()/4,letterRect.Height());
		
		//Set the Color for the letter "O"
		red = 24;
		green = 250;
		blue = 23;
	
		msgRect->AddInt8("red",red);
		msgRect->AddInt8("green",green);
		msgRect->AddInt8("blue",blue);
		msgLine->AddInt8("red",red);
		msgLine->AddInt8("green",green);
		msgLine->AddInt8("blue",blue);
		
		
		//Stroke each layer at a time
		//Layer 1
		partRect.Set(letterRect.Width()/2-width,letterRect.top,
				 letterRect.Width()/2+width,letterRect.Height()/13*1);
		msgRect->AddRect("logoRect",partRect);
		Window()->PostMessage(msgRect,this);
		snooze(aTime);
		
		//Layer 2 Left
		topPoint.Set(letterRect.Width()/2,letterRect.Height()/13*1);
		bottomPoint.Set(letterRect.Width()/9*3,letterRect.Height()/13*2);
		msgLine->AddPoint("appPoint",topPoint);
		msgLine->AddPoint("libPoint",bottomPoint);
		Window()->PostMessage(msgLine,this);
		snooze(aTime);	
		
		//Layer 3 Left
		partRect.Set(letterRect.Width()/9*3-width,letterRect.Height()/13*2,
				letterRect.Width()/9*3+width,letterRect.Height()/13*3);
		msgRect->AddRect("logoRect",partRect);
		Window()->PostMessage(msgRect,this);
		snooze(aTime);
		
		//Layer 4 Left
		topPoint.Set(letterRect.Width()/9*3,letterRect.Height()/13*3);
		bottomPoint.Set(letterRect.Width()/10*2,letterRect.Height()/13*4);
		msgLine->AddPoint("appPoint",topPoint);
		msgLine->AddPoint("libPoint",bottomPoint);
		Window()->PostMessage(msgLine,this);
		snooze(aTime);	
		
		partRect.Set(letterRect.Width()/9*6-width,letterRect.Height()/13*2,
				letterRect.Width()/9*6+width,letterRect.Height()/13*3);
		//FillRect(partRect);
		bottomPoint.Set(letterRect.Width()/9*6,letterRect.Height()/13*2);
		//StrokeLine(topPoint,bottomPoint);
		
		partRect.Set(letterRect.Width()/10*2-width,letterRect.Height()/13*4,
				letterRect.Width()/10*2+width,letterRect.Height()/13*5);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()/10*8-width,letterRect.Height()/13*4,
				letterRect.Width()/10*8+width,letterRect.Height()/13*5);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.left,letterRect.Height()/13*6,
				letterRect.left+2*width,letterRect.Height()/13*7);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.right-2*width,letterRect.Height()/13*6,
				letterRect.right,letterRect.Height()/13*7);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()/10*2-width,letterRect.Height()/13*8,
				letterRect.Width()/10*2+width,letterRect.Height()/13*9);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()/10*8-width,letterRect.Height()/13*8,
				letterRect.Width()/10*8+width,letterRect.Height()/13*9);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()/9*3-width,letterRect.Height()/13*10,
				letterRect.Width()/9*3+width,letterRect.Height()/13*11);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()/9*6-width,letterRect.Height()/13*10,
				letterRect.Width()/9*6+width,letterRect.Height()/13*11);
		StrokeRect(partRect);
		
		partRect.Set(letterRect.Width()/2-width,letterRect.Height()/13*12,
					 letterRect.Width()/2+width,letterRect.Height()/13*13);
		StrokeRect(partRect);
	
	
		//Draw the S
		letterRect = Bounds();
		letterRect.Set(letterRect.Width()/4,letterRect.top,letterRect.Width()/4*2,letterRect.Height());
		StrokeRect(letterRect);
		//letterRect.InsetBy(3.0,3.0);
		//StrokeRect(letterRect);
		//Stroke each Layer
		partRect.Set(letterRect.right-2*width,letterRect.top,
				letterRect.right,letterRect.Height()/13*1);
		StrokeRect(partRect);
		topPoint.Set(letterRect.right-width,letterRect.Height()/13*1);
	
		partRect.Set(letterRect.Width()+letterRect.Width()/2-width,letterRect.top,
				letterRect.Width()+letterRect.Width()/2+width,letterRect.Height()/13*1);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.left,letterRect.Height()/13*2,
				letterRect.left+2*width,letterRect.Height()/13*3);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.left,letterRect.Height()/13*4,
				letterRect.left+2*width,letterRect.Height()/13*5);
		StrokeRect(partRect);
		bottomPoint.Set(letterRect.left+width,letterRect.Height()/13*4);
		StrokeLine(topPoint,bottomPoint);
		topPoint.Set(letterRect.left+width,letterRect.Height()/13*5);
	
		partRect.Set(letterRect.Width()+letterRect.Width()/2-width,letterRect.Height()/13*6,
				letterRect.Width()+letterRect.Width()/2+width,letterRect.Height()/13*7);
		StrokeRect(partRect);
		bottomPoint.Set(letterRect.Width()+letterRect.Width()/2,letterRect.Height()/13*6);
		StrokeLine(topPoint,bottomPoint);
		topPoint.Set(letterRect.Width()+letterRect.Width()/2,letterRect.Height()/13*7);
	
		partRect.Set(letterRect.right-2*width,letterRect.Height()/13*8,
				letterRect.right,letterRect.Height()/13*9);
		StrokeRect(partRect);
		bottomPoint.Set(letterRect.right-width,letterRect.Height()/13*8);
		StrokeLine(topPoint,bottomPoint);
		topPoint.Set(letterRect.right-width,letterRect.Height()/13*9);
	
		partRect.Set(letterRect.right-2*width,letterRect.Height()/13*10,
					letterRect.right,letterRect.Height()/13*11);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()+letterRect.Width()/2-width,letterRect.Height()/13*12,
				letterRect.Width()+letterRect.Width()/2+width,letterRect.Height()/13*13);
		StrokeRect(partRect);
		bottomPoint.Set(letterRect.Width()+letterRect.Width()/2,letterRect.Height()/13*10);
		StrokeLine(topPoint,bottomPoint);
		topPoint.Set(letterRect.Width()+letterRect.Width()/2,letterRect.Height()/13*11);
	
		partRect.Set(letterRect.left,letterRect.Height()/13*12,
				letterRect.left+2*width,letterRect.Height()/13*13);
		StrokeRect(partRect);
		bottomPoint.Set(letterRect.left+width,letterRect.Height()/13*12);
		StrokeLine(topPoint,bottomPoint);
	
		//Draw the i
		letterRect = Bounds();
		letterRect.Set(letterRect.Width()/4*2,letterRect.top,letterRect.Width()/4*3,letterRect.Height());
		StrokeRect(letterRect);
		//letterRect.InsetBy(3.0,3.0);
	
		//Stroke each layer
		partRect.Set(letterRect.Width()*2+letterRect.Width()/2-width,letterRect.Height()/13*2,
				letterRect.Width()*2+letterRect.Width()/2+width,letterRect.Height()/13*3);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()*2+letterRect.Width()/2-width,letterRect.Height()/13*6,
				letterRect.Width()*2+letterRect.Width()/2+width,letterRect.Height()/13*7);
		StrokeRect(partRect);
		
		partRect.Set(letterRect.Width()*2+letterRect.Width()/2-width,letterRect.Height()/13*8,
				letterRect.Width()*2+letterRect.Width()/2+width,letterRect.Height()/13*9);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()*2+letterRect.Width()/2-width,letterRect.Height()/13*10,
				letterRect.Width()*2+letterRect.Width()/2+width,letterRect.Height()/13*11);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()*2+letterRect.Width()/2-width,letterRect.Height()/13*12,
				letterRect.Width()*2+letterRect.Width()/2+width,letterRect.Height()/13*13);
		StrokeRect(partRect);
		
		//Draw the m
		letterRect = Bounds();
		letterRect.Set(letterRect.Width()/4*3,letterRect.top,letterRect.Width(),letterRect.Height());
		StrokeRect(letterRect);
		//letterRect.InsetBy(3.0,3.0);
	
		//Stroke each layer
		partRect.Set(letterRect.Width()*3,letterRect.Height()/13*6,
				letterRect.Width()*3+2*width,letterRect.Height()/13*7);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()*3,letterRect.Height()/13*8,
				letterRect.Width()*3+2*width,letterRect.Height()/13*9);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()*3,letterRect.Height()/13*10,
				letterRect.Width()*3+2*width,letterRect.Height()/13*11);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()*3,letterRect.Height()/13*12,
				letterRect.Width()*3+2*width,letterRect.Height()/13*13);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()*3+letterRect.Width()/6*2-width,letterRect.Height()/13*6,
				letterRect.Width()*3+letterRect.Width()/6*2+width,letterRect.Height()/13*7);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()*3+letterRect.Width()/2-width,letterRect.Height()/13*8,
				letterRect.Width()*3+letterRect.Width()/2+width,letterRect.Height()/13*9);
		StrokeRect(partRect);
		
		partRect.Set(letterRect.Width()*3+letterRect.Width()/6*4-width,letterRect.Height()/13*6,
				letterRect.Width()*3+letterRect.Width()/6*4+width,letterRect.Height()/13*7);
		StrokeRect(partRect);
		
		partRect.Set(letterRect.Width()*4-2*width,letterRect.Height()/13*6,
				letterRect.Width()*4,letterRect.Height()/13*7);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()*4-2*width,letterRect.Height()/13*8,
				letterRect.Width()*4,letterRect.Height()/13*9);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()*4-2*width,letterRect.Height()/13*10,
				letterRect.Width()*4,letterRect.Height()/13*11);
		StrokeRect(partRect);
	
		partRect.Set(letterRect.Width()*4-2*width,letterRect.Height()/13*12,
				letterRect.Width()*4,letterRect.Height()/13*13);
		StrokeRect(partRect); 
		
		//Window()->DisableUpdates();
	}
}	

void LogoView::MessageReceived(BMessage *message)
{
	status_t result;
	status_t error;
	//printf("OSimWindow Message Received\n");
	BPoint appPoint;
	BPoint libPoint;
	BRect logoRect;
	int8 red, green, blue;
	switch (message->what) {
		case DRAW_LOGO_RECT:
			if (showAnimation) {
				error = message->FindRect("logoRect",&logoRect);
				//error = message->FindPoint("libPoint",&libPoint);
				error = message->FindInt8("red",&red);
				error = message->FindInt8("green",&green);
				error = message->FindInt8("blue",&blue);
				SetHighColor((uint8)red,(uint8)green,(uint8)blue);
				logoRect.InsetBy(1.0,1.0);
				FillRect(logoRect);
				SetHighColor(0,0,0);
				Invalidate();
			}
			
			break;
			
		case DRAW_LOGO_LINE:
			if (showAnimation) {
				
				error = message->FindPoint("appPoint",&appPoint);
				error = message->FindPoint("libPoint",&libPoint);
				error = message->FindInt8("red",&red);
				error = message->FindInt8("green",&green);
				error = message->FindInt8("blue",&blue);
				SetHighColor((uint8)red,(uint8)green,(uint8)blue);
				StrokeLine(appPoint, libPoint);
				SetHighColor(0,0,0);
				Invalidate();
			}
			
			break;
		default: 
			BView::MessageReceived(message);
			break;
	}	
}*/