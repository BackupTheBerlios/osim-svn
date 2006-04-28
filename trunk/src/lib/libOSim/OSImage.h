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
#ifndef __OSIMAGE_H__
#define __OSIMAGE_H__

#include <Control.h>
#include <List.h>



enum osimage_type { IMAGE_DEVICE = 0, 
				IMAGE_BUS, 
				IMAGE_MODULE,
				IMAGE_KERNEL,
				IMAGE_SYSLIB,
				IMAGE_SERVER,
				IMAGE_LIB,
				IMAGE_APP};


class OSImage : public BControl {
	public:
						OSImage(BRect frame, const char *name, osimage_type type = IMAGE_APP);
						~OSImage();
		virtual void	Draw(BRect updateRect);
		virtual void	MouseDown(BPoint where);
		virtual void 	FrameMoved(BPoint origin);
		virtual void	FrameResized(float width, float height);
				bool	GetMatch();
				void	SetMatch(bool match); 
		const char *	GetName();
				void	AddRelationship(void *relationship);
				void	RemoveRelationship(void *relationship);
				void	GetType(osimage_type *type);
		
	private:
				BPath	*fimagePath;
				BString *fOSImageName;
				osimage_type fimageType;
				bool	flistMatch;  //Kind of like an archive bit
				BMessage *fmsg;
				BList *frelationshipList;
				
};																		
#endif