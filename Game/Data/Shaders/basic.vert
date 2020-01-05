#version 120

attribute vec2 a_Position;
attribute vec4 a_Color;

uniform vec2 u_ObjectTranslation;
uniform vec2 u_CameraTranslation;
uniform vec2 u_ProjectionScale;

varying vec4 v_Color;

void main()
{
    vec2 pos = a_Position;

    pos += u_ObjectTranslation;
    pos += u_CameraTranslation;
    pos *= u_ProjectionScale;

    gl_Position = vec4( pos, 0, 1 );

    v_Color = a_Color;
}
