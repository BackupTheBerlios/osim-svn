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
#include <Control.h>
#include <Path.h>
#include <Rect.h>
#include <String.h>
#include <View.h>

#include <stdio.h>

#include "Messages.h"
#include "OSImage.h"
#include "OSRelationship.h"

OSImage::OSImage(BRect rect, const char *name, osimage_type type = IMAGE_APP)
		: BControl(rect, name, NULL, NULL, B_FOLLOW_NONE, B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE | B_NAVIGABLE |B_FRAME_EVENTS)
{
	frelationshipList = NULL;
	fimagePath = new BPath(name);
	fOSImageName = new BString(name);
	flistMatch = false;
	fimageType = type;
	BString leafName; 
	int32 firstOffSet, lastOffSet;
	//Check to see if it is a Kernel Module
	if (fimageType == IMAGE_DEVICE) {
		leafName << fimagePath->Leaf();
		leafName.Capitalize();
		SetLabel(leafName.String());
	//Check to see if it is a device
	} else if ((fimageType == IMAGE_MODULE) || (fimageType == IMAGE_BUS)) {
		leafName << name;
		firstOffSet = leafName.FindFirst("/");
		lastOffSet = leafName.FindLast("/");
		BString destination;
		leafName.CopyInto(destination,firstOffSet + 1,lastOffSet - firstOffSet - 1);
		destination.Capitalize();
		SetLabel(destination.String());
	} else {
		leafName << fimagePath->Leaf();
		leafName.Capitalize();
		SetLabel(leafName.String());
	}
	
	//Set the Message
	fmsg = new BMessage(OSIMAGE_SELECTED);
	fmsg->AddInt32("type",(uint32)fimageType);
	fmsg->AddString("name",*fOSImageName);
	SetMessage(fmsg);
	printf("OSImage Created\n");	

}

OSImage::~OSImage() {
	if ((fimageType == IMAGE_SERVER) || (fimageType == IMAGE_APP) || (fimageType == IMAGE_KERNEL)) {
		for ( int32 i = frelationshipList->CountItems(); i > 0; i--) {
			((OSRelationship *)frelationshipList->ItemAt(i-1))->RemoveLibRelationship((void *)frelationshipList->ItemAt(i-1));
		}
	} else {
		for ( int32 i = frelationshipList->CountItems(); i > 0; i--) {
			((OSRelationship *)frelationshipList->ItemAt(i-1))->RemoveAppRelationship((void *)frelationshipList->ItemAt(i-1));
		}
	}
	for ( int32 i = frelationshipList->CountItems(); i > 0; i--) {
		delete ((OSRelationship *)frelationshipList->ItemAt(i-1));
	}
		
	delete fimagePath;
	delete fOSImageName;
	//delete fmsg;
	delete frelationshipList;
	
	printf("OSImage Destroyed\n");	
}

void OSImage::Draw(BRect)
{
	BRect frame = Bounds();
	StrokeRoundRect(frame,5.0,5.0);
	if (IsFocus()) {
		//Draw blue square outline
		SetHighColor(210,219,255);
		frame.InsetBy(2.0,2.0);
		FillRoundRect(frame,5.0,5.0);
		frame.InsetBy(7.0,7.0);
		SetHighColor(255,255,255);
		FillRoundRect(frame,5.0,5.0);
		SetHighColor(0.0,0.0,0.0);
			
		//if (frelationshipList != NULL){
		//	for ( int32 i = frelationshipList->CountItems(); i > 0; i--) {
		//		//((OSRelationship *)frelationshipList->ItemAt(i-1))->Animate();
		//	}
		//}
		
	} else {
		//Erase blue outline 
		SetHighColor(255,255,255);
		frame.InsetBy(2.0,2.0);
		FillRoundRect(frame,5.0,5.0);
		SetHighColor(0.0,0.0,0.0);
		
		//if (frelationshipList != NULL){
		//	for ( int32 i = frelationshipList->CountItems(); i > 0; i--) {
		//		//((OSRelationship *)frelationshipList->ItemAt(i-1))->Move();
		//	}
		//}
	}
	
	//if (frelationshipList != NULL){
	//		for ( int32 i = frelationshipList->CountItems(); i > 0; i--) {
	//			((OSRelationship *)frelationshipList->ItemAt(i-1))->Move();
	//		}
	//	}
	//SetHighColor(0.0,0.0,0.0);
	SetLowColor(255.0,255.0,255.0);
	frame = Bounds();
	float fSize=12.0;
	SetFontSize(fSize);
	while (((StringWidth(Label())+2.0) > frame.Width()) && (fSize > 8.0)) {
		fSize-=1.0;
		SetFontSize(fSize);
	}	
	MovePenTo(BPoint(frame.Width()/2-(StringWidth(Label())/2),frame.Height()/2));
	DrawString(Label());	
}

void OSImage::MouseDown(BPoint where) {
	MakeFocus();
	BControl::Invoke(Message());
	printf("Message Sent\n");
}

void OSImage::FrameMoved(BPoint origin) {
	if (frelationshipList != NULL){
		for ( int32 i = frelationshipList->CountItems(); i > 0; i--) {
			((OSRelationship *)frelationshipList->ItemAt(i-1))->Move();
		}
	}
}

void OSImage::FrameResized(float width, float height) {
	if (frelationshipList != NULL){
		for ( int32 i = frelationshipList->CountItems(); i > 0; i--) {
			((OSRelationship *)frelationshipList->ItemAt(i-1))->Move();
		}
	}
}
// && ((fimageType == IMAGE_SERVER) || (fimageType == IMAGE_APP)))
//The match bit is used during checking rather an item drawn
//is still running in memory.  If the bit is still false after
//all running apps are scanned it the object will be deleted
bool OSImage::GetMatch() { return flistMatch; }
void OSImage::SetMatch(bool match) { flistMatch = match; } 

const char * OSImage::GetName()
{
	return fOSImageName->String();	
}

void OSImage::AddRelationship(void *relationship){
	if (frelationshipList == NULL) {
		frelationshipList = new BList();
	}	
	frelationshipList->AddItem(relationship);
}				

void OSImage::RemoveRelationship(void *relationship){
	frelationshipList->RemoveItem(relationship);
}	

void OSImage::GetType(osimage_type *type) {
	*type = fimageType;
}			

