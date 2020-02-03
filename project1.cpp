#include <iostream>
using namespace std;

//Represents a 2D point (x,y)
class Point {
protected:
	double x; //x coordinate value
	double y; //y coordinate value
public:
	//default constructor; x = 0.0 and y = 0.0
	Point() {
		x = 0.0;
		y = 0.0;
	}
	//no-default constructor, rounds input parameters
	Point(double xvalue, double yvalue) {
		x = round(xvalue);
		y = round(yvalue);
	}
	// set x = xvalue and y = yvalue
	void setLocation(double xvalue, double yvalue) {
		x = xvalue;
		y = yvalue;
	}
	//rounds to 2 decimal places
	double round(double var)
	{
		double value = (int)(var * 100.0);
		return (double)value / 100.0;
	}
	//return x
	double getXValue() {
		return x;
	}
	//return y
	double getYValue() {
		return y;
	}
	//checks if two points are equal
	bool isEqual(Point point) {
		if ((x == point.getXValue()) & (y == point.getYValue()))
			return true;
		return false;
	}
	// Print (x, y)
	void display() {
		cout << "(" << x << ", " << y << ")";
	}
};
class LineSegment {
protected:
	Point P1;
	Point P2;
public:
	//default constructor
	LineSegment() {
		P1 = Point();
		P2 = Point();
	}
	//no-default constructor
	LineSegment(Point one, Point two) {
		P1 = one;
		P2 = two;
	}
	//return the length of the line segment
	//Formula:|P1P2|=squareroot((x1-x2)^2+(y1-y2)^2)
	double length() {
		return round(squareroot((P1.getXValue() - P2.getXValue()) * (P1.getXValue() - P2.getXValue())
			+ (P1.getYValue() - P2.getYValue()) * (P1.getYValue() - P2.getYValue())));
	}
	//return the midpoint of the line segment
	//Formula:((x1+x2)/2,(y1+y2)/2)
	Point midpoint() {
		return Point(((P1.getXValue() + P2.getXValue()) / 2),((P1.getYValue() + P2.getYValue()) / 2));
	}
	//return the x-intercept point of the line segment
	//We are assuming the intercepts are same as those of a line
	//Formula:x=x1-y1((x2-x1)/(y2-y1))
	Point xIntercept() {
		double xIntercept = P1.getXValue() - P1.getYValue() * 
			((P2.getXValue() - P1.getXValue()) / (P2.getYValue() - P1.getYValue()));
		return Point(xIntercept, 0.00);
	}
	//return the y-intercept point of the line segment
	//Formula:c=y1-x1((y2-y1)/(x2-x1))
	Point yIntercept() {
		//slope()=(y2-y1)/(x2-x1)
		double yIntercept = P1.getYValue() - P1.getXValue() * ((P2.getYValue() - P1.getYValue()) / (P2.getXValue() - P1.getXValue()));
		return Point(0.00, yIntercept);
	}
	//return the slope of the line segment
	//Formula:(y2-y1)/(x2-x1)
	double slope() {
		return round((P2.getYValue() - P1.getYValue()) / (P2.getXValue() - P1.getXValue()));
	}
	//returns vector point of line segment
	//Formula:(X2-X1,Y2-Y1)
	Point vector(Point P1, Point P2) {
		return Point(P2.getXValue() - P1.getXValue(), P2.getYValue() - P1.getYValue());
	}
	//Returns cross multiplication result of two points
	//Formula:mxn=u1v2-u2v1
	double crossMultiply(Point P1, Point P2) {
		return (P1.getXValue() * P2.getYValue()) - (P1.getYValue() * P2.getXValue());
	}
	//returns true if L intersects
	//with this line segment
	bool itIntersects(LineSegment L) {
		//if the lines are parallel, and intercepts are different, they don't intersect
		if (isParallel(L) & !yIntercept().isEqual(L.yIntercept()))
			return false;
		//Define Points
		Point Q1 = L.getP1();
		Point Q2 = L.getP2();
		//Define vectors
		Point P1P2 = vector(P1, P2);
		Point P1Q1 = vector(P1, Q1);
		Point P1Q2 = vector(P1, Q2);
		Point Q1Q2 = vector(Q1, Q2);
		Point Q1P1 = vector(Q1, P1);
		//Cross Multiply
		//P1P2xP1Q1
		double d1 = crossMultiply(P1P2, P1Q1);
		//P1P2xP1Q2
		double d2 = crossMultiply(P1P2, P1Q2);
		//Q1Q2xQ1P1
		double d3 = crossMultiply(Q1Q2, Q1P1);
		//Q1Q2xP1P2
		double d4 = crossMultiply(Q1Q2, P1P2);
		//Line Segments intersect if d1d2 <= 0, d3d4 <=0
		if ((d1 * d2 <= 0) && (d3 * d4 <= 0)) {
			return true;
		}
		return false;
	}
	//returns intersection point of this segment and input segment
	Point intersectionPoint(LineSegment L) {
		//If the points don't intersect return origin to avoid errors
		if (!itIntersects(L))
			return Point(0, 0);
		//x = (c2-c1)/(m1-m2)
		//y = (c1m2-c2m1)/(m2-m1)
		double c2 = L.yIntercept().getYValue();
		double c1 = yIntercept().getYValue();
		double m1 = slope();
		double m2 = L.slope();
		double x = (c2 - c1) / (m1 - m2);
		double y = (c1 * m2 - c2 * m1) / (m2 - m1);
		return Point(x, y);
	}
	//check if slopes are equivalent
	bool isParallel(LineSegment L) {
		if (L.slope() == slope())
			return true;
		return false;
	}
	//Square root function
	double squareroot(double k) {
		double eps = 1e-6;
		double l = 0.0, r, mid;
		if (k >= 1) {
			r = k;
		}
		if (k < 1) {
			r = 1;
		}
		while (l - k / l > eps || l - k / l < -eps)
		{
			mid = l + (r - l) / 2;
			if (mid < k / mid)
			{
				l = mid;
			}
			else {
				r = mid;
			}
		}
		return l;
	}
	//rounds to 0.00
	double round(double var)
	{
		double value = (int)(var * 100.0);
		return (double)value / 100.0;
	}
	//Returns P1
	Point getP1() {
		return P1;
	}
	//Returns P2
	Point getP2() {
		return P2;
	}
	//Displays line equation y=m*x+b
	void displayEquation() {
		cout << "y=" << slope() << "*x+" << yIntercept().getYValue();
	}
};
class Intervals {
protected:
	LineSegment* segments;
	int count;
	int maxSize;
public:
	//default constructor
	Intervals() {
		segments = NULL;
		count = 0;
		maxSize = 0;
	}
	//non-default constructor
	Intervals(int size) {
		segments = new LineSegment[size];
		count = 0; //currently there is none
		maxSize = size;
	}
	//Assigns segment to next index in array
	void addLineSegment(LineSegment L) {
		segments[count++] = L;
	}
	//Displays information about each line segment
	void display() {
		for (int i = 0; i < count; i++) {
			LineSegment s = segments[i];
			cout << "Line Segment " << i + 1 << ":" << endl;
			s.getP1().display();
			cout << ",";
			s.getP2().display();
			cout << endl << "Slope:" << s.slope() << endl;
			cout << "Midpoint:(" << s.midpoint().getXValue() << ", " << s.midpoint().getYValue() << ")" << endl;
			cout << "X Intercept:" << s.xIntercept().getXValue() << endl;
			cout << "Y Intercept:" << s.yIntercept().getYValue() << endl;
			cout << "Length:" << s.length() << endl;
			s.displayEquation();
			cout << endl;
		}
	}
	//Prints information on intersections between each line segment
	void displayIntersects() {
		int currentSegment = 0;
		for (int i = 0; i < count; i++) {
			for (int j = i + 1; j < count; j++) {
				cout << "The line segments compared are segments[" << i << "] and segments[" << j << "]: ";
				if (segments[i].itIntersects(segments[j])) {
					cout << "Intersection Point :";
					Point iP = segments[i].intersectionPoint(segments[j]);
					iP.display();
				}
				else if (segments[i].slope() == segments[j].slope()) {
					cout << "Lines are Parallel";
				}
				else {
					cout << "Not Parallel and not Intersecting";
				}
				cout << endl;
			}
		}
	}
};
int main() {
	int noOfSegments;
	cin >> noOfSegments;
	Intervals intervals = Intervals(noOfSegments);
	for (int i = 0; i < noOfSegments; i++) {
		double x;
		double y;
		cin >> x >> y;
		Point point1 = Point(x, y);
		cin >> x >> y;
		Point point2 = Point(x, y);
		LineSegment segment = LineSegment(point1, point2);
		intervals.addLineSegment(segment);
	}
	intervals.display();
	intervals.displayIntersects();
	return 0;
}

