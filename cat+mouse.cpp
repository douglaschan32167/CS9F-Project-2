#include <iostream>
#include <cmath>
#include "positions.h"

using namespace std;


/*  --- Project Source Code --- */


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
  Position catPrevPosition;
  for (int minutes = 1; minutes <= 30; minutes++) {    
    if (cat.IsAtStatue()) {
      // Save previous cat position before incrementing to see if mouse has been caught
      catPrevPosition = cat;
      cat.IncrementPosition(0.0, 1.25);
      mouse.IncrementPosition(0.0, 1.0);
      // If cat passes mouse, end simulation
      if (mouse.IsBetween(catPrevPosition, cat)) {
        cout << "Cat has caught mouse in " << minutes << " minutes! NOM NOM NOM... Game over." << endl;
        return;
      }
    } else {
      if (cat.Sees(mouse)) {
        cat.IncrementPosition(1.0, 0.0);
      } else {
        cat.IncrementPosition(0.0, 1.25);
      }
      mouse.IncrementPosition(0.0, 1.0);
    }
    // Inform user of cat and mouse positions at current time
    printGameStatus(mouse, cat, minutes);
  }
  cout << "Cat gives up after failing to catch the mouse within 30 minutes. Game over." << endl;
  return;
}

/*  --- END OF PROJECT SOURCE CODE  --- */







/*  --- Unit and Integration Tests  --- */


// cat+mouse.cpp :

void SimplifyAngleInDegreesTest() {
  bool test1, test2, test3, test4, test5;
  // negative angles should be confined to an angle between 0 and 360
  test1 = (SimplifyAngleInDegrees(-180.0) == 180.0);
  test2 = (SimplifyAngleInDegrees(-361.0) == 359.0);
  
  
  // angles exceeding 360 should be confined to an angle between 0 and 360
  test3 = (SimplifyAngleInDegrees(720.0) == 360.0);
  test4 = (SimplifyAngleInDegrees(365.0) == 5.0);
  
  // If angle is within 0 and 360 degrees, simply return input angle
  test5 = (SimplifyAngleInDegrees(355.0) == 355.0);
  
  if (test1 && test2 && test3 && test4&& test5) {
    cout << "SimplifyAngleInDegrees Test cases passed." << endl;
  } else {
    cout <<"SimplifyAngleInDegrees Test cases fail: " << test1 << " " << test2 << " " << test3 << " " << test4 << " " << test5 << endl;
  }
}

void DegreesToRadiansTest() {
  // Test quadrants
  cout << "DegreesToRadians Test: " << DegreesToRadians(180.0) << " " << DegreesToRadians(0.0) << " " << DegreesToRadians(90.0) << " " << DegreesToRadians(270.0) << endl;
  cout << "DegreesToRadians Test: Above should be: 3.14, 0.0, 1.57, 4.71" << endl;

}


// positions.cpp:

// Assumes Sees() is accurate
void SetAbsolutePositionTest() {
  bool test1, test2, test3;
  Position testLocation1, testLocation2, testLocation3;
  testLocation2.SetAbsolutePosition(1.5, 0);
  testLocation3.SetAbsolutePosition(1.0, 3.14);
  
  test1 = (testLocation1.Sees(testLocation1) == true);
  test2 = (testLocation2.Sees(testLocation1) == true);
  test3 = (testLocation3.Sees(testLocation1) == false);
  
  if (test1 && test2 && test3) {
    cout << "SetAbsolutePosition Test cases passed." << endl;
  } else {
    cout << "SetAbsolutePosition Test cases fail: " << test1 << " " << test2 << " " << test3 << endl;
  }
  
}

// Assumes Sees() is accurate
void IncrementPositionTest() {
  bool test1, test2, test3;
  Position testLocation1;
  Position testLocation2(1.5);
  Position testLocation3(1.0, 3.14);
  
  testLocation1.IncrementPosition(0.0, 3.14);
  testLocation2.IncrementPosition(1.0, 0.0);
  
  test1 = (testLocation2.Sees(testLocation1) == false);
  test2 = (testLocation3.Sees(testLocation1) == true);
  test3 = (testLocation3.Sees(testLocation2) == false);
  
  if (test1 && test2 && test3) {
    cout << "IncrementPosition Test cases passed." << endl;
  } else {
    cout << "IncrementPosition Test cases fail: " << test1 << " " << test2 << " " << test3 << endl;
  }
}

void SeesTest() {
  bool test1, test2, test3;
  Position testLocation1;
  Position testLocation2(1.5);
  Position testLocation3(1.0, 3.14);
  
  test1 = (testLocation1.Sees(testLocation1) == true);
  test2 = (testLocation2.Sees(testLocation1) == true);
  test3 = (testLocation3.Sees(testLocation1) == false);
  
  if (test1 && test2 && test3) {
    cout << "Sees Test cases passed." << endl;
  } else {
    cout << "Sees Test cases fail: " << test1 << " " << test2 << " " << test3 << endl;
  }
}

void IsAtStatueTest() {
  bool test1, test2;
  Position atStatue;
  Position notAtStatue(2.5);
  
  test1 = (atStatue.IsAtStatue() == true);
  test2 = (notAtStatue.IsAtStatue() == false);
  
  if (test1 && test2) {
    cout << "IsAtStatue Test cases passed." << endl;
  } else {
    cout << "IsAtStatue Test cases fail: " << test1 << " " << test2 << endl;
  }
}

void IsBetweenTest() {
  bool test1, test2, test3;
  Position testLocation1;
  Position testLocation2(1.0, 1.5);
  Position testLocation3(1.0, 1.7);
  
  test1 = (testLocation1.IsBetween(testLocation2, testLocation3) == false);
  test2 = (testLocation2.IsBetween(testLocation1, testLocation3) == true);
  test3 = (testLocation3.IsBetween(testLocation1, testLocation2) == false);
  
  if (test1 && test2 && test3) {
    cout << "IsBetween Test cases passed." << endl;
  } else {
    cout << "IsBetween Test cases fail: " << test1 << " " << test2 << " " << test3 << endl;
  }
}

/*  --- END OF TESTS  --- */



/*  -- MAIN FUNCTION  --- */


int main () {
  /* Uncomment following to run unit and integration tests */
  /*
  SimplifyAngleInDegreesTest();
  DegreesToRadiansTest();
  SetAbsolutePositionTest();
  IncrementPositionTest();
  SeesTest();
  IsAtStatueTest();
  IsBetweenTest();
  cout << endl;
  cout << "END OF TESTS" << endl;
  cout << endl;
  cout << endl;
  */
  
  /*  ---   End of Tests  --- */
  
	Position cat, mouse;
	GetPositions (cat, mouse);
  cat.Print();
  mouse.Print();
	RunChase (cat, mouse);
	return 0;
	
}