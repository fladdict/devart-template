#version 120

uniform sampler2DRect tex0;
uniform float redOffsetX;
uniform float redOffsetY;
uniform float greenOffsetX;
uniform float greenOffsetY;
uniform float blueOffsetX;
uniform float blueOffsetY;


void main()
{
    vec2 pos = gl_TexCoord[0].xy;
    vec4 col0 = texture2DRect(tex0, pos+vec2(redOffsetX,redOffsetY));
    vec4 col1 = texture2DRect(tex0, pos+vec2(greenOffsetX,greenOffsetY));
    vec4 col2 = texture2DRect(tex0, pos+vec2(blueOffsetX,blueOffsetY));
    vec4 col3 = vec4(col0.r, col1.g, col2.b,1);
    
    gl_FragColor = vec4(col3);
}