#include "color_helpers.h" 
#include <math.h>



char *gdkrgba_to_hex(const GdkRGBA *const rgba) {
    guchar red = roundf(rgba->red * 255.0f);
    guchar green = roundf(rgba->green * 255.0f);
    guchar blue = roundf(rgba->blue * 255.0f);

    char *to = malloc(RGB_HEX_STRING_LENGTH);
    if (!to) {
      perror("malloc failed at gdkrgba_to_hex.\n");
      return NULL; 
    }

    snprintf(to, RGB_HEX_STRING_LENGTH, "#%02hhx%02hhx%02hhx", red, green, blue);

    return to;
}



GdkRGBA *hex_to_gdkrgba(const char *hex_color) {
    if (!hex_color) return NULL;

    if (hex_color[0] == '#') hex_color++;

    size_t len = strlen(hex_color);
    if (len != 6 && len != 8) { // RRGGBB or RRGGBBAA
        perror("Invalid hex color length");
        return NULL;
    }

    uint32_t r, g, b, a = 255;
    if (len == 6) {
        if (sscanf(hex_color, "%02x%02x%02x", &r, &g, &b) != 3) return NULL;
    } else {
        if (sscanf(hex_color, "%02x%02x%02x%02x", &r, &g, &b, &a) != 4) return NULL;
    }

    GdkRGBA *color = malloc(sizeof(GdkRGBA));
    if (!color) return NULL;

    color->red   = r / 255.0;
    color->green = g / 255.0;
    color->blue  = b / 255.0;
    color->alpha = a / 255.0;

    return color;
}


