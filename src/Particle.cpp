#include "Particle.h"


Particle::Particle() {
	Particle(ofColor::hotPink,
		ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0));
}

Particle::Particle(ofColor c,
	ofVec3f p) {
	color = c;
	position = p;
}

void Particle::update() {
	//lifespan += deltaTime;
	//velocity += acceleration;
	//velocity.limit(50);
	//position += velocity;
}

void Particle::draw(ofImage image) {
	ofSetColor(color);
	ofPushMatrix();

	ofTranslate(position);

	ofFill();
	ofSetHexColor(0xe0be21);
	image.draw(0,0,0);

	
	ofPopMatrix();

}

//drawable shape