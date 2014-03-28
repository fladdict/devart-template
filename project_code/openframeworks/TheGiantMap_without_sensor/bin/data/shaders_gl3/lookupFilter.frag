#version 150

//Original Image to Render
uniform sampler2DRect sourceTexture;

//512x512 6bit LookupTable.
uniform sampler2DRect lookupTexture;
uniform float interpolation;

in vec2 texCoordVarying;
out vec4 outputColor;

void main()
{
    vec4 originalCol = texture(sourceTexture, texCoordVarying);
    float blue = floor(originalCol.b * 63.0);
    float b2 = floor(blue / 8);
    vec4 lookupCol = texture(lookupTexture, vec2(originalCol.r*63.0 + 64.0 * (blue-b2*8.0), originalCol.g*63.0 + 64.0 * b2));
    outputColor = vec4(originalCol.rgb * (1-interpolation) + lookupCol.rgb * interpolation,1);
}