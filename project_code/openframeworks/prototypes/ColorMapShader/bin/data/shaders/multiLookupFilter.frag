#version 120

//Original Image to Render
uniform sampler2DRect sourceTexture;

//512x512 6bit LookupTable.
uniform sampler2DRect lookupTexture0;
uniform sampler2DRect lookupTexture1;
uniform float interpolation;

in vec2 texCoordVarying;
out vec4 outputColor;

void main()
{
    vec4 originalCol = texture(sourceTexture, texCoordVarying);
    float red = originalCol.r * 63.0;
    float green = originalCol.g * 63.0;
    float blue = floor(originalCol.b * 63.0);
    float b2 = floor(blue / 8);

    vec2 lookupPos;
    lookupPos.x = red + 64 * (blue-b2*8);
    lookupPos.y = green + 64 * b2;
    vec4 lookupCol0 = texture(lookupTexture0, lookupPos);
    vec4 lookupCol1 = texture(lookupTexture1, lookupPos);
    
    outputColor = lookupCol0 * (1-interpolation) + lookupCol1 * interpolation;
}