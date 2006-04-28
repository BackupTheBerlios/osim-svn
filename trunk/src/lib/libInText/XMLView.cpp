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

#include "XMLDocument.h"
#include "XMLView.h"


XMLView::XMLView(BRect rect, char *name) 
		: BView(rect, name, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE | B_FRAME_EVENTS |B_SUBPIXEL_PRECISE) 
{
	currentEntry = new BEntry();
	currentXMLDoc = new XMLDocument();	
	fMaxPages = 1;
	fCurrentPage = 1;	
	fXMLData = new BString();

}

void XMLView::Draw(BRect updateRect) {
	
	//set fXMLData to current page
	currentXMLDoc->GetElementData("sect2",fXMLData, fCurrentPage);
	
	//Set Draw size
	float leftMargin = 5.0;
	float rightMargin = 5.0;
	float viewWidth;
	float lineSpace = 4.0;
	
	BRect xmlViewRect = Bounds();
	viewWidth = xmlViewRect.Width() - leftMargin - rightMargin;
	
	//loop until all lines are drawn
	BString currentLine;
	int32 currentCharIndex = 0;
	int32 fXMLDataSize = fXMLData->Length();
	
	BString currentWord;
	int32 nextSpaceIndex;
	
	int32 nextTagIndex;
	int32 endOfTagIndex;
	BString currentTag;
	
	//get line spacing from the BFont class
	font_height height;
	GetFontHeight(&height);
	lineSpace = height.descent + height.leading + height.ascent;
	float currentLineIndex;
	lineSpace += (lineSpace * 0.5);
	currentLineIndex = lineSpace;
	MovePenTo(leftMargin,lineSpace);
	
	printf("fXMLDataSize = %i\n",fXMLDataSize);
	
	while (currentCharIndex < fXMLDataSize - 1) {
		printf("currentCharIndex = %i\n",currentCharIndex);
		//Process tags
		if (fXMLData->ByteAt(currentCharIndex) == '<')  {
			endOfTagIndex = fXMLData->FindFirst(">", currentCharIndex);
			if (endOfTagIndex - currentCharIndex >= 1) {
				fXMLData->CopyInto(currentTag,currentCharIndex,endOfTagIndex - currentCharIndex);
			}
			
			//if closing para tag then draw line and start new line
			if (currentTag.IFindFirst("/para") != B_ERROR) {			
				DrawString(currentLine.String());
				currentLine = " ";
				currentLineIndex += lineSpace * 2;
				MovePenTo(leftMargin,currentLineIndex);
				currentCharIndex = endOfTagIndex + 1;
			
			//if tag is para then indent
			} else if (currentTag.IFindFirst("para") != B_ERROR) {
				currentLine << "    ";
				currentCharIndex = fXMLData->FindFirst(">", currentCharIndex);
				currentCharIndex++;
			
			} else if (currentTag.IFindFirst("/itemizedlist") != B_ERROR) {			
				DrawString(currentLine.String());
				currentLine = "";
				currentLineIndex += lineSpace;
				MovePenTo(leftMargin,currentLineIndex);
				currentCharIndex = endOfTagIndex + 1;
			
			
			//if itemized list closing or opening skip a line
			} else if (currentTag.IFindFirst("itemizedlist") != B_ERROR) {			
				DrawString(currentLine.String());
				currentLine = "";
				currentLineIndex += lineSpace;
				MovePenTo(leftMargin,currentLineIndex);
				currentCharIndex = endOfTagIndex + 1;
			//starrt new line
			} else if (currentTag.IFindFirst("/listitem") != B_ERROR) {			
				DrawString(currentLine.String());
				currentLine = "";
				currentLineIndex += lineSpace;
				MovePenTo(leftMargin,currentLineIndex);
				currentCharIndex = endOfTagIndex + 1;
			
			//if listiten then indent draw line start new line
			} else if (currentTag.IFindFirst("listitem") != B_ERROR) {
				currentLine << "       * ";
				currentCharIndex = fXMLData->FindFirst(">", currentCharIndex);
				currentCharIndex++;
			
			//start a new line
			} else if (currentTag.IFindFirst("/title") != B_ERROR) {			
				DrawString(currentLine.String());
				currentLine = "";
				currentLineIndex += lineSpace;
				MovePenTo(leftMargin,currentLineIndex);
				currentCharIndex = endOfTagIndex + 1;
			
			//Set the font to bold for titles
			} else if (currentTag.IFindFirst("title") != B_ERROR) {
				
				currentCharIndex = fXMLData->FindFirst(">", currentCharIndex);
				currentCharIndex++;
			
			//Create MediaLink
			
			//Else just strip tag
			} else {
				currentCharIndex = fXMLData->FindFirst(">", currentCharIndex);
				currentCharIndex++;
			}
		//Process text
		//add word to line unless adding word would create the line
		//to be too long, then we want to darw the line and start fresh
		//with a new one.
		} else {
			//do not include anything less than a space in a line
			if (fXMLData->ByteAt(currentCharIndex) <= ' ') {
				currentCharIndex++;
			//if the character is not a tag or space we need to add it to the line
			} else {
				nextSpaceIndex = fXMLData->FindFirst(" ",currentCharIndex);
				nextTagIndex = fXMLData->FindFirst("<",currentCharIndex);
				if ((nextSpaceIndex > 0) && (nextTagIndex > 0)){			
					if (nextTagIndex < nextSpaceIndex) {
						nextSpaceIndex = nextTagIndex;
					} 
					if (nextSpaceIndex - currentCharIndex >= 1){
						fXMLData->CopyInto(currentWord,currentCharIndex,nextSpaceIndex - currentCharIndex);
						if ((StringWidth(currentLine.String()) + StringWidth(currentWord.String())) < viewWidth) {
							currentLine << currentWord.String() << " ";
						} else {
							DrawString(currentLine.String());
							currentLine = currentWord.String();
							currentLine << " ";
							currentLineIndex += lineSpace;
							MovePenTo(leftMargin,currentLineIndex);
						}	
					}
					currentCharIndex = nextSpaceIndex;
				} else {
					if (nextTagIndex > nextSpaceIndex) {
						nextSpaceIndex = nextTagIndex;
					} 
					if (nextSpaceIndex - currentCharIndex >= 1){
						fXMLData->CopyInto(currentWord,currentCharIndex,nextSpaceIndex - currentCharIndex);
						if ((StringWidth(currentLine.String()) + StringWidth(currentWord.String())) < viewWidth) {
							currentLine << currentWord.String() << " ";
							//DrawString(currentLine.String());
						} else {
							DrawString(currentLine.String());
							currentLine = currentWord.String();
							currentLine << " ";
							currentLineIndex += lineSpace;
							MovePenTo(leftMargin,currentLineIndex);
							//DrawString(currentLine.String());
						}	
						
					}
					currentCharIndex = nextSpaceIndex;
				}
			}
		} // End of Current Char Detect
	}  //End of While
	
} //End of function 


void XMLView::MessageReceived(BMessage *message)
{
	status_t result;
	switch (message->what) {
		default: 
			BView::MessageReceived(message);
			break;
	}
}

void XMLView::SetRef(BEntry *entry)
{
	entry_ref ref;
	entry->GetRef(&ref);
	currentEntry->SetTo(&ref);
	currentXMLDoc->SetRef(currentEntry);	
	currentXMLDoc->CountElements("sect2",&fMaxPages);
	fCurrentPage = 1;
	Invalidate();
}

void XMLView::PreviousButton(void)
{
	fCurrentPage--;
	if (fCurrentPage < 1) {
		fCurrentPage = fMaxPages;
	}
	Invalidate();
}

void XMLView::NextButton(void)
{
	fCurrentPage++;
	if (fCurrentPage > fMaxPages) {
		fCurrentPage = 1;
	} 
	Invalidate();
}

void XMLView::PageCount(uint32 *num) {
	*num = fMaxPages;
}

void XMLView::CurrentPage(uint32 *num) {
	*num = fCurrentPage;
}

