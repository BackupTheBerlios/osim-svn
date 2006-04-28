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
#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__


#define MENU_BAR_HEIGHT 18.0

// Bit values for turning updating on or off for certain OS objects
const uint32 UPDATE_APP_DRAW 		= 0x00000001;	
const uint32 UPDATE_LIB_DRAW 		= 0x00000002;	
const uint32 UPDATE_SERVER_DRAW 	= 0x00000004;	
const uint32 UPDATE_KERNEL_DRAW		= 0x00000008;	
const uint32 UPDATE_FILESYSTEM_DRAW	= 0x00000010;	
const uint32 UPDATE_DRIVER_DRAW 	= 0x00000020;	


#endif