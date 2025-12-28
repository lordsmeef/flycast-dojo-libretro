/*
	Simple MSVC compatibility helpers for libretro-common C sources.
*/
#include <stdlib.h>
#include <string.h>

char *retro_strdup__(const char *orig)
{
	if (orig == NULL)
		return NULL;

	size_t len = strlen(orig) + 1;
	char *dst = (char *)malloc(len);
	if (dst != NULL)
		memcpy(dst, orig, len);
	return dst;
}
