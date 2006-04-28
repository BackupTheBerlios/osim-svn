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
#ifndef __OSRELATIONSHIP_H__
#define __OSRELATIONSHIP_H__

#include <String.h>

#include "OSImage.h"

enum osrelationship_type { APP_SYSLIB_RELATE = 0, 
				APP_LIB_RELATE, 
				SYSLIB_KERNEL_RELATE,
				KERNEL_MODULE_RELATE};

class OSRelationship {
	public:
						//to create a relationship I must have to images	
						OSRelationship(OSImage *appImage, OSImage *libImage, BWindow *window);
						~OSRelationship();
				void	Move();
				void	Animate();
				void	RemoveLibRelationship(void *relationship);
				void 	RemoveAppRelationship(void *relationship);
				void	GetName(BString *);
		
	private:
				BString fOSRelationshipName;
				BRect fappRect, flibRect;
				BPoint fappPoint, flibPoint;
				OSImage *fapp_image, *flib_image;
				BMessage *fmsg;
				BWindow *fcurrent_window;
				osimage_type fappType, flibType;
};												
						
#endif