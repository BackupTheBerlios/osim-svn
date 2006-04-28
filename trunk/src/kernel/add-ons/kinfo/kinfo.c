/*
Copyright (c) 2006 Bart Upchurch

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

/* ++++++++++
	
	Used driver.c
	A skeletal device driver as a guide to create kinfo
+++++ */

#include <KernelExport.h>
#include <Drivers.h>
#include <Errors.h>

#include "kinfo.h"


int32 api_version = B_CUR_DRIVER_API_VERSION;

/* ----------
	init_hardware - called once the first time the driver is loaded
----- */
status_t
init_hardware (void)
{
	return B_OK;
}


/* ----------
	init_driver - optional function - called every time the driver
	is loaded.
----- */
status_t
init_driver (void)
{
	return B_OK;
}


/* ----------
	uninit_driver - optional function - called every time the driver
	is unloaded
----- */
void
uninit_driver (void)
{
}

	
/* ----------
	kinfo_open - handle open() calls
----- */

static status_t
kinfo_open (const char *name, uint32 flags, void** cookie)
{
	*cookie = NULL;
	return B_OK;
}


/* ----------
	kinfo_read - handle read() calls
----- */

static status_t
kinfo_read (void* cookie, off_t position, void *buf, size_t* num_bytes)
{
	*num_bytes = 0;				/* tell caller nothing was read */
	return B_IO_ERROR;
}


/* ----------
	kinfo_write - handle write() calls
----- */

static status_t
kinfo_write (void* cookie, off_t position, const void* buffer, size_t* num_bytes)
{
	*num_bytes = 0;				/* tell caller nothing was written */
	return B_IO_ERROR;
}


/* ----------
	kinfo_control - handle ioctl calls
----- */

static status_t
kinfo_control (void* cookie, uint32 op, void* arg, size_t len)
{
	status_t result;
	struct kinfo_ioctl_data *params =(struct kinfo_ioctl_data *)arg;
	
	if (params == NULL || params->magic != op)
		return B_BAD_VALUE; 		
			
	switch (op) {
	
		case KINFO_GET_NEXT_MODULE_NAME:
			result = get_next_loaded_module_name(&params->cookie,(char *)params->data,&params->data_len);
			return result;
			break;
		default:
			return EINVAL;
	}
	
	return B_OK;
}


/* ----------
	kinfo_close - handle close() calls
----- */

static status_t
kinfo_close (void* cookie)
{
	return B_OK;
}


/* -----
	kinfo_free - called after the last device is closed, and after
	all i/o is complete.
----- */
static status_t
kinfo_free (void* cookie)
{
	return B_OK;
}


/* -----
	null-terminated array of device names supported by this driver
----- */

static const char *kinfo_name[] = {
	"misc/kinfo",
	NULL
};

/* -----
	function pointers for the device hooks entry points
----- */

device_hooks kinfo_hooks = {
	kinfo_open, 			/* -> open entry point */
	kinfo_close, 			/* -> close entry point */
	kinfo_free,			/* -> free cookie */
	kinfo_control, 		/* -> control entry point */
	kinfo_read,			/* -> read entry point */
	kinfo_write			/* -> write entry point */
};

/* ----------
	publish_devices - return a null-terminated array of devices
	supported by this driver.
----- */

const char**
publish_devices()
{
	return kinfo_name;
}

/* ----------
	find_device - return ptr to device hooks structure for a
	given device name
----- */

device_hooks*
find_device(const char* name)
{
	return &kinfo_hooks;
}

