#include "positions.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

using namespace std;

Position::Position() {
		myRadius = 1.0;
		myAngleInRadians = 0.0;
		
	}
Position::Position(float r) {
		myRadius = r;
		myAngleInRadians = 0.0;
	}
	
Position::Position(float r, float thetaInRadians) {
		myRadius = r;
		myAngleInRadians = thetaInRadians;
	}
	
void Position::SetAbsolutePosition (float r, float thetaInRadians) {
		myRadius = r;
		myAngleInRadians = thetaInRadians;
	}
	
void Position::IncrementPosition(float rChange, float angularDistChange) {
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
	
bool Position::Sees(Position pos) {
	//fill this in
		float value = myRadius * cos(myAngleInRadians - pos.getAngle());
		return value >= 1.0;
	}
	
void Position::Print() {
    cout << "the myRadius is " << myRadius << endl;
		cout << "the angle is " << myAngleInRadians << endl;
	}
	
bool Position::IsAtStatue() {
		return myRadius == 1.0;
	}

bool Position::IsBetween(Position pos1, Position pos2) {
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
	
float Position::getAngle() {
		return myAngleInRadians;
	}
	
float Position::getRadius() {
		return myRadius;
	}
/*
int main() {
	Position test1 = Position(7.0, 0.0);
	test1.Print();
  cout << "The radius should be 7 and the angle should be 0" << endl;
  cout<< test1.getRadius() << endl;
  cout << test1.getAngle() << endl;
	Position statueTest = Position(1.0, 3.14);
	cout << statueTest.IsAtStatue() << " == " << "1" << endl;
	Position notAtStatueTest = Position (4.0, 2.1);
	cout << notAtStatueTest.IsAtStatue() << " == " << "0" << endl;
	cout << test1.Sees(statueTest) << " == " << "0" << endl;
	return 0;
} ;
*/