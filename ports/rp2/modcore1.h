#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int launch_interface();
int set_color_interface(int);

#ifdef __cplusplus
} // extern "C"
#endif

int rgb565(unsigned char r, unsigned char g, unsigned char b) {
  unsigned char red = r >> 3;
  unsigned char green = g >> 2;
  unsigned char blue = b >> 3;

  int result = (red << (5 + 6)) | (green << 5) | blue;

  return result;
}
