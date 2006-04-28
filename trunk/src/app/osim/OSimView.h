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
#ifndef __OSIMVIEW_H__
#define __OSIMVIEW_H__

#include <View.h>
#include "OSImage.h"
#include "OSRelationship.h"
#include "StatusWindow.h"
#include "Constants.h"


class OSimView : public BView {
	public:
						OSimView(BRect frame, char *name);
		virtual void	Draw(BRect updateRect);	
		virtual void 	Pulse();
		virtual void	AttachedToWindow();
		virtual void    FrameResized(float new_width, float new_height);
		//virtual void	MessageReceived(BMessage *message);
				void  	UpdateSizeOnAllLists();
				void	UpdateAllLists();
				void 	UpdateList(BList *list, int32 columnNumber, BString *imageName, osimage_type type = IMAGE_APP);
				void    UpdateApplicationDrawList(uint32 flags);
				void 	UpdateKernelDrawList();
				void    BuildDevList(BDirectory dir);
				void	CountEntries(BDirectory dir,int32 *num);
				BRect 	GetImageSize(int32 columnNumber, int32 totalImages, int32 currentImage);
				
	private:
		BList	*ApplicationDrawList,
				*AppLibDrawList,		//Relationships
				*LibraryDrawList,	
				*LibServDrawList,		//Relationships
				*ServerDrawList,	
				*ServSysDrawList,		//Relationships	
				*SystemLibDrawList,	
				*SysKernDrawList,		//Relationships
				*KernelDrawList,
				*KernBusDrawList,		//Relationships
				*BusDrawList,
				*BusIOSDrawList,		//Relationships
				*IOSDrawList;
		// Rather the list representes the whole or partial
		bool	ApplicationFilter,
				AppLibFilter,
				LibraryFilter,
				LibServFilter,
				ServerFilter,
				ServSysFilter,
				SystemLibFilter,
				SysKernFilter,
				KernelFilter,
				KernBusFilter,
				BusFilter,
				BusIOSFilter,
				IOSFilter;	
		StatusWindow *statusWindow;
		//Used to create OS Relationships
		OSImage *currentAppImage, *currentLibImage, *kernelAppImage;
		OSRelationship *currentRelationship;
};

#endif