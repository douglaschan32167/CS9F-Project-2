#include <iostream>
#include <cmath>
#include "positions.h"

using namespace std;

// Limit input angles to between 0 and 360 degrees.
// Given an input angle in degrees, returns the angle reduced to a float between 0.0 and 360.0
float SimplifyAngleInDegrees(float angleInDegrees) {
  while (angleInDegrees > 360.0 || angleInDegrees < 0.0) {
    if (angleInDegrees > 360.0) {
      angleInDegrees -= 360.0;
    }
    else if (angleInDegrees < 0.0) {
      angleInDegrees += 360.0;
    }
  }
  return angleInDegrees;
}
// Given an angle in degrees, return its value in radians

float DegreesToRadians(float degrees) {
  return degrees * 3.14/180.0;
}

// Print current positions and time-state of simulation
void printGameStatus(Position mouse, Position cat, int minutes) {
  cout << "After " << minutes << " minute(s), " << endl;
  cout << "Cat: " << endl;
  cat.Print();
  cout << endl;
  cout << "Mouse: " << endl;
  mouse.Print();
  cout << endl << endl;
}

// You define the GetPositions function.
// It should read legal cat and mouse positions from the user
// and return the position values in its two arguments.
void GetPositions (Position cat, Position mouse ) {
  float mouseAngleInDegrees, catAngleInDegrees, catRadius, mouseAngleInRadians, catAngleInRadians;
  cout << "First, enter the starting angle of the mouse in degrees: " << endl;
  cin >> mouseAngleInDegrees;
  cout << "Now, enter the starting angle of the cat in degrees: " << endl;
  cin >> catAngleInDegrees;
  cout << "Lastly, enter the starting radius of the cat in degrees: " << endl;
  cin >> catRadius;
  if (catRadius < 1) {
    cout << "Invalid starting radius for cat; must be greater than 1.0, " << endl;
    return;
  }
  // Limit angles to between 0 and 360 degrees.
  mouseAngleInDegrees = SimplifyAngleInDegrees(mouseAngleInDegrees);
  catAngleInDegrees = SimplifyAngleInDegrees(catAngleInDegrees);
  
  // Convert degrees to radians
  mouseAngleInRadians = DegreesToRadians(mouseAngleInDegrees);
  catAngleInRadians = DegreesToRadians(catAngleInDegrees);
  
  // Set initial positions of cat and mouse
  mouse.SetAbsolutePosition(1.0, mouseAngleInRadians);
  cat.SetAbsolutePosition(catRadius, catAngleInRadians);
}


// You define the RunChase function.
// Given initialized cat and mouse positions,
// it should simulate the cat chasing the mouse, printing the 
// result of each movement of cat and mouse.  Either the cat will 
// catch the mouse, or 30 time units will go by and the cat will 
// give up.
void RunChase (Position cat, Position mouse) {
  for (int minutes = 1; minutes <= 30; minutes++) {
    // Save previous cat position before incrementing to see if mouse has been caught
    Position catPrevPosition;
    catPrevPosition.SetAbsolutePosition(cat.getRadius(), cat.getAngle());
    
    if (cat.Sees(mouse)) {
      cat.IncrementPosition(1.0, 0.0);
    } else {
      cat.IncrementPosition(0.0, 1.25);
    }
    mouse.IncrementPosition(0.0, 1.0);
    // Inform user of cat and mouse positions at current time
    printGameStatus(mouse, cat, minutes);
    
    
    // If cat passes mouse, end simulation
    if (cat.IsAtStatue() && mouse.IsBetween(catPrevPosition, cat)) {
      cout << "Cat has caught mouse in " << minutes << " minutes! Game over." << endl;
      return;
    }
  }
  
  cout << "Cat gives up after failing to catch the mouse within 30 minutes. Game over." << endl;
  return;
}

int main () {
	Position cat, mouse;
	GetPositions (cat, mouse);
	RunChase (cat, mouse);
	return 0;
}