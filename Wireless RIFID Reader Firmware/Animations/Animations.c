/*
 * File:   Animations.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include <plib.h>
#include "NeoPixels/NeoPixels.h"
//#include "SystemClock.h"

//------------------------------------------------------------------------------
// Definitions

#define MAX_NUMBER_OF_PIXELS 256

typedef struct {
    float red;
    float green;
    float blue;
} PIXEL;

typedef struct {
    PIXEL pixels[MAX_NUMBER_OF_PIXELS];
    unsigned int numberOfPixels;
} PIXEL_STRIP;

//------------------------------------------------------------------------------
// Function declarations

PIXEL PixelAdd(PIXEL pixelA, PIXEL pixelB) {
    PIXEL pixelResult;
    pixelResult.red = pixelA.red + pixelB.red;
    pixelResult.green = pixelA.green + pixelB.green;
    pixelResult.blue = pixelA.blue + pixelB.blue;
    return pixelResult;
}

PIXEL PixelMultiply(PIXEL pixelA, PIXEL pixelB) {
    PIXEL pixelResult;
    pixelResult.red = pixelA.red * pixelB.red;
    pixelResult.green = pixelA.green * pixelB.green;
    pixelResult.blue = pixelA.blue * pixelB.blue;
    return pixelResult;
}

PIXEL PixelMultiplyScalar(PIXEL pixel, float scalar) {
    PIXEL pixelResult;
    pixelResult.red = pixel.red * scalar;
    pixelResult.green = pixel.green * scalar;
    pixelResult.blue = pixel.blue * scalar;
    return pixelResult;
}

NEOPIXEL PixelToNeoPixel(PIXEL pixel) {
    NEOPIXEL neoPixel;
    pixel.red = (pixel.red < 0.0f) ? 0.0f : (pixel.red > 1.0f) ? 1.0f : pixel.red;
    pixel.green = (pixel.green < 0.0f) ? 0.0f : (pixel.green > 1.0f) ? 1.0f : pixel.green;
    pixel.blue = (pixel.blue < 0.0f) ? 0.0f : (pixel.blue > 1.0f) ? 1.0f : pixel.blue;
    neoPixel.red = (unsigned char) (255.0f * pixel.red);
    neoPixel.green = (unsigned char) (255.0f * pixel.green);
    neoPixel.blue = (unsigned char) (255.0f * pixel.blue);
    return neoPixel;
}

int PixelStripInitialise(PIXEL_STRIP * const pixelStrip, const unsigned int numberOfPixels) {
    if (numberOfPixels > MAX_NUMBER_OF_PIXELS) {
        return 0; // error: number of pixels too large
    }
    pixelStrip->numberOfPixels = numberOfPixels;
}

void PixelStripClear(PIXEL_STRIP * const pixelStrip) {
    unsigned int i;
    for (i = 0; i < pixelStrip->numberOfPixels; i++) {
        pixelStrip->pixels[i].red = 0;
        pixelStrip->pixels[i].green = 0;
        pixelStrip->pixels[i].blue = 0;
    }
}

void PixelStripMultiplyScalar(PIXEL_STRIP * const pixelStrip, const float scalar) {
    unsigned int i;
    for (i = 0; i < pixelStrip->numberOfPixels; i++) {
        pixelStrip->pixels[i].red *= scalar;
        pixelStrip->pixels[i].green *= scalar;
        pixelStrip->pixels[i].blue *= scalar;
    }
}

void PixelStripMultiplyPixel(PIXEL_STRIP * const pixelStrip, const PIXEL pixel) {
    unsigned int i;
    for (i = 0; i < pixelStrip->numberOfPixels; i++) {
        pixelStrip->pixels[i].red *= pixel.red;
        pixelStrip->pixels[i].green *= pixel.green;
        pixelStrip->pixels[i].blue *= pixel.blue;
    }
}

unsigned int PixelStripToNeoPixelArray(PIXEL_STRIP * const pixelStrip, NEOPIXEL * const destination, const unsigned int destinationLength) {
    if (pixelStrip->numberOfPixels > destinationLength) {
        return 0; // error: destination too small
    }
    unsigned int i;
    for (i = 0; i < pixelStrip->numberOfPixels; i++) {
        destination[i] = PixelToNeoPixel(pixelStrip->pixels[i]);
    }
}

#define ANIMATION_SPEED 2.0f // scenes per second
#define FADE_AMOUNT 0.9f
#define FADE_AMOUNT_2 0.95f
#define FRAME_PERIOD 0.01f // seconds (1 / frame rate)

const PIXEL fadeColour = {227.0f / 255.0f, 193.0f / 255.0f, 255.0f / 255.0f}; // chosen by phil because it look good

static PIXEL_STRIP pixelStrip;

const PIXEL uvColourPalette[] = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.003921569f},
    {0.0f, 0.0f, 0.007843138f},
    {0.0f, 0.0f, 0.01176471f},
    {0.003921569f, 0.0f, 0.01568628f},
    {0.003921569f, 0.0f, 0.02352941f},
    {0.007843138f, 0.0f, 0.03529412f},
    {0.01176471f, 0.0f, 0.04313726f},
    {0.01568628f, 0.0f, 0.05490196f},
    {0.01960784f, 0.0f, 0.06666667f},
    {0.02352941f, 0.0f, 0.08235294f},
    {0.02745098f, 0.0f, 0.09803922f},
    {0.03137255f, 0.0f, 0.1137255f},
    {0.03529412f, 0.0f, 0.1333333f},
    {0.04313726f, 0.0f, 0.1529412f},
    {0.04705883f, 0.0f, 0.172549f},
    {0.05490196f, 0.0f, 0.1921569f},
    {0.0627451f, 0.0f, 0.2156863f},
    {0.06666667f, 0.0f, 0.2352941f},
    {0.07450981f, 0.0f, 0.254902f},
    {0.07843138f, 0.003921569f, 0.2705882f},
    {0.08627451f, 0.003921569f, 0.2862745f},
    {0.09019608f, 0.003921569f, 0.3019608f},
    {0.09411766f, 0.003921569f, 0.3176471f},
    {0.09803922f, 0.003921569f, 0.3294118f},
    {0.1058824f, 0.003921569f, 0.3411765f},
    {0.1098039f, 0.003921569f, 0.3490196f},
    {0.1098039f, 0.003921569f, 0.3607843f},
    {0.1137255f, 0.003921569f, 0.3686275f},
    {0.1176471f, 0.003921569f, 0.3764706f},
    {0.1215686f, 0.003921569f, 0.3803922f},
    {0.1215686f, 0.003921569f, 0.3843138f},
    {0.1254902f, 0.003921569f, 0.3882353f},
    {0.1254902f, 0.003921569f, 0.3882353f},
    {0.1294118f, 0.003921569f, 0.3921569f},
    {0.1294118f, 0.007843138f, 0.3921569f},
    {0.1294118f, 0.007843138f, 0.3960785f},
    {0.1333333f, 0.007843138f, 0.3960785f},
    {0.1333333f, 0.007843138f, 0.3960785f},
    {0.1333333f, 0.007843138f, 0.4f},
    {0.1333333f, 0.007843138f, 0.4f},
    {0.1372549f, 0.007843138f, 0.4039216f},
    {0.1372549f, 0.007843138f, 0.4039216f},
    {0.1372549f, 0.007843138f, 0.4078432f},
    {0.1372549f, 0.007843138f, 0.4078432f},
    {0.1411765f, 0.007843138f, 0.4078432f},
    {0.1411765f, 0.007843138f, 0.4117647f},
    {0.1411765f, 0.007843138f, 0.4117647f},
    {0.1411765f, 0.007843138f, 0.4156863f},
    {0.145098f, 0.007843138f, 0.4156863f},
    {0.145098f, 0.003921569f, 0.4196079f},
    {0.145098f, 0.003921569f, 0.4196079f},
    {0.1490196f, 0.003921569f, 0.4235294f},
    {0.1490196f, 0.003921569f, 0.4235294f},
    {0.1490196f, 0.003921569f, 0.427451f},
    {0.1529412f, 0.003921569f, 0.427451f},
    {0.1529412f, 0.003921569f, 0.4313726f},
    {0.1529412f, 0.003921569f, 0.4313726f},
    {0.1568628f, 0.003921569f, 0.4352942f},
    {0.1568628f, 0.003921569f, 0.4392157f},
    {0.1568628f, 0.003921569f, 0.4392157f},
    {0.1607843f, 0.003921569f, 0.4431373f},
    {0.1607843f, 0.003921569f, 0.4431373f},
    {0.1607843f, 0.003921569f, 0.4470589f},
    {0.1647059f, 0.003921569f, 0.4470589f},
    {0.1647059f, 0.003921569f, 0.4509804f},
    {0.1686275f, 0.003921569f, 0.454902f},
    {0.1686275f, 0.003921569f, 0.454902f},
    {0.1686275f, 0.003921569f, 0.4588236f},
    {0.1686275f, 0.003921569f, 0.4588236f},
    {0.172549f, 0.003921569f, 0.4627451f},
    {0.172549f, 0.003921569f, 0.4627451f},
    {0.172549f, 0.007843138f, 0.4666667f},
    {0.1764706f, 0.007843138f, 0.4705883f},
    {0.1764706f, 0.007843138f, 0.4705883f},
    {0.1764706f, 0.007843138f, 0.4745098f},
    {0.1764706f, 0.007843138f, 0.4745098f},
    {0.1764706f, 0.007843138f, 0.4784314f},
    {0.1803922f, 0.007843138f, 0.482353f},
    {0.1803922f, 0.007843138f, 0.482353f},
    {0.1803922f, 0.007843138f, 0.4862745f},
    {0.1803922f, 0.007843138f, 0.4862745f},
    {0.1843137f, 0.003921569f, 0.4901961f},
    {0.1843137f, 0.003921569f, 0.4941177f},
    {0.1843137f, 0.003921569f, 0.4941177f},
    {0.1882353f, 0.003921569f, 0.4980392f},
    {0.1882353f, 0.003921569f, 0.4980392f},
    {0.1882353f, 0.003921569f, 0.5019608f},
    {0.1921569f, 0.003921569f, 0.5058824f},
    {0.1921569f, 0.003921569f, 0.5058824f},
    {0.1921569f, 0.003921569f, 0.509804f},
    {0.1960784f, 0.003921569f, 0.5137255f},
    {0.1960784f, 0.003921569f, 0.5137255f},
    {0.1960784f, 0.003921569f, 0.5176471f},
    {0.2f, 0.003921569f, 0.5215687f},
    {0.2f, 0.003921569f, 0.5215687f},
    {0.2f, 0.003921569f, 0.5254902f},
    {0.2039216f, 0.0f, 0.5294118f},
    {0.2039216f, 0.0f, 0.5294118f},
    {0.2039216f, 0.0f, 0.5333334f},
    {0.2078432f, 0.0f, 0.5372549f},
    {0.2078432f, 0.0f, 0.5372549f},
    {0.2078432f, 0.0f, 0.5411765f},
    {0.2078432f, 0.0f, 0.5450981f},
    {0.2117647f, 0.0f, 0.5490196f},
    {0.2117647f, 0.0f, 0.5490196f},
    {0.2117647f, 0.0f, 0.5529412f},
    {0.2156863f, 0.0f, 0.5568628f},
    {0.2156863f, 0.0f, 0.5607843f},
    {0.2156863f, 0.0f, 0.5647059f},
    {0.2196079f, 0.0f, 0.5686275f},
    {0.2196079f, 0.0f, 0.572549f},
    {0.2196079f, 0.0f, 0.5764706f},
    {0.2235294f, 0.0f, 0.5803922f},
    {0.2235294f, 0.0f, 0.5843138f},
    {0.2235294f, 0.0f, 0.5843138f},
    {0.227451f, 0.0f, 0.5882353f},
    {0.227451f, 0.0f, 0.5921569f},
    {0.227451f, 0.0f, 0.5960785f},
    {0.2313726f, 0.0f, 0.6f},
    {0.2313726f, 0.0f, 0.6039216f},
    {0.2352941f, 0.0f, 0.6078432f},
    {0.2352941f, 0.0f, 0.6117647f},
    {0.2392157f, 0.0f, 0.6156863f},
    {0.2392157f, 0.0f, 0.6196079f},
    {0.2392157f, 0.0f, 0.627451f},
    {0.2431373f, 0.0f, 0.6313726f},
    {0.2431373f, 0.0f, 0.6352941f},
    {0.2470588f, 0.003921569f, 0.6392157f},
    {0.2470588f, 0.003921569f, 0.6431373f},
    {0.2509804f, 0.003921569f, 0.6470588f},
    {0.2509804f, 0.003921569f, 0.6509804f},
    {0.254902f, 0.003921569f, 0.654902f},
    {0.2588235f, 0.003921569f, 0.6588235f},
    {0.2588235f, 0.003921569f, 0.6627451f},
    {0.2627451f, 0.003921569f, 0.6666667f},
    {0.2627451f, 0.003921569f, 0.6705883f},
    {0.2666667f, 0.003921569f, 0.6745098f},
    {0.2666667f, 0.003921569f, 0.682353f},
    {0.2705882f, 0.003921569f, 0.6862745f},
    {0.2705882f, 0.003921569f, 0.6901961f},
    {0.2745098f, 0.003921569f, 0.6941177f},
    {0.2784314f, 0.003921569f, 0.6980392f},
    {0.2784314f, 0.003921569f, 0.7019608f},
    {0.282353f, 0.003921569f, 0.7058824f},
    {0.282353f, 0.003921569f, 0.7098039f},
    {0.2862745f, 0.003921569f, 0.7137255f},
    {0.2901961f, 0.003921569f, 0.7176471f},
    {0.2901961f, 0.003921569f, 0.7215686f},
    {0.2941177f, 0.003921569f, 0.7254902f},
    {0.2980392f, 0.003921569f, 0.7294118f},
    {0.2980392f, 0.003921569f, 0.7333333f},
    {0.3019608f, 0.003921569f, 0.7372549f},
    {0.3019608f, 0.003921569f, 0.7411765f},
    {0.3058824f, 0.003921569f, 0.7411765f},
    {0.3098039f, 0.003921569f, 0.7450981f},
    {0.3098039f, 0.003921569f, 0.7490196f},
    {0.3137255f, 0.003921569f, 0.7490196f},
    {0.3137255f, 0.003921569f, 0.7529413f},
    {0.3176471f, 0.007843138f, 0.7568628f},
    {0.3176471f, 0.007843138f, 0.7568628f},
    {0.3215686f, 0.007843138f, 0.7607844f},
    {0.3215686f, 0.007843138f, 0.7607844f},
    {0.3254902f, 0.007843138f, 0.764706f},
    {0.3294118f, 0.01176471f, 0.764706f},
    {0.3294118f, 0.01176471f, 0.7686275f},
    {0.3333333f, 0.01176471f, 0.7686275f},
    {0.3333333f, 0.01176471f, 0.7686275f},
    {0.3372549f, 0.01176471f, 0.7725491f},
    {0.3372549f, 0.01568628f, 0.7725491f},
    {0.3411765f, 0.01568628f, 0.7764707f},
    {0.345098f, 0.01568628f, 0.7764707f},
    {0.345098f, 0.01960784f, 0.7803922f},
    {0.3490196f, 0.01960784f, 0.7803922f},
    {0.3529412f, 0.01960784f, 0.7803922f},
    {0.3568628f, 0.02352941f, 0.7843138f},
    {0.3607843f, 0.02352941f, 0.7843138f},
    {0.3607843f, 0.02352941f, 0.7882354f},
    {0.3647059f, 0.02745098f, 0.7882354f},
    {0.3686275f, 0.02745098f, 0.7921569f},
    {0.372549f, 0.02745098f, 0.7921569f},
    {0.3764706f, 0.03137255f, 0.7921569f},
    {0.3803922f, 0.03137255f, 0.7960785f},
    {0.3843138f, 0.03529412f, 0.7960785f},
    {0.3882353f, 0.03529412f, 0.7960785f},
    {0.3921569f, 0.03529412f, 0.8000001f},
    {0.3960785f, 0.03921569f, 0.8000001f},
    {0.4f, 0.03921569f, 0.8000001f},
    {0.4039216f, 0.04313726f, 0.8039216f},
    {0.4078432f, 0.04313726f, 0.8039216f},
    {0.4156863f, 0.04313726f, 0.8039216f},
    {0.4196079f, 0.04705883f, 0.8078432f},
    {0.4235294f, 0.04705883f, 0.8078432f},
    {0.427451f, 0.0509804f, 0.8078432f},
    {0.4313726f, 0.0509804f, 0.8078432f},
    {0.4392157f, 0.05490196f, 0.8117648f},
    {0.4431373f, 0.05490196f, 0.8117648f},
    {0.4470589f, 0.05490196f, 0.8117648f},
    {0.454902f, 0.05882353f, 0.8117648f},
    {0.4588236f, 0.05882353f, 0.8156863f},
    {0.4627451f, 0.05882353f, 0.8156863f},
    {0.4705883f, 0.05882353f, 0.8156863f},
    {0.4745098f, 0.0627451f, 0.8156863f},
    {0.482353f, 0.0627451f, 0.8156863f},
    {0.4862745f, 0.0627451f, 0.8196079f},
    {0.4941177f, 0.06666667f, 0.8196079f},
    {0.4980392f, 0.06666667f, 0.8196079f},
    {0.5058824f, 0.06666667f, 0.8196079f},
    {0.5137255f, 0.06666667f, 0.8196079f},
    {0.5176471f, 0.06666667f, 0.8196079f},
    {0.5254902f, 0.07058824f, 0.8196079f},
    {0.5333334f, 0.07058824f, 0.8235295f},
    {0.5372549f, 0.07450981f, 0.8235295f},
    {0.5450981f, 0.07843138f, 0.8235295f},
    {0.5529412f, 0.08235294f, 0.8235295f},
    {0.5607843f, 0.09019608f, 0.8235295f},
    {0.5686275f, 0.09803922f, 0.8274511f},
    {0.5764706f, 0.1058824f, 0.8274511f},
    {0.5843138f, 0.1137255f, 0.8313726f},
    {0.5960785f, 0.1254902f, 0.8313726f},
    {0.6039216f, 0.1411765f, 0.8352942f},
    {0.6156863f, 0.1529412f, 0.8352942f},
    {0.6235294f, 0.172549f, 0.8392158f},
    {0.6352941f, 0.1921569f, 0.8431373f},
    {0.6470588f, 0.2156863f, 0.8470589f},
    {0.6588235f, 0.2392157f, 0.8509805f},
    {0.6745098f, 0.2705882f, 0.8588236f},
    {0.6901961f, 0.2980392f, 0.8627452f},
    {0.7019608f, 0.3333333f, 0.8705883f},
    {0.7176471f, 0.3647059f, 0.8745099f},
    {0.7333333f, 0.4f, 0.882353f},
    {0.7490196f, 0.4352942f, 0.8862746f},
    {0.764706f, 0.4705883f, 0.8941177f},
    {0.7803922f, 0.5019608f, 0.9019608f},
    {0.7960785f, 0.5372549f, 0.9058824f},
    {0.8078432f, 0.5686275f, 0.909804f},
    {0.8235295f, 0.6f, 0.9176471f},
    {0.8352942f, 0.6352941f, 0.9215687f},
    {0.8509805f, 0.6666667f, 0.9294118f},
    {0.8666667f, 0.6980392f, 0.9333334f},
    {0.8784314f, 0.7254902f, 0.9411765f},
    {0.8901961f, 0.7529413f, 0.9450981f},
    {0.9019608f, 0.7803922f, 0.9490197f},
    {0.909804f, 0.8000001f, 0.9529412f},
    {0.9176471f, 0.8235295f, 0.9568628f},
    {0.9294118f, 0.8431373f, 0.9607844f},
    {0.937255f, 0.8588236f, 0.9647059f}
};

#include "DeviceID/DeviceID.h"

void AnimiationInitialise() {
    switch (DeviceIDGetID()) {
        case HANDSHAKE:
            PixelStripInitialise(&pixelStrip, 27);
        case HIGH_FIVE:
            PixelStripInitialise(&pixelStrip, 25); // number of pixels on wrist bands
            break;
        case HUG:
            PixelStripInitialise(&pixelStrip, 16); // number of pixels badge
            break;
        case TAP: // pixels not used
        default:
            PixelStripInitialise(&pixelStrip, 16);
            break;
    }
}

#include <math.h>
#include "SystemClock.h"

//#define DEBUG_PIN_HIGH()    mPORTDSetBits(BIT_0)
//#define DEBUG_PIN_LOW()     mPORTDClearBits(BIT_0)

static int scene; // FSM state
static float sceneProgress; // 0.0 = start of scene, 1.0 = end of scene

// animation scenes:
// 1 = loop
// 2 = loop
// 3 = pulse (ends with white flash)
// 4 = fade down

void AnimationsPlay() {
    scene = 0;
    sceneProgress = 0.0f;
}

void AnimationsDoTasks() {
    if (scene > 5) {
        return;
    }

    // Update at frame rate
    UINT32 t = ReadCoreTimer();
    static UINT32 tPrevious;
    if ((t - tPrevious) > (PBCLK / 200)) { // bug!!!!!!!!!
        tPrevious = t;

        //        DEBUG_PIN_HIGH();

        // Update scene progress and scene
        sceneProgress += FRAME_PERIOD * ANIMATION_SPEED;
        if (sceneProgress >= 1.0f) {
            scene = (scene + 1);
        }
        sceneProgress = fmod(sceneProgress, 1.0f);

        // Scene-scpecific behaviour
        if (scene < 2) {
            PixelStripMultiplyPixel(&pixelStrip, PixelMultiplyScalar(fadeColour, FADE_AMOUNT));

            float xPos = sceneProgress * (float) pixelStrip.numberOfPixels;

            PIXEL localColour = uvColourPalette[255]; // choose brightest colour in paltte (will be faded by fadeColour)

            // lower/upper pixel index either side of
            int lower = (int) xPos;
            int upper = ((int) xPos + 1) % pixelStrip.numberOfPixels; // mod to overflow

            float propInUpper = xPos - lower; // proportion in upper physical pixel

            pixelStrip.pixels[lower] = PixelAdd(pixelStrip.pixels[lower], PixelMultiplyScalar(localColour, (1.0f - propInUpper)));
            pixelStrip.pixels[upper] = PixelAdd(pixelStrip.pixels[upper], PixelMultiplyScalar(localColour, propInUpper));

        } else if (scene == 2) {
            PixelStripMultiplyPixel(&pixelStrip, PixelMultiplyScalar(fadeColour, FADE_AMOUNT));

            PIXEL localColour = uvColourPalette[(int) (pow(sceneProgress, 7) * 255.0f)];

            int y;
            for (y = 0; y < pixelStrip.numberOfPixels; y++) {
                pixelStrip.pixels[y] = PixelAdd(pixelStrip.pixels[y], localColour);
            }
        } else {
            PixelStripMultiplyPixel(&pixelStrip, PixelMultiplyScalar(fadeColour, FADE_AMOUNT_2));
        }

        NEOPIXEL neoPixels[MAX_NUMBER_OF_PIXELS];
        PixelStripToNeoPixelArray(&pixelStrip, neoPixels, pixelStrip.numberOfPixels);
        NeoPixelsWrite(neoPixels, pixelStrip.numberOfPixels);

        //        DEBUG_PIN_LOW();
    }
}

//------------------------------------------------------------------------------
// End of file
