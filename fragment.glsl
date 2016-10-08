varying vec2 varyingTexCoord;
uniform sampler2D texture;
uniform float keyPress;

void main() {
    vec2 texCoord = vec2(varyingTexCoord.x , varyingTexCoord.y + keyPress);
    gl_FragColor = texture2D(texture, texCoord);
}
