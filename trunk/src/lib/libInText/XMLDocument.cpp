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
#include <Entry.h>
#include <String.h>
#include <stdio.h>

#include "XMLDocument.h"

XMLDocument::XMLDocument(const BEntry *entry) {
	
	fXMLData = new BString();
	fElement = new BString();
	fElementEnd = new BString();
	fAttribute = new BString();
	
	off_t size;
	ssize_t readSize;
	status_t sizeStatus;
	BFile XMLFile(entry, B_READ_ONLY);
	sizeStatus = XMLFile.GetSize(&size);
	if (sizeStatus == B_NO_ERROR) {
		char *data = new char[size];
		readSize = XMLFile.Read((void *)data,size);
		if (readSize > 0 ) {
			printf("Set RefRead File Successful\n");
			fXMLData->SetTo(data); 
			delete data;
		}
	}	
}

XMLDocument::XMLDocument(void) {
	fXMLData = new BString();	
	fElement = new BString();
	fElementEnd = new BString();
	fAttribute = new BString();
}

void XMLDocument::SetRef(const BEntry *entry) {
	
	off_t size;
	ssize_t readSize;
	status_t sizeStatus;
	BFile XMLFile(entry, B_READ_ONLY);
	sizeStatus = XMLFile.GetSize(&size);
	if (sizeStatus == B_NO_ERROR) {
		char *data = new char[size];
		readSize = XMLFile.Read((void *)data,size);
		if (readSize > 0 ) {
			printf("Set RefRead File Successful\n");
			fXMLData->SetTo(data); 
			delete data;
		}
	}	
	
}


void XMLDocument::GetAttributeData(const char *elementName, const char *attributeName, BString *buffer, uint32 elementIndex) {
	
	
	fElement->SetTo(elementName);
	fElementEnd->SetTo(elementName);
	fAttribute->SetTo(attributeName);
	
	//Sets string for seaching for elements and not text within document
	fElement->Insert("<",0);
	fElementEnd->Insert("</",0);
	
	uint32 index = 0;
	bool match = false;
	int32 elementLocation = 0;
	int32 attributeLocation = 0;
	int32 charStartIndex = 0;
	int32 charStopIndex = 0;
	int32 charSize = 0;
	
	while (!match) {
		elementLocation = fXMLData->IFindFirst(*fElement, elementLocation);
		if (elementLocation != B_ERROR) {
			index++;
			if (index == elementIndex) {
				match = true;
				attributeLocation = fXMLData->IFindFirst(*fAttribute, elementLocation);
				if (attributeLocation != B_ERROR) {
					charStartIndex = fXMLData->IFindFirst("\"", attributeLocation);
					charStartIndex++;
					charStopIndex = fXMLData->IFindFirst("\"", charStartIndex);
					charSize = charStopIndex - charStartIndex;
					if (charSize > 0) {
						fXMLData->CopyInto(*buffer,charStartIndex,charSize);
					}
				}	
			}
		} else {
			match = true;
			buffer->SetTo(NULL);
		}
	}
		
}

void XMLDocument::GetElementData(const char *elementName, BString *buffer, uint32 elementIndex) {
	
	
	fElement->SetTo(elementName);
	fElementEnd->SetTo(elementName);
		
	//Sets string for seaching for elements and not text within document
	fElement->Insert("<",0);
	fElementEnd->Insert("</",0);
	
	uint32 index = 0;
	bool match = false;
	int32 elementLocation = 0;
	int32 charStartIndex = 0;
	int32 charStopIndex = 0;
	int32 charSize = 0;
	
	while (!match) {
		elementLocation = fXMLData->IFindFirst(*fElement, elementLocation);
		if (elementLocation != B_ERROR) {
			index++;
			if (index == elementIndex) {
				match = true;
				charStartIndex = fXMLData->IFindFirst(">", elementLocation);
				if (charStartIndex != B_ERROR) {
					charStartIndex++;
					charStopIndex = fXMLData->IFindFirst(*fElementEnd, charStartIndex);
					charSize = charStopIndex - charStartIndex;
					if (charSize > 0) {
						fXMLData->CopyInto(*buffer,charStartIndex,charSize);
					}
				}	
			} else {
				elementLocation += 1;
			}
		} else {
			match = true;
			buffer->SetTo(NULL);
		}
	}
		
}

void XMLDocument::CountElements(const char *elementName, uint32 *index) {
	
	//Very Rudimentary way counting tags
	fElement->SetTo(elementName);
	fElement->Insert("<",0);
	
	bool match = false;
	int32 elementLocation = 0;
	
	*index = 0;
	while (!match) {
		elementLocation = fXMLData->IFindFirst(*fElement, elementLocation);
		if (elementLocation != B_ERROR) {
			(*index)++;
			elementLocation += 2;
		} else {
			match = true;
		}
	}
		
}
