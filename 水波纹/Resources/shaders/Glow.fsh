varying vec4 v_fragmentColor; 
varying vec2 v_texCoord;

uniform vec4 u_textColor;
uniform vec4 u_effectColor;
 
void main() 
{
    gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord) * u_textColor; 
}