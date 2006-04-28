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

#include <MenuItem.h>

#include "ColorMenuItem.h"

//The main purpose for this object is to get the Color from the BMessage
// and display it instead of a label for a menu. The other functions take 
// care of the highlighting and selection
ColorMenuItem::ColorMenuItem(BMessage *message) 
	: BMenuItem("Color Choice",message) {
	
	message->FindInt8("red",&red);
	message->FindInt8("green",&green);
	message->FindInt8("blue",&blue);
}

void ColorMenuItem::DrawContent() {
	BMenu *menu = Menu();
	selectBox = Frame();
	selectBox.InsetBy(1.0,1.0);
	menu->SetHighColor(0.0,0.0,0.0);
	menu->StrokeRect(selectBox);
}

void ColorMenuItem::Draw() {
	
	BMenu *menu = Menu();
	colorBox = Frame();
	menu->SetHighColor(222,222,222);
	menu->FillRect(colorBox);
	colorBox.InsetBy(4.0,4.0);
	menu->SetHighColor((uint8)red,(uint8)green,(uint8)blue);
	menu->FillRect(colorBox);
	
	if (IsMarked()) {
		DrawContent();
	}
	
	if(IsSelected()) {
		Highlight(true);
	} 

}

void ColorMenuItem::Highlight(bool on) {
	
	BMenu *menu = Menu();
	
	// a nonstandard but simple way to draw highlights
	colorBox = Frame();
	//colorBox.InsetBy(3.0,3.0);
	if (on) {
		menu->SetHighColor((uint8)red,(uint8)green,(uint8)blue);
		menu->FillRect(colorBox);
	} else {
		menu->SetHighColor(222,222,222);
		menu->FillRect(colorBox);
		colorBox.InsetBy(4.0,4.0);
		menu->SetHighColor((uint8)red,(uint8)green,(uint8)blue);
		menu->FillRect(colorBox);
	}
	if (IsMarked()) {
			DrawContent();
		}
	
}