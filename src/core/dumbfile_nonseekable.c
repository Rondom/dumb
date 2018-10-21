//
// Created by andreas on 21/10/18.
//

#include <internal/dumbfile.h>
#include "dumbfile_nonseekable.h"
#include "internal/dumb.h"

typedef struct dfs_nonseekable_wrapper {
    DUMBFILE_SYSTEM* wrapped;
    size_t buffer_size;
    char* buffer;
    size_t pos;
    size_t max_read_pos;
    void* file;
} dfs_nonseekable_wrapper;

#define INITIAL_BUFFER_SIZE 4096


#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)(-1))
#endif

static int resize_buffer(dfs_nonseekable_wrapper* file, off_t new_pos) {
    // TODO: find good factor for exponential increase
    if (new_pos > file->buffer_size) {
        off_t new_size = file->buffer_size;
        while (new_pos > new_size) {
            new_size *= 1.5;
        }
        if (new_size > SIZE_MAX) {
            return -1;
        }
        void* buffer = realloc(file->buffer, new_size);
        if (!buffer) {
            return -1;
        }
        file->buffer = buffer;
        file->buffer_size = new_size;
    }
};

DUMBFILE *nonseekable_open(const char *filename)
}

static int nonseekable_getc(void *f) {
    dfs_nonseekable_wrapper* file = (dfs_nonseekable_wrapper*) f;
    size_t new_pos = file->pos + 1;
    if (new_pos < file->max_read_pos) {
        int res = dumbfile_getc(file->file);
        if (res < 0) {
            return res;
        }
        if (resize_buffer(file, new_pos) < 0) {
            return -1;
        }
        file->buffer[new_pos] = res;
    }

    return file->buffer[new_pos];
}

static int nonseekable_seek(void *f) {
    dfs_nonseekable_wrapper* file = (dfs_nonseekable_wrapper*) f;
    size_t new_pos = file->pos + 1;
    if (new_pos < file->max_read_pos) {
        if (resize_buffer(file, new_pos) < 0) {
            return -1;
        }
        int res = file->wrapped->getc(file->file);
        if (res < 0) {
            return res;
        }
        file->buffer[new_pos] = res;
    }

    return file->buffer[new_pos];
}


static void nonseekable_close(void *f) {
    dfs_nonseekable_wrapper* file = (dfs_nonseekable_wrapper*) f;
    free(file->buffer);
    file->buffer = NULL;
    file->buffer_size = 0;
    file->max_read_pos = 0;
    return file->wrapped->close(file->file);
}


static const DUMBFILE_SYSTEM dumbfilesystem_nonseekable_wrapper_ = {NULL, // open (called already by dumbfile_open)
                                                              &nonseekable_skip,
                                                              &nonseekable_getc,
                                                              &nonseekable_getnc,
                                                              &nonseekable_close,
                                                              &nonseekable_seek,
                                                              &nonseekable_get_size};

/**
 * If the DUMBFILE_SYSTEM for the given DUMBFILE is lacking support for
 * random access (no dfs->seek and/or dfs->get_size), this function will
 * modify the given dumbfile to buffer its contents to enable random access.
 * @param dumbfile
 * @return 0 on success, negative on failure
 */
int wrap_nonseekable_dumbfile_if_needed(DUMBFILE* dumbfile) {
    dfs_nonseekable_wrapper* nonseekable = malloc(sizeof(dfs_nonseekable_wrapper));
    if (!nonseekable) {
        return -1;
    }
    nonseekable->buffer_size = INITIAL_BUFFER_SIZE;
    nonseekable->buffer = malloc(nonseekable->buffer_size);
    if (!nonseekable->buffer) {
        free(nonseekable);
        return -1;
    }
    nonseekable->pos = 0;
    nonseekable->max_read_pos = 0;
    nonseekable->file = dumbfile->file;
    nonseekable->wrapped = dumbfile->dfs;
    dumbfile->dfs = &dumbfilesystem_nonseekable_wrapper_;
    dumbfile->file = nonseekable;
    return 0;
}
