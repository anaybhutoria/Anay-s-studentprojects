/* GIMP RGBA C-Source image dump (waterTile.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[36 * 36 * 2 + 1];
} WaterTile = {
  36, 36, 2,
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s"
  ">s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s>s",
};

