#include <cmath>

class Position {
	private float myRadius;
	private float myAngleInRadians;
	
	Position() {
		myRadius = 1.0;
		myAngleInRadians = 0.0;
		
	}
	Position(float r) {
		myRadius = r;
		myAngleInRadians = 0.0;
	}
	
	Position(float r, float thetaInRadians) {
		myRadius = r;
		myAngleInRadians = thetaInRadians;
	}
	
	void SetAbsolutePosition(float r, float thetaInRadians){
		myRadius = r;
		myAngleInRadians = thetaInRadians;
	}
	
	void IncrementPosition(float rChange, float angularDistChange) {
		myRadius += rChange;
		if (myRadius < 1.0) {
			myRadius = 1.0;
		}
		myAngleInRadians += angularDistChange/myRadius;
		if (myAngleInRadians > 2 * 3.14) {
			while(myAngleInRadians > 2 * 3.14) {
				myAngleInRadians -= 6.28;
			}
		}
		if (myAngleInRadians < 0) {
			while(myAngleInRadians < 0) {
				myAngleInRadians += 6.28;
			}
		}
	}
	
	bool Sees(Position pos) {
	//fill this in
		value = myRadius * cmath.cos(myAngleInRadians - pos.getAngle);
		return value >= 1;
	}
	
	void Print() {
		cout >> "the myRadius is" >> myRadius >> endl;
		cout >> "the angle is" >> myAngleInRadians >> endl;
	}
	
	bool IsAtStatue() {
		return myRadius == 1.0;
	}

	bool IsBetween(Position pos1, Position pos2) {
		bool isBetweenRadius = (pos1.getRadius() <= myRadius && pos2.getRadius() >= myRadius) || (pos1.getRadius() >= myRadius && pos2.getRadius() <= myRadius);
		bool isBetweenAngle = true;
	//fill this in
	}
	
	float getAngle() {
		return myAngleInRadians;
	}
	
	float getRadius() {
		return myRadius;
	}




};