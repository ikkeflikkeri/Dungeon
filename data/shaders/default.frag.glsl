#version 120

uniform sampler2D uniTex;

varying vec3 fragColor;
varying vec2 fragTexCoord;

void main()
{
	vec4 texColor = texture2D(uniTex, fragTexCoord);
	gl_FragColor = texColor * vec4(fragColor, 1.0);
}