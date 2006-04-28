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
to describe the fields used in each message.  These Messages can be used by
plugins.

Note: Messages are how most of my intraprocess communiction occurs.  Example
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

#define MENU_SAVE_IMAGE  		'sima' 
// Not Currently Used
// Maybe we can use this for to save an image of the current screen
// Is that necessary since we can take screenshot?  We also need to be able
// to print the OS image.  Should be able to select to print the plugin also.
#define MENU_VIEW_TEXT 	 		'vtex' 
// Creates a text file in /tmp then displays it in a text editor
#define MENU_VIEW_IM_ENABLE 	'vdet'
// Enables the selected instructional module
// 	Fields 	Name:		Type:		Purpose:
//			IMName		String		Show the selected addon named IMName
#define MENU_VIEW_IM_DISABLE	'vdis'
// Disables all instructional modules

#define MENU_VIEW_RELATIONSHIP	'vrel'
//	Toggles the Relationship view

#define MENU_SETTINGS_REFRESH 	'msre'
// Set the Refresh Rate to Updating OSImage objects
// If the Rate is 0 then disable Pulse updates
// The window will multiple the value by 1000000 to get the number of seconds
// 	Fields 	Name:		Type:		Purpose:
//			refreshRate	int8		Set the Refresh Rate of Window

#define MENU_SET_COLOR_RELATE	'mscr'
// Sets Relationship type 
//			type		int32		The relationship types from the OSim Library

// Set the color of the line 
//			red			int8		RGB colors
//			green		int8
//			blue		int8

#define MENU_SET_COLOR_BACK 	'mscb'
// Set the Background Color
// 	Fields 	Name:		Type:		Purpose:
//			red			int8		RGB colors
//			green		int8
//			blue		int8

#define MENU_SET_COLOR_IMAGE 	'msci'
// Set the Background Color
// 	Fields 	Name:		Type:		Purpose:
//			red			int8		RGB colors
//			green		int8
//			blue		int8

#define MENU_SET_COLOR_FOCUS 	'mscf'
// Set the Background Color
// 	Fields 	Name:		Type:		Purpose:
//			red			int8		RGB colors
//			green		int8
//			blue		int8

#define DRAW_LINE 				'drli'
// Tells the Windows to draw a line
// Can be used to erase the line by drawing a white line
// 	Fields 	Name:		Type:		Purpose:
//			appPoint	BPoint		Location of Application Point
//			libPoint	BPoint		Location of Library Point


// Relationships use image type to draw line.  This allows the menu to control
// color without having to change the color in all the relationship objects 
//			type		int32		The image types
 
// We will leave these as options in case a plugin wants to draw a line with
// a special color. 
//			red			int8		RGB colors
//			green		int8
//			blue		int8

#define DRAW_RECT				'drre'
// Tells the Windows to draw a rectangle
// Can be used to erase the  by drawing a black line ||Background color
// 	Fields 	Name:		Type:		Purpose:
//			drawRect	BRect		Location of Rectangle

// Relationships use image type to draw a rectangle.  If type is specified this will
// draw a rectangle for the selected layer 
//			type		int32		The image types from the OSim Library
 
// We will leave these as options in case a plugin wants to draw a rectangle with
// a special color. 
//			red			int8		RGB colors
//			green		int8
//			blue		int8


#define OSIMAGE_SELECTED 		'osis'
//  If the plugin addon is activated it will allow the OS image to send
//	a message to the active plugin.  The OS image provides these fields
// 	Fields 	Name:		Type:		Purpose:
//			name		String		The OS image path		
//			type		int32		The image types from the OSim Library
 
#endif