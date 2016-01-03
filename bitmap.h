#ifndef _BITMAP_H_
#  define _BITMAP_H_

#  include <stdio.h>
#  include <stdlib.h>
#  include <errno.h>
#  include <windows.h>
#  include <wingdi.h>

#  include <GL/gl.h>


/*
 * Make this header file work with C and C++ source code...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

extern void	*LoadDIBitmap(char *filename, BITMAPINFO **info);
extern int	SaveDIBitmap(char *filename, BITMAPINFO *info, void *bits);
extern void	*ReadDIBitmap(BITMAPINFO **info);
extern int	PrintDIBitmap(HWND owner, BITMAPINFO *info, void *bits);

extern GLubyte	*ConvertRGB(BITMAPINFO *info, void *bits);

#  ifdef __cplusplus
}
#  endif /* __cplusplus */
#endif /* !_BITMAP_H_ */
