#include "positions.h"
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <iostream>

using namespace std;

/*  --- Project Source Code --- */

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
		float value = myRadius * cos(myAngleInRadians - pos.myAngleInRadians);
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
		//assume pos2 - pos1 is less than 3.14 radians.
  float maxGap = cos(pos2.myAngleInRadians - pos1.myAngleInRadians);
  return (cos(myAngleInRadians - pos1.myAngleInRadians) > maxGap) && (cos(pos2.myAngleInRadians - myAngleInRadians) > maxGap);
}
	
/*  --- END OF PROJECT SOURCE CODE  --- */


	
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