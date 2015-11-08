/* null_nbdkit.c
 * See https://github.com/pepaslabs/nbdkit-null-plugin
 * Copyright (C) 2015 Jason Pepas.
 * Released under the terms of the MIT license.  See https://opensource.org/licenses/MIT
 */

// see also https://github.com/libguestfs/nbdkit/blob/master/docs/nbdkit-plugin.pod

#include <config.h>
#include <nbdkit-plugin.h> // nbdkit_error(), etc.
#include <strings.h> // bzero(), etc.

#define THREAD_MODEL NBDKIT_THREAD_MODEL_PARALLEL

// per-connection state (not used):
int handle;

void* null_open(int readonly)
{
    return (void*)(&handle);
}

int64_t null_get_size(void *passed_handle)
{
    return (int64_t)(8) * 1024 * 1024 * 1024;
}

int null_pread(void *passed_handle, void *buf, uint32_t count, uint64_t offset)
{
    bzero(buf, count);
    return 0;
}

int null_pwrite(void *passed_handle, const void *buf, uint32_t count, uint64_t offset)
{
    return 0;
}

static struct nbdkit_plugin plugin = {
    .name              = "null",
    .longname          = "nbdkit null plugin",
    .description       = "An nbdkit plugin which serves /dev/zero and writes to /dev/null.",
    .version           = "0.0",

    .open              = null_open,
    .get_size          = null_get_size,

    .pread             = null_pread,
    .pwrite            = null_pwrite
};

NBDKIT_REGISTER_PLUGIN(plugin)
