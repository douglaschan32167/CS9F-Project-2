#include <math.h>
#include <stdio.h>
#include <iostream>
using namespace std;



class Position {
private:
	float myRadius;
	float myAngleInRadians;
public:	
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
		float value = myRadius * cos(myAngleInRadians - pos.getAngle());
		return value >= 1.0;
	}
	
	void Print() {
		printf("the myRadius is %f", myRadius);
		printf("the angle is %f", myAngleInRadians);
	}
	
	bool IsAtStatue() {
		return myRadius == 1.0;
	}

	bool IsBetween(Position pos1, Position pos2) {
		//all radii are assumed to be the same
		//assume all positions are within 
		float onetwogap = pos1.getAngle() - pos2.getAngle();
		if (onetwogap < .25 && myRadius == pos1.getRadius() && myRadius == pos2.getRadius() && pos1.getRadius() == pos2.getRadius()) {
			return pos1.getAngle() - myAngleInRadians < onetwogap; 
		} else {
			return false;
		}
		
	//fill this in
	}
	
	float getAngle() {
		return myAngleInRadians;
	}
	
	float getRadius() {
		return myRadius;
	}




};

int main() {
	Position test1 = Position(7.0, 0.0);
	test1.Print();
	printf("The radius should be 7 and the angle should be 0");
	printf("%f", test1.getRadius());
	printf("%f", test1.getAngle());
	Position statueTest = Position(1.0, 3.14);
	cout << statueTest.IsAtStatue() << endl;
	printf("IsAtStatue test: That should say true. ^");
	Position notAtStatueTest = Position (4.0, 2.1);
	cout << notAtStatueTest.IsAtStatue() << endl;
	printf("IsAtStatueTest: that should say 0 ^");
	cout << test1.Sees(statueTest) << endl;
	printf("Sees test: That should say 0 ^");
	return 0;
} ;
