#version 150

//Original Image to Render
uniform sampler2DRect tex0;
uniform vec4 globalColor;

//Coordinates on texture;
in vec2 texCoordVarying;
out vec4 outputColor;


void main()
{
    vec4 originalCol = texture(tex0, texCoordVarying);
    originalCol.a = 0.1;//originalCol.a * globalColor.a;
    outputColor = originalCol;
}