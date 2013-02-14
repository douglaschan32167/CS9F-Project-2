#ifndef POSITIONS_H
#define POSITIONS_H

class Position {
public:
	// Initialize a position. It consists of a radius expressed in meters
	// and an angle expressed in radians.
	Position ();	// radius = 1, angle = 0.
	Position (float r);	// angle = 0.
	Position (float r, float thetaInRadians);

	// Reinitialize this position.
	void SetAbsolutePosition (float r, float thetaInRadians);

	// Change this position, incrementing the radius by rChange
	// and incrementing the angle by angularDistChange/myRadius.
	// angularDistChange is expressed in meters.
	// One of the two arguments must be 0.
	// Negative radius values represent movement toward the statue.
	// Positive distance changes represent counterclockwise motion; 
	// negative values are clockwise.
	void IncrementPosition (float rChange, float angularDistChange);

	// Print this position.
	void Print ( ) ;

	// Return true if someone at this position can see someone or
	// something at the argument position (i.e. the statue does
	// not block one's view), and return false otherwise.
	// The argument position must be at the statue.
	bool Sees (Position pos);

	// Return true if this position is at the base of the statue,
	// i.e. its radius is 1, and return false otherwise.
	bool IsAtStatue ( );

	// Return true if this position is between the first argument
	// position and the second.  Precondition: the counterclockwise
	// difference between the first and second argument positions 
	// is less than ¼ radians, and the radii of all the positions 
	// are the same.
	bool IsBetween (Position pos1, Position pos2);
	
	// Returns the angle (in radians) and the radius of the Position object respectively
  float getAngle();
  float getRadius();
  
private:
	float myRadius;
	float myAngleInRadians;
};

#endif