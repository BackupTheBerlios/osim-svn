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


#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "kinfo_wrapper.h"

static int fd;

status_t init_kinfo_wrapper(void)
{
	static const char device[] = "/dev/" KINFO_DEVICE_NAME;

	fd = open(device, 0);
	if (fd < 0)
		return errno;
	return B_OK;
}

status_t uninit_kinfo_wrapper(void)
{
	close(fd);
	return B_OK;
}

status_t get_next_module_name(uint32 *cookie,
		char *name, uint32 size)
{
	status_t result;
	struct kinfo_ioctl_data params;

	params.magic = KINFO_GET_NEXT_MODULE_NAME;
	params.cookie = *cookie;
	params.data = name;
	params.data_len = size;

	result = ioctl(fd, params.magic, &params, sizeof(params));

	if (result == B_OK) *cookie = params.cookie;

	return result;
}
