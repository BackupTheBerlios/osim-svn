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
/*
This file contains all the messages the software responds to.  I also tried
to describe the fields used in each message.  

Note: Messages are how most of my intraprocess communication occurs.  Example
my OS relations draw lines with messages

todo:
	DRAW_LINE: Be able to set the patteren of line to allow animation
	Create a message to allow filters on the displayed images.  This will
	allow plugins to limit the number of OS images on the screen.  It will 
	also allow the plugin to animate a particular connected.  The plugin
	should also be able to set the focused view to draw attention to it.
	
	The plugin should be able to query the main view to obtain a list of
	current shown images.  The plugin can modify the displayed images.
*/
#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#define UNIT_CHANGED  			'unch' 
// Notifies the Unit View which file to use
// 	Fields 	Name:		Type:		Purpose:
//		"entry"			Entry Ref	Name of file		 
#define SET_UNIT_VIEW			'seuv'
// Notifies the Unit View which file to use
// 	Fields 	Name:		Type:		Purpose:
//		"view"			Pointer		Sets Pointer to Unit View	
#define PREVIOUS_BUTTON			'prbu'
#define NEXT_BUTTON				'bepu'

#endif