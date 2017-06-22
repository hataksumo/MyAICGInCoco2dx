uniform float u_weights[22];
uniform int u_raduis;
uniform vec2 u_pixelSize;

uniform vec4 u_mulFactor;
uniform vec4 u_addFactor;

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
	vec4 sum = vec4(0);
	int j=0;
	for(int i = -u_raduis; i <= u_raduis; i++)
	{
		sum += texture2D(CC_Texture0,vec2(v_texCoord.x ,v_texCoord.y + float(i) * u_pixelSize.y)) * u_weights[j++];
	}
	gl_FragColor = v_fragmentColor * (sum * u_mulFactor + u_addFactor);
}