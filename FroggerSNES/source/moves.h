/* GIMP RGB C-Source image dump (moves.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[120 * 25 * 2 + 1];
} Moves = {
  120, 25, 2,
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\242\020\212RIJIJIJIJIJIJIJIJIJIJIJIJIJIJ"
  "IJIJIJiJ(B\000\000\000\000\000\000\000\000IJIJIJIJIJIJIJIJIJIJIJIJIJIJIJIJIJ\252R$!\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\303\030\333\336\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\353ZY\316\000\000\242\020\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\000\000\377\377\377\377\377\377\377\377\377\377\216s\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\064\245\377\377\377\377\377\377\377\377<\347\252"
  "R\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\242\020\000\000\000\000\000\000mk\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\337\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000a\010\377"
  "\377\377\377\202\020\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\262\224\377\377\030\306\000\000\202\020\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\000\000\020\204\377"
  "\377\377\377\377\377\377\377<\347\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\377\377\377\377\377\377\377\377\377\377E)IJ\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\317{\000\000\000\000\000\000e)\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\206\061\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000a\010\377\377\377\377\377\377\313Z\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\202\020\373\336\377\377\377\377"
  "\367\275\000\000\202\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\000\000A\010\377\377\377\377\377\377\377\377"
  "\377\377\347\071\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\216s\377\377\377\377\377"
  "\377\377\377\276\367\000\000\252R\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\367\275\000\000\000\000\000\000\000\000<\347\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\256s\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000a\010\377\377\377\377\377\377\377\377U\255\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000IJ\377\377\377\377\377\377\377\377\367\275\000\000\202"
  "\020\377\377\377\377\377\377\377\377\377\377\212R$!e)e)e)e)e)e)$!,c\377\377"
  "\377\377\377\377\377\377\377\377\000\000\000\000U\255\377\377\377\377\377\377\377"
  "\377\030\306\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377\377\377\377\377\377\377\377"
  "\377\377\252R\000\000\252R\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\353Z\377\377\377\377"
  "\377\377\377\377\377\377\034\347\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\024\245\024\245\064\245q\214\000\000\000\000a\010\377\377"
  "\377\377\377\377\377\377\377\377}\357e)\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\222"
  "\224\377\377\377\377\377\377\377\377\377\377\367\275\000\000\202\020\377\377\377"
  "\377\377\377\377\377\377\377E)\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000(B\377\377"
  "\377\377\377\377\377\377\377\377\000\000\000\000\343\030\377\377\377\377\377\377\377"
  "\377\377\377\202\020\000\000\000\000\000\000\000\000\000\000\000\000IJ\377\377\377\377\377\377\377"
  "\377\377\377\000\000\000\000\252R\377\377\377\377\377\377\377\377\377\377\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\313Z\377\377\377"
  "\377\377\377\377\377\377\377e)\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\377\377\377\377\377\377]\357\000\000\000\000a\010\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\353Z\000\000\000\000\000\000\000\000\000\000"
  "a\010Y\316\377\377\377\377\377\377\377\377\377\377\377\377\367\275\000\000\202"
  "\020\377\377\377\377\377\377\377\377\377\377e)\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000IJ\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000\000\266\265\377\377"
  "\377\377\377\377\377\377\323\234\000\000\000\000\000\000\000\000\000\000\000\000y\316\377\377\377"
  "\377\377\377\377\377\317{\000\000\000\000\252R\377\377\377\377\377\377\377\377\377"
  "\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\313"
  "Z\377\377\377\377\377\377\377\377\377\377\206\061\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377\377\377\377\377\377\034\347"
  "\000\000\000\000a\010\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\064\245\000\000\000\000\000\000\010B\276\367\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\367\275\000\000\202\020\377\377\377\377\377\377\377\377\377\377"
  "e)\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000IJ\377\377\377\377\377\377\377\377\377"
  "\377\000\000\000\000\000\000$!\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000\000\000"
  "\000\000\000\004!\377\377\377\377\377\377\377\377\377\377A\010\000\000\000\000\252R\377\377"
  "\377\377\377\377\377\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\313Z\377\377\377\377\377\377\377\377\377\377\206"
  "\061\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377"
  "\377\377\377\377\377]\357\000\000\000\000a\010\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\373\336\303\030\060\204\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\367\275\000\000\202"
  "\020\377\377\377\377\377\377\377\377\377\377e)\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000IJ\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000\000\000\000\232\326\377"
  "\377\377\377\377\377\377\377mk\000\000\000\000\000\000\000\000\363\234\377\377\377\377\377"
  "\377\377\377\024\245\000\000\000\000\000\000\252R\377\377\377\377\377\377\377\377\377"
  "\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\313"
  "Z\377\377\377\377\377\377\377\377\377\377$!\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\327\275\030\306\030\306\064\245\000\000\000"
  "\000a\010\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\367\275\000\000\202\020\377\377\377\377\377\377\377"
  "\377\377\377e)\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000IJ\377\377\377\377\377\377"
  "\377\377\377\377\000\000\000\000\000\000\000\000iJ\377\377\377\377\377\377\377\377<\347\000"
  "\000\000\000\000\000\000\000\377\377\377\377\377\377\377\377\377\377\202\020\000\000\000\000\000\000"
  "\252R\377\377\377\377\377\377\377\377\377\377\020\204\020\204\020\204\020\204"
  "\020\204\020\204\020\204\020\204\020\204\020\204\020\204\020\204q\214\246\061\000\000"
  "\000\000\313Z\377\377\377\377\377\377\377\377\377\377\222\224\357{\020\204\020"
  "\204\020\204\020\204\020\204\020\204\020\204\020\204\020\204\020\204\020\204Q\214"
  "\014c\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000a\010\377\377\377\377\377\377\377"
  "\377\377\377\313Z\373\336\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\357{\327\275\377\377\377\377\377\377\377\377\367\275\000\000"
  "\202\020\377\377\377\377\377\377\377\377\377\377e)\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000IJ\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000\000\000\000\000\000}\357"
  "\377\377\377\377\377\377\377\377\347\071\000\000\000\000Mk\377\377\377\377\377\377"
  "\377\377Y\316\000\000\000\000\000\000\000\000\252R\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377Mk\000\000\000\000\313Z\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377Y\316\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000a\010\377\377\377\377\377\377\377\377\377\377$!\000\000\266"
  "\265\377\377\377\377\377\377\377\377\377\377\377\377\212R\000\000\367\275\377"
  "\377\377\377\377\377\377\377\367\275\000\000\202\020\377\377\377\377\377\377\377"
  "\377\377\377e)\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000IJ\377\377\377\377\377\377"
  "\377\377\377\377\000\000\000\000\000\000\000\000\000\000Mk\377\377\377\377\377\377\377\377Y\316"
  "\000\000\000\000}\357\377\377\377\377\377\377\377\377\343\030\000\000\000\000\000\000\000\000\252"
  "R\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  ",c\000\000\000\000\313Z\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\367\275\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000a\010\377"
  "\377\377\377\377\377\377\377\377\377e)\000\000\000\000Mk\377\377\377\377\377\377"
  "Y\316\000\000\000\000\000\000\367\275\377\377\377\377\377\377\377\377\367\275\000\000\202"
  "\020\377\377\377\377\377\377\377\377\377\377e)\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000IJ\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000\377"
  "\377\377\377\377\377\377\377\377\377\000\000\347\071\377\377\377\377\377\377\377"
  "\377Y\316\000\000\000\000\000\000\000\000\000\000\252R\377\377\377\377\377\377\377\377\377\377"
  "\276\367\276\367\337\377\337\377\337\377\337\377\337\377\337\377\337\377"
  "\337\377\337\377\337\377\377\377\014c\000\000\000\000\313Z\377\377\337\377\337\377"
  "\337\377\337\377\337\377\337\377\337\377\337\377\337\377\337\377\337\377"
  "\337\377\276\367\377\377\377\377\377\377\377\377\377\377\367\275\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000a\010\377\377\377\377\377\377\377\377\377\377"
  "e)\000\000\000\000\000\000e)}\357\020\204\000\000\000\000\000\000\000\000\367\275\377\377\377\377\377"
  "\377\377\377\367\275\000\000\202\020\377\377\377\377\377\377\377\377\377\377e"
  ")\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000IJ\377\377\377\377\377\377\377\377\377\377"
  "\000\000\000\000\000\000\000\000\000\000\000\000q\214\377\377\377\377\377\377\377\377,c\226\265\377"
  "\377\377\377\377\377\377\377\010B\000\000\000\000\000\000\000\000\000\000\252R\377\377\377\377"
  "\377\377\377\377\377\377A\010A\010a\010a\010a\010a\010a\010a\010a\010a\010a\010a\010"
  "a\010\040\000\000\000\000\000\040\000a\010a\010a\010a\010a\010a\010a\010a\010a\010a\010a\010a\010a\010"
  "\000\000y\316\377\377\377\377\377\377\377\377\367\275\000\000\000\000\000\000E)E)e)$!\000\000"
  "\000\000a\010\377\377\377\377\377\377\377\377\377\377e)\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\367\275\377\377\377\377\377\377\377\377\367\275\000\000\202"
  "\020\377\377\377\377\377\377\377\377\377\377\010B\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000IJ\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000"
  "a\010\377\377\377\377\377\377\377\377\337\377\337\377\377\377\377\377\377"
  "\377}\357\000\000\000\000\000\000\000\000\000\000\000\000\252R\377\377\377\377\377\377\377\377\377"
  "\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000Y\316\377\377\377"
  "\377\377\377\377\377\367\275\000\000\000\000\000\000\377\377\377\377\377\377<\347\000\000"
  "\000\000a\010\377\377\377\377\377\377\377\377\377\377e)\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\367\275\377\377\377\377\377\377\377\377\367\275\000\000\242"
  "\020\377\377\377\377\377\377\377\377\377\377\337\377\040\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000IJ\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\323\234\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\014c\000\000\000\000\000\000\000\000\000\000\000\000\252R\377\377\377\377\377\377\377\377"
  "\377\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000Y\316\377\377"
  "\377\377\377\377\377\377\367\275\000\000\000\000\000\000\377\377\377\377\377\377\034\347"
  "\000\000\000\000a\010\377\377\377\377\377\377\377\377\377\377e)\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\367\275\377\377\377\377\377\377\377\377\367\275\000"
  "\000\000\000\373\336\377\377\377\377\377\377\377\377\377\377\333\336\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000IJ\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\242\020\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\252R\377\377\377\377\377\377\377"
  "\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\070\306\377"
  "\377\377\377\377\377\377\377\367\275\000\000\000\000\000\000\377\377\377\377\377\377"
  "\034\347\000\000\000\000a\010\377\377\377\377\377\377\377\377\377\377e)\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\367\275\377\377\377\377\377\377\377\377\367"
  "\275\000\000\000\000a\010\377\377\377\377\377\377\377\377\377\377\377\377\317{\000\000"
  "\000\000\000\000\000\000\000\000\000\000\307\071\377\377\377\377\377\377\377\377\377\377\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\030\306\377\377\377\377\377\377\377\377\377\377"
  "\377\377\020\204\000\000\000\000\000\000\000\000\000\000\000\000\000\000\252R\377\377\377\377\377\377"
  "\377\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000A\010\377"
  "\377\377\377\377\377\377\377\377\377\030\306\000\000\000\000\000\000\377\377\377\377\377"
  "\377\276\367\000\000\000\000a\010\377\377\377\377\377\377\377\377\377\377e)\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\367\275\377\377\377\377\377\377\377\377"
  "\367\275\000\000\000\000\000\000\246\061\377\377\377\377\377\377\377\377\377\377\377\377"
  "\367\275\327\275\327\275\327\275\327\275\327\275Y\316\377\377\377\377\377"
  "\377\377\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\206\061\377\377\377\377"
  "\377\377\377\377\377\377\377\377a\010\000\000\000\000\000\000\000\000\000\000\000\000\000\000\252R\377"
  "\377\377\377\377\377\377\377\377\377\313Z\313Z\353Z\353Z\353Z\353Z\353Z\353"
  "Z\353Z\353Z\353Z\014cE)\000\000\000\000\000\000,c\353Z\353Z\353Z\353Z\353Z\353Z\353Z\353"
  "Z\353Z\353Z\353Z\353Z\212R\333\336\377\377\377\377\377\377\377\377\377\377"
  "\327\275\000\000\000\000\000\000\040\000\040\000\040\000\040\000\000\000\000\000a\010\377\377\377\377\377"
  "\377\377\377\377\377e)\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\367\275\377"
  "\377\377\377\377\377\377\377\367\275\000\000\000\000\000\000\000\000Q\214\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\272\326\377\377\377\377\377\377\377\377\222\224\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\252R\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377a\010\000\000\000\000,c\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\040\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000a\010\377\377\377\377\377\377\377\377\377\377\206\061\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000Y\316\377\377\377\377\377\377\377\377Y\316"
  "\000\000\000\000\000\000\000\000\000\000\373\336\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\252R\377\377\377\377\377"
  "\377\377\377A\010\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\252R\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377Y\316\000\000\000\000\000\000\226"
  "\265\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377e)\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\040\000\363\234q\214q\214q\214\323\234"
  "\303\030\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000Mk\262\224q\214q\214\262\224"
  "Mk\000\000\000\000\000\000\000\000\000\000a\010\323\234q\214q\214q\214q\214q\214q\214q\214q\214"
  "q\214q\214q\214q\214q\214q\214\363\234\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000q\214\222\224\222\224\317{\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000iJ\276"
  "\367<\347<\347<\347<\347<\347<\347<\347<\347<\347<\347<\347<\347<\347<\347"
  "<\347<\347<\347\377\377IJ\000\000\000\000\000\000\232\326]\357<\347<\347<\347<\347<\347"
  "<\347<\347<\347<\347<\347<\347<\347<\347}\357\363\234\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
};

