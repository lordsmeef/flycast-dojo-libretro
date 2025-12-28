#ifndef LIBRETRO_COMMON_FILE_STREAM_H
#define LIBRETRO_COMMON_FILE_STREAM_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque libretro VFS file handle. */
typedef struct RFILE RFILE;

typedef struct core_file
{
   void *argp;
   uint64_t (*fsize)(struct core_file *file);
   size_t (*fread)(void *ptr, size_t size, size_t nmemb, struct core_file *file);
   int (*fclose)(struct core_file *file);
   int (*fseek)(struct core_file *file, int64_t offset, int whence);
} core_file;

#define core_fsize(file) ((file)->fsize((file)))
#define core_fread(file, ptr, size) ((file)->fread((ptr), 1, (size), (file)))
#define core_fclose(file) ((file)->fclose((file)))
#define core_fseek(file, offset, whence) ((file)->fseek((file), (offset), (whence)))

#ifdef __cplusplus
}
#endif

#endif
