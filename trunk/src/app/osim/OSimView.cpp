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

#include "OSimView.h"
#include "OSImage.h"
#include "kinfo_wrapper.h"
#include "OSRelationship.h"


OSimView::OSimView(BRect rect, char *name) 
		: BView(rect, name, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE | B_FRAME_EVENTS |B_SUBPIXEL_PRECISE)
{
	//Initialize Private Variables
	ApplicationDrawList = new BList();
	AppLibDrawList = new BList();		//Relationships
	LibraryDrawList = new BList();	
	LibServDrawList = new BList();		//Relationships
	ServerDrawList = new BList();	
	ServSysDrawList = new BList();		//Relationships	
	SystemLibDrawList = new BList();	
	SysKernDrawList = new BList();		//Relationships
	KernelDrawList = new BList();
	KernBusDrawList = new BList();		//Relationships
	BusDrawList = new BList();
	BusIOSDrawList = new BList();		//Relationships
	IOSDrawList = new BList();
	// Rather the list representes the whole or partial
	ApplicationFilter = false;
	AppLibFilter = false;
	LibraryFilter = false;
	LibServFilter = false;
	ServerFilter = false;
	ServSysFilter = false;
	SystemLibFilter = false;
	SysKernFilter = false;
	KernelFilter = false;
	KernBusFilter = false;
	BusFilter = false;
	BusIOSFilter = false;
	IOSFilter = false;	
	
	statusWindow = NULL;	
	currentAppImage = NULL;
	currentLibImage = NULL;
	currentRelationship = NULL;
	
	
}

void OSimView::Draw(BRect)
{
	//This is just a top view I may need to delete this and choose for this view not to draw :)
	
} 


//void OSimView::MessageReceived(BMessage *message)
//{
//	
//
//	switch (message->what) {
//		default: 
//			BView::MessageReceived(message);
//			break;
//	}
//}

void OSimView::Pulse()
{
	UpdateApplicationDrawList(UPDATE_APP_DRAW);
}

void OSimView::AttachedToWindow()
{
	Window()->SetPulseRate(3000000); //Set the Pulse rate in microseconds of the Window
	SetFlags(Flags() | B_PULSE_NEEDED); //Activate the Pulse function
	
	//BAlert *alert;
	//status_t result;
	
	//be_app->PostMessage(B_QUIT_REQUESTED);
	//alert = new BAlert("Notice","Please be patient as device information is collected","OK");	
	//result = alert->Go();
	
	//Display the status window in the middle of the screen
	BScreen osimScreen;
	BRect sRect(osimScreen.Frame());
	sRect.Set(sRect.Width()/2-100,sRect.Height()/2-25,sRect.Width()/2+100,sRect.Height()/2+25);
	statusWindow = new StatusWindow(sRect);
	
	//Go ahead and manually add the kernel
	BString *strImageName = new BString("KERNEL");
	UpdateList(KernelDrawList, 9, strImageName, IMAGE_KERNEL);
	UpdateAllLists();
	delete strImageName;
}

void OSimView::FrameResized(float new_width, float new_height)
{
	UpdateSizeOnAllLists();
}

void OSimView::UpdateAllLists()
{
	//Create image objects or resize if needed
	UpdateApplicationDrawList(UPDATE_APP_DRAW);
	UpdateKernelDrawList();
}

void OSimView::UpdateKernelDrawList() {
	//Kernel Module Information: KernelDrawList, BusDrawList, and IOS draw list
	uint32 mcookie = 0;
	char modName[B_OS_NAME_LENGTH];
	BString strImageName;
	 
	init_kinfo_wrapper();
	// Build the kernel list and module list with kernel module kinfo	
	while (get_next_module_name(&mcookie, modName, sizeof(modName)) == B_NO_ERROR)
	{
		strImageName.SetTo(modName);
		if (strImageName.IFindFirst("bus_managers") == B_ERROR) {
			UpdateList(KernelDrawList, 9, &strImageName, IMAGE_MODULE);
		} else { 
			UpdateList(BusDrawList, 11, &strImageName, IMAGE_BUS);	
		}	
	}
	uninit_kinfo_wrapper();
	
	// Available File Systems
	
	
	//Available Drivers
	BDirectory devDir("/dev");
	BMessage *msg = new BMessage(STATUS_MAX);
	int32 numOfEntries = 0;
	CountEntries(devDir,&numOfEntries);
	msg->AddFloat("max",(float)numOfEntries);
	statusWindow->PostMessage(msg,statusWindow);
	delete msg;
	//BInputDevice::Stop(B_POINTING_DEVICE);
	//BInputDevice::Stop(B_KEYBOARD_DEVICE);
	//BInputDevice::Stop(B_UNDEFINED_DEVICE);
	BuildDevList(devDir);
	//Restarting the whole input server fixes the lockup of accessing input devices
	//BInputDevice::Start(B_POINTING_DEVICE);
	//BInputDevice::Start(B_KEYBOARD_DEVICE);
	//BInputDevice::Start(B_UNDEFINED_DEVICE);
	system("/system/servers/input_server -q");	
	statusWindow->PostMessage(B_QUIT_REQUESTED);
	statusWindow->Lock();
	statusWindow->Quit();
	//Do no worry about deletes yet
}

void OSimView::CountEntries(BDirectory dir, int32 *num) {
	BDirectory devDir;
	BEntry devEntry;
		
	dir.Rewind();
	while (dir.GetNextEntry(&devEntry,false) == B_NO_ERROR) {
		BString strImageName;
		if (devEntry.IsDirectory()) {
			devDir.SetTo(&devEntry);
			*num += 1;
			CountEntries(devDir,num);
		} else if (!(devEntry.IsSymLink())) {
			*num += 1;
			
		}	
	}

}
//Use recursive function to walk through file structure
void OSimView::BuildDevList(BDirectory dir) {
	
	BDirectory devDir;
	BEntry devEntry;
	BPath devicePath;
		
	dir.Rewind();
	while (dir.GetNextEntry(&devEntry,false) == B_NO_ERROR) {
		BString strImageName;
		if (devEntry.IsDirectory()) {
			devDir.SetTo(&devEntry);
			BMessage *msg = new BMessage(STATUS_UPDATE);
			msg->AddFloat("delta",1.0);
			statusWindow->PostMessage(msg,statusWindow);
			delete msg;
			BuildDevList(devDir);
		} else if (!(devEntry.IsSymLink())) {
			devEntry.GetPath(&devicePath);
			//*outputBuff << devicePath.Path() << "\n";
			BMessage *msg = new BMessage(STATUS_UPDATE);
			msg->AddFloat("delta",1.0);
			statusWindow->PostMessage(msg,statusWindow);
			delete msg;
			int fd;
			BString bDevice;
			bDevice = devicePath.Path();
			printf("device: %s \n",bDevice.String());		
			//accessing input devices lock up the computer
			//Maybe I should restart the input server?
			//if (bDevice.IFindFirst("input") == B_ERROR) {
			//if the dev is not the first tt or pt we do not want to check
			//This saves some time on startup
			if  ((bDevice.IFindFirst("/dev/tt") != B_ERROR) && (devicePath != "/dev/tt/p0")) {
				//do nothing 
			} else if ((bDevice.IFindFirst("/dev/pt") != B_ERROR) && (devicePath != "/dev/pt/p0")) { 
				//do nothing
			} else if (bDevice.IFindFirst("/dev/input/mouse/serial") != B_ERROR) { 
				//do nothing
			} else if (bDevice.IFindFirst("/dev/input/mouse/usb") != B_ERROR) { 
				//do nothing
			} else if (bDevice.IFindFirst("usb") != B_ERROR) { 
				//do nothing
			} else if (bDevice.IFindFirst("serial") != B_ERROR) { 
				//do nothing
			} else {			
				fd = open(bDevice.String(), 0);
				if (fd > 0) {
					status_t result;
					driver_path dPath;
					int size;
					printf("Opened Device\n");
					result = ioctl(fd,B_GET_DRIVER_FOR_DEVICE, (void *)dPath, size);
					if (result != B_ERROR) {
						//add to IOSDraw List if it doesn't already exist
						printf("ioctrl successful: %s \n", &dPath);
						strImageName << *((driver_path *)dPath);
						UpdateList(IOSDrawList,13,&strImageName, IMAGE_DEVICE);
					} else {
						printf("ioctrl failed\n");	
					}
				close(fd);
				} else { 
					printf("Could not open Device\n");	
				}
			}	
		} //close file type check if		
	} //close while loop	
}

void OSimView::UpdateApplicationDrawList(uint32 flags)
{
	//Compare items with existing list
	//Add to the list if it did not preexist
	//Delete from view and list if object is no longer opened
	team_info teamInfo;
	image_info imageInfo;
	int32 cookie = 0;
	int32 icookie;
	BString strImageName;
	BFile	imageFile;
	BAppFileInfo	appImageInfo;
	app_info	appInfo;
	uint32	appFlags;	
	
	//Cycle through open programs to add to list
	while (get_next_team_info(&cookie, &teamInfo) == B_NO_ERROR)
	{
		icookie = 0;
		//Cycle through processes
		while (get_next_image_info(teamInfo.team, &icookie, &imageInfo) == B_NO_ERROR)
		{
			strImageName.SetTo(imageInfo.name);
			if (imageInfo.type == B_APP_IMAGE) {
				imageFile.SetTo(imageInfo.name, B_READ_WRITE);
				appImageInfo.SetTo(&imageFile);
				appImageInfo.GetAppFlags(&appFlags);
			
				if ((appFlags & B_BACKGROUND_APP) == B_BACKGROUND_APP) {
					UpdateList(ServerDrawList, 5, &strImageName, IMAGE_SERVER);
				} else { 
					UpdateList(ApplicationDrawList, 1, &strImageName);
				}	
			} else if (imageInfo.type == B_LIBRARY_IMAGE) {
				if ((strImageName.IFindFirst("libbe.so") != B_ERROR) || (strImageName.IFindFirst("libroot.so") != B_ERROR)){ 
					UpdateList(SystemLibDrawList, 7, &strImageName, IMAGE_SYSLIB);
				} else {
					UpdateList(LibraryDrawList, 3, &strImageName, IMAGE_LIB);
				}
			} // End image check	
		} //End of get_next_image_info
		
	}//End of get_next_team_info
	
	//The relationships will be deleted by the deletion of OSImage
	//Cycle through shown images to check if deletions are required
	for (int32 i = ApplicationDrawList->CountItems(); i > 0; i--) {
		if(!(((OSImage *)ApplicationDrawList->ItemAt(i-1))->GetMatch())) {
			//delete object and remove from lists
			RemoveChild((OSImage *)ApplicationDrawList->ItemAt(i-1));
			delete((OSImage *)ApplicationDrawList->ItemAt(i-1));
			ApplicationDrawList->RemoveItem(i-1);	
			UpdateSizeOnAllLists();				
		} else {	
			((OSImage *)ApplicationDrawList->ItemAt(i-1))->SetMatch(false);
		}
	}
	
	//Cycle through shown images to check if deletions are required
	for (int32 i = LibraryDrawList->CountItems(); i > 0; i--) {
		if(!(((OSImage *)LibraryDrawList->ItemAt(i-1))->GetMatch())) {
			//delete object and remove from lists
			RemoveChild((OSImage *)LibraryDrawList->ItemAt(i-1));
			delete((OSImage *)LibraryDrawList->ItemAt(i-1));
			LibraryDrawList->RemoveItem(i-1);	
			UpdateSizeOnAllLists();				
		} else {	
			((OSImage *)LibraryDrawList->ItemAt(i-1))->SetMatch(false);
		}
	}
	
	//Cycle through shown images to check if deletions are required
	for (int32 i = ServerDrawList->CountItems(); i > 0; i--) {
		if(!(((OSImage *)ServerDrawList->ItemAt(i-1))->GetMatch())) {
			//delete object and remove from lists
			RemoveChild((OSImage *)ServerDrawList->ItemAt(i-1));
			delete((OSImage *)ServerDrawList->ItemAt(i-1));
			ServerDrawList->RemoveItem(i-1);	
			UpdateSizeOnAllLists();				
		} else {	
			((OSImage *)ServerDrawList->ItemAt(i-1))->SetMatch(false);
		}
	}
	
	//Cycle through shown images to check if deletions are required
	for (int32 i = SystemLibDrawList->CountItems(); i > 0; i--) {
		if(!(((OSImage *)SystemLibDrawList->ItemAt(i-1))->GetMatch())) {
			//delete object and remove from lists
			RemoveChild((OSImage *)SystemLibDrawList->ItemAt(i-1));
			OSImage *delImage = (OSImage *)SystemLibDrawList->ItemAt(i-1);
			SystemLibDrawList->RemoveItem(i-1);	
			delete(delImage);
			UpdateSizeOnAllLists();				
		} else {	
			((OSImage *)SystemLibDrawList->ItemAt(i-1))->SetMatch(false);
		}
	}
}

//This function resizes all Operating System objects on their respective rolls
void OSimView::UpdateSizeOnAllLists() 
{
	BRect rect;
	int32 i,j;
	//I could do this a better way, but I would get confused if I look at this later
	for (i = ApplicationDrawList->CountItems(), j=1; i > 0; i--, j++) {
		rect = GetImageSize(1,ApplicationDrawList->CountItems(),j);
		((OSImage *)ApplicationDrawList->ItemAt(i-1))->MoveTo(rect.LeftTop());
		((OSImage *)ApplicationDrawList->ItemAt(i-1))->ResizeTo(rect.Width(),rect.Height());				
	}	
	
	for (i = LibraryDrawList->CountItems(), j=1; i > 0; i--, j++) {
		rect = GetImageSize(3,LibraryDrawList->CountItems(),j);
		((OSImage *)LibraryDrawList->ItemAt(i-1))->MoveTo(rect.LeftTop());
		((OSImage *)LibraryDrawList->ItemAt(i-1))->ResizeTo(rect.Width(),rect.Height());				
	}
		
	for (i = ServerDrawList->CountItems(), j=1; i > 0; i--, j++) {
		rect = GetImageSize(5,ServerDrawList->CountItems(),j);
		((OSImage *)ServerDrawList->ItemAt(i-1))->MoveTo(rect.LeftTop());
		((OSImage *)ServerDrawList->ItemAt(i-1))->ResizeTo(rect.Width(),rect.Height());				
	}		
	
	for (i = SystemLibDrawList->CountItems(), j=1; i > 0; i--, j++) {
		rect = GetImageSize(7,SystemLibDrawList->CountItems(),j);
		((OSImage *)SystemLibDrawList->ItemAt(i-1))->MoveTo(rect.LeftTop());
		((OSImage *)SystemLibDrawList->ItemAt(i-1))->ResizeTo(rect.Width(),rect.Height());				
	}
	
	for (i = KernelDrawList->CountItems(), j=1; i > 0; i--, j++) {
		rect = GetImageSize(9,KernelDrawList->CountItems(),j);
		((OSImage *)KernelDrawList->ItemAt(i-1))->MoveTo(rect.LeftTop());
		((OSImage *)KernelDrawList->ItemAt(i-1))->ResizeTo(rect.Width(),rect.Height());				
	}	
	
	for (i = BusDrawList->CountItems(), j=1; i > 0; i--, j++) {
		rect = GetImageSize(11,BusDrawList->CountItems(),j);
		((OSImage *)BusDrawList->ItemAt(i-1))->MoveTo(rect.LeftTop());
		((OSImage *)BusDrawList->ItemAt(i-1))->ResizeTo(rect.Width(),rect.Height());				
	}	
	
	for (i = IOSDrawList->CountItems(), j=1; i > 0; i--, j++) {
		rect = GetImageSize(13,IOSDrawList->CountItems(),j);
		((OSImage *)IOSDrawList->ItemAt(i-1))->MoveTo(rect.LeftTop());
		((OSImage *)IOSDrawList->ItemAt(i-1))->ResizeTo(rect.Width(),rect.Height());				
	}		
	
}

//Update List if needed
void OSimView::UpdateList(BList *list, int32 columnNumber, BString *imageName, osimage_type type = IMAGE_APP) 
{
	bool listMatch = false;
	BString strAppListName;
	BRect rect;
	//Cycle through the Application BList to check if the application image is already displayed
	for (int32 i = list->CountItems(); (i > 0) && (!(listMatch)); i--) {
		strAppListName.SetTo(((OSImage *)list->ItemAt(i-1))->GetName());
		//Check to make sure it is not a match
		//I need to check if there is another way of determining servers Backgound APP possible
		if (strAppListName.IFindFirst(imageName->String()) != B_ERROR) {
			listMatch = true;
			((OSImage *)list->ItemAt(i-1))->SetMatch(true);
			//if there is a match we need to add it to the current app image
			if ((type == IMAGE_APP) || (type == IMAGE_SERVER)) {
				currentAppImage = (OSImage *)list->ItemAt(i-1);
			} else if ((type == IMAGE_SYSLIB) || (type == IMAGE_LIB)){
				currentLibImage = (OSImage *)list->ItemAt(i-1);
				//Build Relationship
				currentRelationship = new OSRelationship(currentAppImage,currentLibImage, Window());
				currentAppImage->AddRelationship((void *)currentRelationship);
				currentLibImage->AddRelationship((void *)currentRelationship);
			} 
		} 
	}
	//If there is not a match then add image to BList
	if (!(listMatch)) {
		//resize other Boxes to make room for the new one
		int32 i,j;
		for (i = list->CountItems(), j=1; i >= 0; i--, j++) {
			rect = GetImageSize(columnNumber,list->CountItems() + 1,j);
			if (i >= 1) {
				((OSImage *)list->ItemAt(i-1))->MoveTo(rect.LeftTop());
				((OSImage *)list->ItemAt(i-1))->ResizeTo(rect.Width(),rect.Height());
			}				
		}
		//Add box at the end
		//If it is an image set to current OSImage so we can create relationships
		//If it is a library we can build a relationship with the current app image
		if ((type == IMAGE_APP) || (type == IMAGE_SERVER)) {
			currentAppImage = new OSImage(rect, imageName->String(), type);
			list->AddItem((void *)currentAppImage);
		} else if ((type == IMAGE_SYSLIB) || (type == IMAGE_LIB)){
			currentLibImage = new OSImage(rect, imageName->String(), type);
			list->AddItem((void *)currentLibImage);
			//Build Relationship
			currentRelationship = new OSRelationship(currentAppImage,currentLibImage, Window());
			currentAppImage->AddRelationship((void *)currentRelationship);
			currentLibImage->AddRelationship((void *)currentRelationship);
		} else if ((type == IMAGE_MODULE) || (type == IMAGE_BUS) || (type == IMAGE_DEVICE)) { 
			currentLibImage = new OSImage(rect, imageName->String(), type);
			list->AddItem((void *)currentLibImage);
			currentAppImage = kernelAppImage;
			//Build Relationship They all connect to the kernel
			currentRelationship = new OSRelationship(currentAppImage,currentLibImage, Window());
			currentAppImage->AddRelationship((void *)currentRelationship);
			currentLibImage->AddRelationship((void *)currentRelationship);
		} else if (type == IMAGE_KERNEL) { 
			kernelAppImage = new OSImage(rect, imageName->String(), type);
			list->AddItem((void *)kernelAppImage);
		} else {
			list->AddItem(new OSImage(rect, imageName->String(), type));
		}
		AddChild((OSImage *)list->LastItem());  //Make it visible
		((OSImage *)list->LastItem())->SetMatch(true);
	}		
}

BRect OSimView::GetImageSize(int32 columnNumber, int32 totalImages, int32 currentImage)
{
	BRect imageSize;
	BRect viewFrame = Bounds();
	int32 spacing = 10;
	float width;
	
	width=(viewFrame.Width()-(totalImages-1)*spacing)/totalImages;
	imageSize.left = (currentImage-1)*spacing + (currentImage-1)*width;
	imageSize.top = (columnNumber-1) * viewFrame.Height() / 13;
	imageSize.right = imageSize.left + width;
	imageSize.bottom = (columnNumber) * viewFrame.Height() / 13;
	return imageSize;
}