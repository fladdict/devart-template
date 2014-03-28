// vertex shader

#version 120

uniform mat4 modelViewProjectionMatrix;

void main(){
    //texCoordVarying = texcoord;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    gl_FrontColor = gl_Color;
}