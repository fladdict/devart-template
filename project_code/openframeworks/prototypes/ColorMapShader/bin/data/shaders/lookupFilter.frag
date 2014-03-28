#version 120


//uniform sampler2DRect texture0;
uniform sampler2DRect sourceTexture;    //Original Image to Render
uniform sampler2DRect lookupTexture;    //512x512 6bit LookupTable.
uniform float interpolation;


void main()
{
    vec2 pos = gl_TexCoord[0].xy;

    vec4 originalCol = texture2DRect(sourceTexture, pos);
    float blue = floor(originalCol.b * 63.0);
    float b2 = floor(blue / 8.0);

    vec2 lookupPos;
    lookupPos.x = originalCol.r * 63.0+ 64.0 * (blue-b2*8.0);
    lookupPos.y = originalCol.g * 63.0 + 64.0 * b2;
    vec4 lookupCol = texture2DRect(lookupTexture, lookupPos);
    
    gl_FragColor = originalCol * (1-interpolation) + lookupCol * interpolation;
}