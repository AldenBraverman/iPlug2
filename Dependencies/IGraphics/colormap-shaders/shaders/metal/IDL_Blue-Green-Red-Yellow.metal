#include <metal_stdlib>
using namespace metal;

namespace colormap {
namespace IDL {
namespace Blue_Green_Red_Yellow {

float colormap_red(float x) {
    if (x < (8.40958823529412E+02 - 5.2E+02) / (7.50588235294118 - 5.0)) {
        return 7.50588235294118 * x - 8.40958823529412E+02;
    } else if (x < (5.2E+02 + 1.27747747747748E+02) / (5.0 - 5.0e-1)) {
        return 5.0 * x - 5.2E+02;
    } else {
        return 5.0e-1 * x + 1.27747747747748E+02;
    }
}

float colormap_green(float x) {
    if (x < (150.0 + 1.00373100303951E+02) / 3.12386018237082) { // 80.1486256385
        return 3.12386018237082 * x - 1.00373100303951E+02;
    } else if (x < (2.08794117647059E+02 - 150.0) / 6.17647058823529E-01) { // 95.1904761905
        return 150.0;
    } else if (x < (4.19041176470588E+02 - 2.08794117647059E+02) / (-6.17647058823529E-01 + 2.49411764705882E+00)) { // 112.043887147
        return -6.17647058823529E-01 * x + 2.08794117647059E+02;
    } else if (x < (8.97617647058824E+02 - 4.19041176470588E+02) / (-2.49411764705882E+00 - -6.23529411764706E+00)) { // 127.921383648
        return -2.49411764705882E+00 * x + 4.19041176470588E+02;
    } else if (x < (8.97617647058824E+02 - - 3.32600912600913E+02) / (2.30624780624781E+00 - -6.23529411764706E+00)) { // 144.027690857
        return -6.23529411764706E+00 * x + 8.97617647058824E+02;
    } else {
        return 2.30624780624781E+00 * x - 3.32600912600913E+02;
    }
}

float colormap_blue(float x) {
    if (x < (100.0 - - 3.36734693877551E-01) / 2.07815892314373E+00) {
        return 2.07815892314373E+00 * x - 3.36734693877551E-01;
    } else if (x < (3.49317448680352E+02 - 100.0) / 3.12243401759531E+00) {
        return 100.0;
    } else {
        return -3.12243401759531E+00 * x + 3.49317448680352E+02;
    }
}

float4 colormap(float x) {
    float t = x * 255.0;
    float r = clamp(colormap_red(t) / 255.0, 0.0, 1.0);
    float g = clamp(colormap_green(t) / 255.0, 0.0, 1.0);
    float b = clamp(colormap_blue(t) / 255.0, 0.0, 1.0);
    return float4(r, g, b, 1.0);
}

} // namespace Blue_Green_Red_Yellow
} // namespace IDL
} // namespace colormap
