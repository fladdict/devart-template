#version 120

uniform sampler2DRect tex0;
uniform float blurAmnt;



void main()
{
    vec2 pos = gl_TexCoord[0].xy;
    vec4 color;
    
    color += 1.0 * texture2DRect(tex0, pos + vec2(blurAmnt * -4.0, 0.0));
    color += 2.0 * texture2DRect(tex0, pos + vec2(blurAmnt * -3.0, 0.0));
    color += 3.0 * texture2DRect(tex0, pos + vec2(blurAmnt * -2.0, 0.0));
    color += 4.0 * texture2DRect(tex0, pos + vec2(blurAmnt * -1.0, 0.0));
    
    color += 5.0 * texture2DRect(tex0, pos + vec2(blurAmnt, 0.0));
    
    color += 4.0 * texture2DRect(tex0, pos + vec2(blurAmnt * 1.0, 0.0));
    color += 3.0 * texture2DRect(tex0, pos + vec2(blurAmnt * 2.0, 0.0));
    color += 2.0 * texture2DRect(tex0, pos + vec2(blurAmnt * 3.0, 0.0));
    color += 1.0 * texture2DRect(tex0, pos + vec2(blurAmnt * 4.0, 0.0));
    
    color /= 25.0;
    
    gl_FragColor = color;
}