/*******************************************************************************
 * Size: 24 px
 * Bpp: 4
 * Opts: --bpp 4 --size 24 --no-compress --stride 1 --align 1 --font NotoSans-Medium.ttf --range 1040 --format lvgl -o noto_24.c
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef NOTO_24
#define NOTO_24 1
#endif

#if NOTO_24

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0410 "А" */
    0x0, 0x0, 0x0, 0xbf, 0xf6, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x1, 0xff, 0xfc, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x7, 0xfe, 0xff, 0x20, 0x0, 0x0,
    0x0, 0x0, 0xd, 0xf8, 0xdf, 0x80, 0x0, 0x0,
    0x0, 0x0, 0x3f, 0xf3, 0x8f, 0xe0, 0x0, 0x0,
    0x0, 0x0, 0x9f, 0xe0, 0x3f, 0xf4, 0x0, 0x0,
    0x0, 0x0, 0xff, 0x90, 0xd, 0xfa, 0x0, 0x0,
    0x0, 0x5, 0xff, 0x30, 0x8, 0xff, 0x10, 0x0,
    0x0, 0xc, 0xfd, 0x0, 0x2, 0xff, 0x70, 0x0,
    0x0, 0x2f, 0xf7, 0x0, 0x0, 0xcf, 0xd0, 0x0,
    0x0, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x0,
    0x0, 0xef, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x0,
    0x4, 0xff, 0x83, 0x33, 0x33, 0x3c, 0xff, 0x0,
    0xa, 0xff, 0x10, 0x0, 0x0, 0x6, 0xff, 0x50,
    0x1f, 0xfa, 0x0, 0x0, 0x0, 0x0, 0xff, 0xb0,
    0x6f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0xaf, 0xf2,
    0xcf, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xf8
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 251, .box_w = 16, .box_h = 17, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 1040, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};

extern const lv_font_t lv_font_noto_24;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t noto_24 = {
#else
lv_font_t noto_24 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .static_bitmap = 0,
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &lv_font_noto_24,
#endif
    .user_data = NULL,
};



#endif /*#if NOTO_24*/
