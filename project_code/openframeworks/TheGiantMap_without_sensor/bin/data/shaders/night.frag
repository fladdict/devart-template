#version 120

uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform float blurAmnt;
uniform vec4 globalColor;
uniform float overlayAlpha;
uniform float lightOffset;



void main()
{
    vec2 pos = gl_TexCoord[0].xy;
    vec4 col0 = texture2DRect(tex0, pos);
    vec4 col1 = texture2DRect(tex1, pos);
    vec4 col2 = col1/255.0 * (col1 + 2.0*col0/255.0 * (255.0-col1));
    col2*=255;
    
    vec4 overlayCol = col0*(1-overlayAlpha) + col2* overlayAlpha;
    float bri = overlayCol.r * 0.298912 + overlayCol.g * 0.586611 + overlayCol.b + 0.114478;
    
    if(bri>0.7 && overlayAlpha>0){
        overlayCol.r += (1.0-overlayCol.r)*lightOffset*0.3 * overlayAlpha;
        overlayCol.g += (1.0-overlayCol.g)*lightOffset*0.3 * overlayAlpha;
        overlayCol.b += (1.0-overlayCol.b)*lightOffset*0.3 * overlayAlpha;
    }
    
    gl_FragColor = overlayCol;
}