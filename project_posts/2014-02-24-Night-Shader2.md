http://www.youtube.com/watch?v=_-2G54bUTvU&feature=youtu.be

Yes now my Google Map has timeline and still very fast!

Pretty cool isn't it?

To express change of time, I implemented lookup table  blender shader.

It blends two lookup table like midnight lookup table and morning lookup talbe.

Another shader I made is night light shader. It detects city structure and dim them. :-)

```
#version 120

//Original Image to Render
uniform sampler2DRect sourceTexture;    //Original Image to Render
uniform sampler2DRect lookupTexture0;    //512x512 6bit LookupTable.
uniform sampler2DRect lookupTexture1;    //512x512 6bit LookupTable.
uniform float interpolation;


void main()
{
    vec2 pos = gl_TexCoord[0].xy;
    vec4 originalCol = texture2DRect(sourceTexture, pos);
    float blue = floor(originalCol.b * 63.0);
    float b2 = floor(blue / 8.0);
    vec2 lookupPos;
    lookupPos.x = originalCol.r * 63.0 + 64.0 * (blue-b2*8.0);
    lookupPos.y = originalCol.g * 63.0 + 64.0 * b2;
    
    vec4 lookupCol0 = texture2DRect(lookupTexture0, lookupPos);
    vec4 lookupCol1 = texture2DRect(lookupTexture1, lookupPos);
    
    gl_FragColor = lookupCol0 * (1-interpolation) + lookupCol1 * interpolation;
}
```
