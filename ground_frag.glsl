float noise(vec2 location){
	float tout = (noise1(location)+0.6)/1.2;
	if(tout>1.0){
		return 1.0;
	} else if(tout<0.0){
		return 0.0;
	}
	return tout;
}
float randv2(vec2 location){
	return sin(round(location.x*75319.1230))+sin(round(location.y*1029935.1320));
}
void main(){
	float scl = 8;
	float v = ((noise(fragTexCoord*64*scl)/4.0+noise(fragTexCoord*32*scl)/4.0)+noise(fragTexCoord*8*scl)/4.0*2.0)*1.0;
	v *= v;
	finalColor.a = 1.0;
	finalColor.r = 0;
	finalColor.b = 0;
	finalColor.g = 0;
	if(v>0.5){
		finalColor.g = 0.6;
	} else if(v>0.1){
		finalColor.g = 0.3;
	} else{
		finalColor.r = 0.2;
		finalColor.g = 0.2;
	}
}
