
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

