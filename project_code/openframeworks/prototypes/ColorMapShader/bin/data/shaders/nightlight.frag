#version 120


uniform sampler2DRect texture0;
uniform float interpolation;
uniform float randomSeed;
uniform float lightThreshold;
uniform float lightAmplifier;

float random( vec2 p )
{
    // We need irrationals for pseudo randomness.
    // Most (all?) known transcendental numbers will (generally) work.
    const vec2 r = vec2(
                        23.1406926327792690,  // e^pi (Gelfond's constant)
                        2.6651441426902251); // 2^sqrt(2) (Gelfond–Schneider constant)
    return fract( cos( mod( 123456789., 1e-7 + 256. * dot(p,r) ) ) );
}


void main()
{
    vec2 pos = gl_TexCoord[0].xy;
    
    vec4 originalCol = texture2DRect(texture0, pos);
    if(originalCol.r>lightThreshold && originalCol.g>lightThreshold && originalCol.b>lightThreshold){
        float rnd = random(vec2(sin(pos.x+randomSeed), cos(pos.y+randomSeed)));
        float bri = 1 + rnd*0.25;
        originalCol.r = originalCol.r * bri;
        originalCol.g = originalCol.g * bri;
        originalCol.b = originalCol.b * bri;
    }
    
    
    gl_FragColor = originalCol;
}