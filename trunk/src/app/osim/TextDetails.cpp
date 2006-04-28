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
#include <File.h>
#include <Directory.h>
#include <FindDirectory.h>
#include <Path.h>
#include <Roster.h>
#include <String.h>
#include <image.h>
#include <Drivers.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <Input.h>

#include <OS.h>

#include "kinfo_wrapper.h"
#include "StatusWindow.h"

StatusWindow *statusWindow;

void printDevList(BString *outputBuff, BDirectory dir);

void CountEntries(BDirectory dir, int32 *num) {
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

status_t textDetails() {
	
	entry_ref	ref;
	const char	*name = "OSimDetails";
	const char *indent = "   ";
	const char *triIndent = "         ";
	BString buff;
	status_t	err;
	
		
	BPath *varPath = new BPath;
	
	//Get the VAR directory 	
	err = find_directory(B_COMMON_TEMP_DIRECTORY, varPath);
	
	BDirectory dir(varPath->Path());
	//BDirectory dir("/R5/home");
	
	BEntry *entry = new BEntry(&dir,name);
	//Create Temporary File that contains all the details
	BFile *file = new BFile(entry, B_READ_WRITE | B_CREATE_FILE |B_ERASE_FILE);
	if ((err = file->InitCheck()) != B_OK)
		return err;

	buff << name << "\n";
	
	file->Write(buff.String(),buff.Length());
	
	//Get Kernel Information
	system_info sysInfo;
	err = get_system_info(&sysInfo);
	
	buff = "\nKernel Details:\n";
	buff << indent << "Kernel Name: " << sysInfo.kernel_name << "\n";
	buff << indent << "Kernel Version: " << sysInfo.kernel_version << "\n"; 
	buff << indent << "Build Date: " << sysInfo.kernel_build_date << "\n";
	buff << indent << "Build Time: " << sysInfo.kernel_build_time << "\n";
	buff << indent << "Boot Time: " << sysInfo.boot_time << "\n";
	buff << indent << "Up Time: " << system_time() << "\n";
		
	file->Write(buff.String(),buff.Length());
	
	//Get CPU Information
	buff = "\nCPU Information:\n";
	buff << indent << "CPU Type: Intel\n";
	buff << indent << "CPU Speed: " << sysInfo.cpu_clock_speed/1000000 << " MHz\n";
	buff << indent << "Bus Speed: " << sysInfo.bus_clock_speed/1000000 << " MHz\n";
	buff << indent << "Number of CPUs: " << sysInfo.cpu_count << "\n";
		
	file->Write(buff.String(),buff.Length());
	
	//Get Resource Information
	buff = "\nResource Information:\n";
	buff << indent << "Max Pages: " << sysInfo.max_pages;
	buff << indent << "Used Pages: " << sysInfo.used_pages << "\n";
	buff << indent << "Page Faults: " << sysInfo.page_faults << "\n";
	buff << indent << "Max Semaphores: " << sysInfo.max_sems;
	buff << indent << "Used Semaphores: " << sysInfo.used_sems << "\n";
	buff << indent << "Max Ports: " << sysInfo.max_ports;
	buff << indent << "Used Ports: " << sysInfo.used_ports << "\n";
	buff << indent << "Max Threads: " << sysInfo.max_threads;
	buff << indent << "Used Threads: " << sysInfo.used_threads << "\n";
	buff << indent << "Max Teams: " << sysInfo.max_teams;
	buff << indent << "Used Teams: " << sysInfo.used_teams << "\n";
		
	file->Write(buff.String(),buff.Length());
	
	//Get Process Team Information and details
	buff = "\nProcess Team Informatioin\n";
	team_info teamInfo;
	//thread_info threadInfo;
	image_info imageInfo;
	//area_info areaInfo;
	//sem_info semInfo;
	//port_info portInfo;
		
	int32 cookie = 0;
	//int32 tcookie;
	int32 icookie;
	//int32 acookie;
	//int32 pcookie;
	//int32 scookie; 
	
	//this statement needs to be fixed in the BeBook
	while (get_next_team_info(&cookie, &teamInfo) == B_NO_ERROR)
	{
		buff << indent << "Team ID:" << teamInfo.team << "\n";
		buff << indent << indent << "Threads: " << teamInfo.thread_count << "\n";
		buff << indent << indent << "Images: " << teamInfo.image_count << "\n";
		buff << indent << indent << "Areas: " << teamInfo.area_count << "\n";
		buff << indent << indent << "Number of Command Line Arguments: " << teamInfo.argc << "\n";
		buff << indent << indent << "Arguments: " << teamInfo.args << "\n"; 
		buff << indent << indent << "User ID: " << teamInfo.uid;
		buff << indent << indent << "Group ID: " << teamInfo.gid << "\n";
		//Thread Details
		//tcookie = 0;
		//while (get_next_thread_info(teamInfo.team, &tcookie, &threadInfo) == B_NO_ERROR)
		//{
		//	buff << triIndent << "Thread ID:" << threadInfo.thread << "\n";
		//	buff << triIndent << indent << "Thread Name: " << threadInfo.name << "\n";
		//}
		//Image Details
		icookie = 0;
		while (get_next_image_info(teamInfo.team, &icookie, &imageInfo) == B_NO_ERROR)
		{
			buff << triIndent << "Image ID:" << imageInfo.id << "\n";
			buff << triIndent << indent << "Image Name: " << imageInfo.name << "\n";
			buff << triIndent << indent << "Image Type: ";
			switch(imageInfo.type) {
				case B_APP_IMAGE:
					buff << "Application\n";
					break;
				case B_LIBRARY_IMAGE:
					buff << "Library\n";
					break;
				case B_ADD_ON_IMAGE:
					buff << "AddOn\n";
					break;
				case B_SYSTEM_IMAGE:
					buff << "System Image\n";
					break;
			} //End of Switch
		}
		
		//Area Details
		//acookie = 0;
		//while (get_next_area_info(teamInfo.team, &acookie, &areaInfo) == B_NO_ERROR)
		//{
		//	buff << triIndent << "Area ID:" << areaInfo.area << "\n";
		//	buff << triIndent << indent << "Area Name: " << areaInfo.name << "\n";
		//}
		//Semaphore Details
		//scookie = 0;
		//while (get_next_sem_info(teamInfo.team, &scookie, &semInfo) == B_NO_ERROR)
		//{
		//	buff << triIndent << "Semaphore ID:" << semInfo.sem << "\n";
		//	buff << triIndent << indent << "Semaphore Name: " << semInfo.name << "\n";
		//}
		//Port Details
		//pcookie = 0;
		//while (get_next_port_info(teamInfo.team, &pcookie, &portInfo) == B_NO_ERROR)
		//{
		//	buff << triIndent << "Port ID:" << portInfo.port << "\n";
		//	buff << triIndent << indent << "Port Name: " << portInfo.name << "\n";
		//}
		
		file->Write(buff.String(),buff.Length());
		buff = " ";
	} 
	
	//Device Info used a lot of code from Haiku's Device Preferences
	
	//Kernel Module Info
	/* I Assume this will not work since I can not link to the kernel ?
	module_info modInfo;
	uint32 mcookie = 0;
	char cBuff;
	size_t buffSize;
	
	buff << "\nKernel Module Information:\n";
	file->Write(buff.String(),buff.Length());
	
	while(get_next_loaded_module_name(&mcookie, &cBuff, &buffSize) == B_NO_ERROR)
	{
		file->Write(&cBuff,buffSize);	
	}
	*/
	BRect sRect(100,100,300,140);
	statusWindow = new StatusWindow(sRect);
	
	//Use custom kinfo module to acces a list of kernel modules
	uint32 mcookie = 0;
	char modName[B_OS_NAME_LENGTH];
	
	buff = "\nKernel Module Information:\n";
	init_kinfo_wrapper();
		
	while (get_next_module_name(&mcookie, modName, sizeof(modName)) == B_NO_ERROR)
	{
		buff << indent << modName << " " << mcookie << "\n";
		
	}
	uninit_kinfo_wrapper();
	file->Write(buff.String(),buff.Length());
	// Available File Systems
	buff = "\nFile System Information:\n";
	
	file->Write(buff.String(),buff.Length());
	//Available Drivers
	buff = "\nDevice Driver Information Information:\n";
	BDirectory devDir("/dev");
	BMessage *msg = new BMessage(STATUS_MAX);
	int32 numOfEntries = 0;
	CountEntries(devDir,&numOfEntries);
	msg->AddFloat("max",(float)numOfEntries);
	statusWindow->PostMessage(msg,statusWindow);
	BInputDevice::Stop(B_POINTING_DEVICE);
	BInputDevice::Stop(B_KEYBOARD_DEVICE);
	BInputDevice::Stop(B_UNDEFINED_DEVICE);
	printDevList(&buff,devDir);
	//BInputDevice::Start(B_POINTING_DEVICE);
	//BInputDevice::Start(B_KEYBOARD_DEVICE);
	//BInputDevice::Start(B_UNDEFINED_DEVICE);
	//Restarting the whole input server fixes the lockup of accessing input devices
	system("/system/servers/input_server -q");
	file->Write(buff.String(),buff.Length());
	//close file
	delete file;	
	statusWindow->Quit();
	//Open the Text file with the default Text Editor
	err = entry->GetRef(&ref);
	err = be_roster->Launch(&ref);
	return err;	
}
//Use recursive function to walk through file structure
void printDevList(BString *outputBuff, BDirectory dir) {
	
	BDirectory devDir;
	BEntry devEntry;
	BPath devicePath;
	
	dir.Rewind();
	while (dir.GetNextEntry(&devEntry,false) == B_NO_ERROR) {
		if (devEntry.IsDirectory()) {
			devDir.SetTo(&devEntry);
			BMessage *msg = new BMessage(STATUS_UPDATE);
			msg->AddFloat("delta",1.0);
			statusWindow->PostMessage(msg,statusWindow);
			delete msg;
			printDevList(outputBuff,devDir);
		} else if (!(devEntry.IsSymLink())) {
			devEntry.GetPath(&devicePath);
			*outputBuff << devicePath.Path() << "\n";
			BMessage *msg = new BMessage(STATUS_UPDATE);
			msg->AddFloat("delta",1.0);
			statusWindow->PostMessage(msg,statusWindow);
			delete msg;
			int fd;
			const char *device = devicePath.Path();
			printf("device: %s \n",device);		
			//BString bDevice(device);
			//accessing input devices lock up the computer
			//Maybe I should restart the input server?
			//if (bDevice.IFindFirst("input") == B_ERROR) {
				fd = open(device, O_RDONLY | O_NONBLOCK);
				if (fd > 0) {
					status_t result;
					driver_path dPath;
					int size;
					printf("Opened Device\n");
					result = ioctl(fd,B_GET_DRIVER_FOR_DEVICE, (void *)dPath, size);
					if (result != B_ERROR) {
						printf("ioctrl successful: %s \n", &dPath);
						*outputBuff << *((driver_path *)dPath) << "\n";
					} else {
						printf("ioctrl failed\n");
					}
				
				} else {
					printf("Could not open Device\n");
				}
				close(fd);	
			//}	
		}	
	}
}