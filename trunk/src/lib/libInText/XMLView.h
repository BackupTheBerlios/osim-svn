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
#ifndef __XMLVIEW_H__
#define __XMLVIEW_H__

#include <View.h>
#include "XMLDocument.h"

class XMLView : public BView {
	public:
						XMLView(BRect frame, char *name);
		virtual void	Draw(BRect updateRect);
				void 	SetRef(BEntry *entry);
				void	PreviousButton(void);
				void    NextButton(void);
				void	PageCount(uint32 *num);
				void	CurrentPage(uint32 *num);
		virtual void	MessageReceived(BMessage *message);		
	
	private:
		BEntry *currentEntry;
		XMLDocument *currentXMLDoc;	
		uint32 fCurrentPage;
		uint32 fMaxPages;
		BString *fXMLData;
};

#endif