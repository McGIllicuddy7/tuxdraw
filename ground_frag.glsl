#version 330
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

int v0 = 109382;
int v1 = 932132;
int v2 = 312332;
struct Noise2d{int v0; int v1; int v2;};
float interpolate(float a, float b, float s){
    return a*(1-s)+b*s;
}


vec2 random_gradient(Noise2d self,int x, int y) {
        int w = 32;
        int s = w / 2;
        int a = x;
        int b = y;
        a *= self.v0;
        b ^= a << s | a >> (w - s);
        b *= self.v1;
        a &= b << s | b >> (w - s);
        a *= self.v2;
        float random = float(a) * (3.14159265 /(10000000.0));
        vec2 rt;
	rt.x = cos(random);
	rt.y = sin(random);
	return rt;
        //return self.points[y as usize % self.points.len()][x as usize % self.points.len()];
}

float dot_grid_gradient(Noise2d  self,int ix, int iy, float x, float y){
    vec2 gradient = random_gradient(self,ix, iy);
    float dx = x - float(ix);
    float dy = y - float(iy);
    return (dx * gradient.x + dy * gradient.y);
}

float perlin(Noise2d self,float xbase, float ybase){
    float x = xbase;
    float y = ybase;
    int x0 = int(floor(x));
    int x1 = x0 + 1;
    int y0 = int(floor(y));
    int y1 = y0 + 1;
    float sx = float(x) - float(x0);
    float sy = float(y)- float(y0);
    float n00 = dot_grid_gradient(self,x0, y0, x, y);
    float n10 = dot_grid_gradient(self,x1, y0, x, y);
    float ix0 = interpolate(n00, n10, sx);
    float n01 = dot_grid_gradient(self, x0, y1, x, y);
    float n11 = dot_grid_gradient(self,x1, y1, x, y);
    float ix1 = interpolate(n01, n11, sx);
    float value = interpolate(ix0, ix1, sy);
    return value;
}

// Output fragment color
out vec4 finalColor;
float noise(Noise2d self,vec2 location){
	float tout = (perlin(self,location.x, location.y)+0.6)/1.2;
	if(tout>1.0){
		return 1.0;
	} else if(tout<0.0){
		return 0.0;
	}
	return tout*tout;
}
float randv2(vec2 location){
	return sin(round(location.x*75319.1230))+sin(round(location.y*1029935.1320));
}

void main(){
	Noise2d ns;
	ns.v0 = v0;
	ns.v1 = v1;
	ns.v2 = v2;
	float scl = 8;
	float v = ((noise(ns,fragTexCoord*16*scl)/4.0+noise(ns,fragTexCoord*8*scl)/4.0)+noise(ns,fragTexCoord*4*scl)/4.0*2.0)*0.8;
	v *= v;
	finalColor.a = 1.0;
	finalColor.r = 0;
	finalColor.b = 0;
	finalColor.g = 0;
	ns.v0 = v0*7;
	ns.v1 = v1*13;
	ns.v2 = v2*17;
	scl = 32;
	float mlt=((noise(ns,fragTexCoord*16*scl)/4.0+noise(ns,fragTexCoord*8*scl)/4.0)+noise(ns,fragTexCoord*4*scl)/4.0*2.0)*0.2 +0.8;
	if(v>0.4){
		finalColor.g = 0.25*mlt;
	} else if(v>0.2){
		finalColor.g = 0.2*mlt;
	} else if (v>0.1){
		finalColor.r = 0.18*mlt;
		finalColor.g = 0.18*mlt;
	} else{
		finalColor.r = 0.15*mlt;
		finalColor.g = 0.15*mlt;
	}

}
