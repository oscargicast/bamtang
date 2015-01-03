#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

using namespace std;


class Vector {
 public:
  Vector(double x = 0, double y = 0, double z = 0) {
    x_ = x;
    y_ = y;
    z_ = z;
  }

  void set(double x, double y, double z) {
    x_ = x;
    y_ = y;
    z_ = z;
  }

  void set_pretty(string point_name) {
    double x, y, z;
    cout << "========== Enter " << point_name << " ==========" << endl;

    cout << point_name << "x = ";
    x = read_var();

    cout << point_name << "y = ";
    y = read_var();

    cout << point_name << "z = ";
    z = read_var();

    set(x, y, z);
  }

  void set_x(double x) {
    x_ = x;
  }

  void set_y(double y) {
    y_ = y;
  }

  void set_z(double z) {
    z_ = z;
  }

  double x() const {
    return x_;
  }

  double y() const {
    return y_;
  }

  double z() const {
    return z_;
  }

  void Print() {
    cout << "(" << x_ << ", " << y_ << ", " << z_ << ")" << endl;
  }

  // Returns false if any value is inf.
  // Convert from Vector to bool.
  operator bool() const {
    return isfinite(x_) && isfinite(y_) && isfinite(z_);
  }

  double Module() {
    return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
  }

  // Operators overload.
  // Plus and minus.
  inline Vector operator+(const Vector &vector) const {
    return Vector(x_ + vector.x(), y_ + vector.y(), z_ + vector.z());
  }
  inline Vector operator-(const Vector &vector) const {
    return Vector(x_ - vector.x(), y_ - vector.y(), z_ - vector.z());
  }
  inline Vector operator-() const {
    return Vector(-x_, -y_, -z_);
  }
  // Scalar product and division.
  inline Vector operator/(double scalar) const {
    return Vector(x_ / scalar , y_ / scalar, z_ / scalar);
  }

  // Product functions.
  static double DotProduct(Vector v1, Vector v2) {
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
  }
  static Vector CrossProduct(Vector v1, Vector v2) {
    return Vector(
             v1.y() * v2.z() - v1.z() * v2.y(),
             v1.z() * v2.x() - v1.x() * v2.z(),
             v1.x() * v2.y() - v1.y() * v2.x()
           );
  }

 private:
  double read_var() {
    double var;
    while (!(cin >> var)) {
      cout << "Invalid value, try again: ";
      cin.clear();
      while (cin.get() != '\n');
    }
    return var;
  }

  double x_;
  double y_;
  double z_;
};

Vector operator*(double scalar, Vector vector) {
  Vector scalar_product;
  scalar_product.set_x(scalar * vector.x());
  scalar_product.set_y(scalar * vector.y());
  scalar_product.set_z(scalar * vector.z());
  return scalar_product;
}

Vector operator*(Vector vector, double scalar) {
  return scalar * vector;
}

// Returns true if Q projects the shadow point S with the light vector V.
double ShadowCondition(Vector q, Vector s, Vector v) {
  // If the angle of QS vector and V vector is 0, then a shadow is proyected.
  // a.b = |a||b|cos(theta); if theta == 0, then:
  // a.b = |a||b|
  Vector qs = s - q;
  return Vector::DotProduct(qs, v) == qs.Module() * v.Module();
}

// Return the shadown point S if it exits otherwise it returns a vector with
// the form V(inf, inf, inf).
Vector GetShadowPoint(Vector q, Vector p1, Vector p2, Vector p3, Vector v) {
  Vector n;
  double t;

  // Normal vector = p1p3 x p1p2
  n = Vector::CrossProduct(p1 - p3, p1 - p2);
  // Plane: n.(P-p1) = 0
  // Line: q + tv = P
  // Thus: t = (n.p0 - n.q) / n.v
  t = Vector::DotProduct(n, p1) - Vector::DotProduct(n, q);
  t /= Vector::DotProduct(n, v);

  // Getting the desired point P = q + tv
  Vector shadow_point;
  shadow_point = q + t * v;

  if (ShadowCondition(q, shadow_point, v) && isfinite(t)) {
    // ShadowCondition ensures that the light source is in backlight.
    //
    // isfinite(t): t!="infinite" ensures the case when the
    // vector v and the plane are parallel.
    return shadow_point;
  }
  return Vector(numeric_limits<double>::infinity(),
                numeric_limits<double>::infinity(),
                numeric_limits<double>::infinity());
}

// Returns 'c' to continue or 'q' to quit.
char ContinueOrQuit(char guard) {
  cout << endl << "Enter [c] to continue or [q] to quit" << endl;
  cin >> guard;
  while (guard != 'c' && guard != 'q') {
    cout << "Invalid command, try again: ";
    cin.clear();
    while (cin.get() != '\n');
    cin >> guard;
  }
  return guard;
}

int main()
{
  Vector q, p1, p2, p3, v, s;
  char guard;

  do {
    // Sets inputs.
    q.set_pretty("Q");
    p1.set_pretty("P1");
    p2.set_pretty("P2");
    p3.set_pretty("P3");
    v.set_pretty("V");

    cout << endl;
    cout << "========== Summary ==========" << endl;
    cout << "Q: "; q.Print();
    cout << "P1: "; p1.Print();
    cout << "P2: "; p2.Print();
    cout << "P3: "; p3.Print();
    cout << "V: "; v.Print();
    cout << endl;

    // All magic is made by this function.
    s = GetShadowPoint(q, p1, p2, p3, v);
    if (s) {
      cout << "++++++++++ I'm exist! :) ++++++++++" << endl;
      cout << "S: ";
      s.Print();
    }
    else
      cout << "++++++++++ I don't have shadow :( ++++++++++" << endl;

    // Asks to continue or not.
    guard = ContinueOrQuit(guard);
    if (guard == 'q')
      break;

    cout << endl << endl;
  } while (true);

  return 0;
}