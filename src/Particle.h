#pragma once
#ifndef Particle_h
#define Particle_h

#include "ofMain.h"

class Particle {
public:
	ofColor color;
	ofVec3f position;

	Particle();
	Particle(ofColor c,
		ofVec3f p);

	void update();
	void draw(ofImage image);
};

#endif /* Particle_h */
