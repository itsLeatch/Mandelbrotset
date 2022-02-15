uniform float maxIteration; 

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main(){

int iteration = 0;

double zReal = 0;
double zImaginary = 0;

while(iteration < maxIteration && zReal * zReal + zImaginary * zImaginary <= 4){
double temp = zReal * zReal - zImaginary * zImaginary + gl_TexCoord[0].x;
zImaginary = 2 * zReal * zImaginary + gl_TexCoord[0].y;
zReal = temp;
iteration++;
}
double colorVal = (double) iteration / maxIteration;

gl_FragColor = vec4(hsv2rgb(vec3(colorVal,1,1 - colorVal)),1.0f);
}