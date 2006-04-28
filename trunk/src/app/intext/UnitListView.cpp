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
#include <ListView.h>
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
#include <Entry.h>

#include "Messages.h"
#include "UnitListView.h"
#include "XMLDocument.h"

UnitListView::UnitListView(BRect rect, char *name) 
		: BListView(rect, name, B_SINGLE_SELECTION_LIST, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS)
{
	entryList = new BList();
	
	//need to look through the unit directory for files
	status_t 	err = B_NO_ERROR; 
   	app_info info; 
    BPath path; 
	be_app->GetAppInfo(&info); 
    BEntry entry(&info.ref); 
    entry.GetPath(&path); 
    path.GetParent(&path);
	path.Append("unit");

	BDirectory dir( path.Path() );

	while( err != B_ENTRY_NOT_FOUND ){
		err = dir.GetNextEntry(&entry);
		if( err != B_ENTRY_NOT_FOUND ){
			char name[B_FILE_NAME_LENGTH];
			entry.GetName(name);
			BString tname;
			XMLDocument test(&entry);
			test.GetAttributeData("sect","id",&tname);
			//I assume the lists will stay synced because
			//I am not sorrting them at any time
			AddItem(new BStringItem(tname.String()));
			entryList->AddItem(new BEntry(entry));
		}
		
	}
}

void UnitListView::SelectionChanged(void) {
	int32 currentListIndex;
	entry_ref currentEntryRef;
	//BEntry currentEntry;
	currentListIndex = CurrentSelection();
	if (currentListIndex >= 0) {
		((BEntry *)entryList->ItemAt(currentListIndex))->GetRef(&currentEntryRef);
		BMessage *selectionMsg;	
		selectionMsg = new BMessage(UNIT_CHANGED);
		selectionMsg->AddRef("entry", &currentEntryRef);
		Window()->PostMessage(selectionMsg);
	}
}

