#Technical Research / Shader

Is it possible to empower an expression of the map with shaders?

Can I add  sun rise, sun set… rainy or cloudy weather to the map?

I have been developing mobile camera apps for log times. Making camefe effect is kind of my main field :-)

I think it would be cool to write some shader code for map.

I use color lookup table to convert map's color tone. 

Below is some concept sketch. Seems it works. :-)



Mid Night Shader.

![Shader Sketch](../project_images/sketches/sketch_021_night_light_shader.png?raw=true "Example Image")


Toy Camera Shader.

![Shader Sketch](../project_images/sketch_022_toycamera.png?raw=true "Example Image")


```
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
    float red = originalCol.r * 63.0;
    float green = originalCol.g * 63.0;
    float blue = floor(originalCol.b * 63.0);
    float b2 = floor(blue / 8);

    vec2 lookupPos;
    lookupPos.x = red + 64 * (blue-b2*8);
    lookupPos.y = green + 64 * b2;
    vec4 lookupCol = texture(lookupTexture, lookupPos);
    
    outputColor = originalCol * (1-interpolation) + lookupCol * interpolation;
}
```