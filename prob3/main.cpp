#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
using namespace std;


class Vector {
private:
    double x, y, z;

public:
    Vector() {
        x = 0;
        y = 0;
        z = 0;
    }
    Vector(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void set(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void pretty_set(string point_name) {
        double x, y, z;
        cout << "========== Enter " << point_name << " ==========" << endl;
        cout << point_name << "x = ";
        while (!(cin >> x)) {
            cout << "Invalid value, try again: ";
            cin.clear();
            while (cin.get() != '\n');
        }

        cout << point_name << "y = ";
        while (!(cin >> y)) {
            cout << "Invalid value, try again: ";
            cin.clear();
            while (cin.get() != '\n');
        }

        cout << point_name << "z = ";
        while (!(cin >> z)) {
            cout << "Invalid value, try again: ";
            cin.clear();
            while (cin.get() != '\n');
        }

        set(x, y, z);
    }

    void setX(double x) {
        this->x = x;
    }

    void setY(double y) {
        this->y = y;
    }

    void setZ(double z) {
        this->z = z;
    }

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    double getZ() const {
        return z;
    }

    void print() {
        cout << "(" << x << ", " << y << ", " << z << ")" << endl;
    }

    // Returns false if any value is inf.
    // Convert from Vector to bool.
    operator bool() const {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
    }

    double Module() {
        return sqrt(x * x + y * y + z * z);
    }

    // Operators overload.
    // Plus and minus.
    inline Vector operator+(const Vector &vector) const {
        return Vector(x + vector.x, y + vector.y, z + vector.z);
    }
    inline Vector operator-(const Vector &vector) const {
        return Vector(x - vector.x, y - vector.y, z - vector.z);
    }
    inline Vector operator-() const {
        return Vector(-x, -y, -z);
    }
    // Scalar product and division.
    inline Vector operator/(double scalar) const {
        return Vector(x / scalar , y / scalar, z / scalar);
    }

    // Product functions.
    static double DotProduct(Vector v1, Vector v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }
    static Vector CrossProduct(Vector v1, Vector v2) {
        return Vector(
                   v1.y * v2.z - v1.z * v2.y,
                   v1.z * v2.x - v1.x * v2.z,
                   v1.x * v2.y - v1.y * v2.x
               );
    }

};

Vector operator*(double scalar, Vector vector) {
    Vector scalar_product;
    scalar_product.setX(scalar * vector.getX());
    scalar_product.setY(scalar * vector.getY());
    scalar_product.setZ(scalar * vector.getZ());
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
// the form (inf, inf, inf)
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

    if (ShadowCondition(q, shadow_point, v) && std::isfinite(t)) {
        // ShadowCondition ensures that the light source is in backlight.
        //
        // std::isfinite(t): t!="infinite" ensures the case when the
        // vector v and the plane are parallel.
        return shadow_point;
    }
    return Vector(std::numeric_limits<double>::infinity(),
                  std::numeric_limits<double>::infinity(),
                  std::numeric_limits<double>::infinity());
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
        q.pretty_set("Q");
        p1.pretty_set("P1");
        p2.pretty_set("P2");
        p3.pretty_set("P3");
        v.pretty_set("V");

        cout << endl;
        cout << "========== Summary ==========" << endl;
        cout << "Q: "; q.print();
        cout << "P1: "; p1.print();
        cout << "P2: "; p2.print();
        cout << "P3: "; p3.print();
        cout << "V: "; v.print();
        cout << endl;

        s = GetShadowPoint(q, p1, p2, p3, v);
        if (s) {
            cout << "++++++++++ I'm exist! :) ++++++++++" << endl;
            cout << "S: ";
            s.print();
        }
        else {
            cout << "++++++++++ I don't have shadow :( ++++++++++" << endl;
        }

        guard = ContinueOrQuit(guard);
        if (guard == 'q')
            break;

        cout << endl << endl;
    } while (true);

    return 0;
}