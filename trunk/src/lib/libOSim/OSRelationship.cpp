/*
Copyright (c) 2006 Bart Upchurch

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
#include <Control.h>
#include <Messenger.h>
#include <Path.h>
#include <Rect.h>
#include <String.h>
#include <View.h>
#include <Window.h>

#include "Messages.h"
#include "OSImage.h"
#include "OSRelationship.h"

OSRelationship::OSRelationship(OSImage *appImage, OSImage *libImage, BWindow *window) {
	fOSRelationshipName << appImage->GetName() << ":" << libImage->GetName();
	
	appImage->GetType(&fappType);
	libImage->GetType(&flibType);
	
	fapp_image = appImage;
	flib_image = libImage;
	fcurrent_window = window;
	
	flibPoint.Set(0.0,0.0);
	fappPoint.Set(0.0,0.0);
	Move();
}

OSRelationship::~OSRelationship() {
	//If app is deleted the relationship needs to be removed from library list
	// and the lines need to be erased
	//flib_image->RemoveRelationship(
	//delete fmsg;
}

void OSRelationship::Move() {
	BRect rectApp, rectLib;
	uint8 red,
		   green,
		   blue;
	//erase the previous line
	if (fappPoint != B_ORIGIN) {
		red = 0;
		blue = 0;
		green = 0;
		fmsg = new BMessage(DRAW_LINE);
		fmsg->AddPoint("fappPoint",fappPoint);
		fmsg->AddPoint("flibPoint",flibPoint);
		fmsg->AddInt8("red",red);
		fmsg->AddInt8("green",green);
		fmsg->AddInt8("blue",blue);
		fcurrent_window->PostMessage(fmsg);
		delete fmsg;
	}
	
	
	//Draw the new line
	rectApp = fapp_image->Frame();
	rectLib = flib_image->Frame();
	
	if ((flibType == IMAGE_LIB) && (fappType == IMAGE_APP)) {
		flibPoint.Set(rectLib.right - (rectLib.Width()/2),rectLib.top);
		fappPoint.Set(rectApp.right - (rectApp.Width()/2),rectApp.bottom);
		red = 0;
		blue = 0;
		green = 255;
	} else if ((flibType == IMAGE_LIB) && (fappType == IMAGE_SERVER)) {
		flibPoint.Set(rectLib.right - (rectLib.Width()/2),rectLib.bottom);
		fappPoint.Set(rectApp.right - (rectApp.Width()/2),rectApp.top);
		red = 0;
		blue = 255;
		green = 0;
	} else {  //should be connected to the bottom lins
		flibPoint.Set(rectLib.right - (rectLib.Width()/2),rectLib.top);
		fappPoint.Set(rectApp.right - (rectApp.Width()/2),rectApp.bottom);
		red = 255;
		blue = 0;
		green = 0;
	}
	
	fmsg = new BMessage(DRAW_LINE);
	fmsg->AddPoint("fappPoint",fappPoint);
	fmsg->AddPoint("flibPoint",flibPoint);
	fmsg->AddInt8("red",red);
	fmsg->AddInt8("green",green);
	fmsg->AddInt8("blue",blue);
	fcurrent_window->PostMessage(fmsg);
	delete fmsg;
}

void OSRelationship::Animate() {
	BRect rectApp, rectLib;
	uint8 red,
		   green,
		   blue;
	//erase the previous line
	if (fappPoint != B_ORIGIN) {
		red = 0;
		blue = 0;
		green = 0;
		fmsg = new BMessage(DRAW_LINE);
		fmsg->AddPoint("fappPoint",fappPoint);
		fmsg->AddPoint("flibPoint",flibPoint);
		fmsg->AddInt8("red",red);
		fmsg->AddInt8("green",green);
		fmsg->AddInt8("blue",blue);
		fcurrent_window->PostMessage(fmsg);
		delete fmsg;
	}
	
	
	//Draw the new line
	rectApp = fapp_image->Frame();
	rectLib = flib_image->Frame();
	
	if ((flibType == IMAGE_LIB) && (fappType == IMAGE_APP)) {
		flibPoint.Set(rectLib.right - (rectLib.Width()/2),rectLib.top);
		fappPoint.Set(rectApp.right - (rectApp.Width()/2),rectApp.bottom);
		red = 0;
		blue = 0;
		green = 0;
	} else if ((flibType == IMAGE_LIB) && (fappType == IMAGE_SERVER)) {
		flibPoint.Set(rectLib.right - (rectLib.Width()/2),rectLib.bottom);
		fappPoint.Set(rectApp.right - (rectApp.Width()/2),rectApp.top);
		red = 0;
		blue = 0;
		green = 0;
	} else {  //should be connected to the bottom lins
		flibPoint.Set(rectLib.right - (rectLib.Width()/2),rectLib.top);
		fappPoint.Set(rectApp.right - (rectApp.Width()/2),rectApp.bottom);
		red = 0;
		blue = 0;
		green = 0;
	}
	
	fmsg = new BMessage(DRAW_LINE);
	fmsg->AddPoint("fappPoint",fappPoint);
	fmsg->AddPoint("flibPoint",flibPoint);
	fmsg->AddInt8("red",red);
	fmsg->AddInt8("green",green);
	fmsg->AddInt8("blue",blue);
	fcurrent_window->PostMessage(fmsg);
	delete fmsg;
}

void OSRelationship::GetName(BString *name)
{
	name->SetTo(fOSRelationshipName.String());	
}

//OSImage destructor will call this class to remove the relationship from other 
//object in the relationship before deleting relationship memory
void OSRelationship::RemoveLibRelationship(void *relationship) {
	uint8 red,
		   green,
		   blue;
	//erase the previous line
	if (fappPoint != B_ORIGIN) {
		red = 0;
		blue = 0;
		green = 0;
		fmsg = new BMessage(DRAW_LINE);
		fmsg->AddPoint("fappPoint",fappPoint);
		fmsg->AddPoint("flibPoint",flibPoint);
		fmsg->AddInt8("red",red);
		fmsg->AddInt8("green",green);
		fmsg->AddInt8("blue",blue);
		fcurrent_window->PostMessage(fmsg);
		delete fmsg;
	}
	flib_image->RemoveRelationship(relationship);
}

void OSRelationship::RemoveAppRelationship(void *relationship) {
	uint8 red,
		   green,
		   blue;
	//erase the previous line
	if (fappPoint != B_ORIGIN) {
		red = 0;
		blue = 0;
		green = 0;
		fmsg = new BMessage(DRAW_LINE);
		fmsg->AddPoint("fappPoint",fappPoint);
		fmsg->AddPoint("flibPoint",flibPoint);
		fmsg->AddInt8("red",red);
		fmsg->AddInt8("green",green);
		fmsg->AddInt8("blue",blue);
		fcurrent_window->PostMessage(fmsg);
		delete fmsg;
	}
	fapp_image->RemoveRelationship(relationship);
}