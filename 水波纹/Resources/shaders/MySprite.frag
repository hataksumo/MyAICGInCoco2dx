varying vec4 v_color;
varying vec2 v_texCoord;

uniform float u_intensity;

void main()
{
	gl_FragColor = v_color * texture2D(CC_Texture0,v_texCoord) * u_intensity;
}