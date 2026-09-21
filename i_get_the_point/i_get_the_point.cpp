#include <iostream>
#include <cmath>
#include <cassert>

#include <string>

class Point {
public:
    constexpr explicit Point(double x, double y) : x_(x), y_(y) {}

    constexpr void set(double x, double y) noexcept {
        x_ = x;
        y_ = y;
    }

    constexpr double operator-(const Point& other) const {
        return std::sqrt(std::pow(other.getX() - x_, 2) + std::pow(other.getY() - y_, 2));
    }

    constexpr bool operator==(const Point& other) const noexcept {
        return isEqual(other);
    }

    constexpr bool operator!=(const Point& other) const noexcept {
        return !isEqual(other);
    }

    constexpr Point operator/(const Point& other) const noexcept {
        return Point((x_ + other.getX()) / 2, (y_ + other.getY()) / 2);
    }

    constexpr Point operator*(double mult) const noexcept {
        return Point(x_ * mult, y_ * mult);
    }

    constexpr Point& operator++() noexcept {
       ++x_;
        return *this;
    }

    constexpr Point operator++(int) noexcept {
        Point old = *this;
        ++y_;
        return old;
    }

    constexpr Point& operator--() noexcept {
        --x_;
        return *this;
    }

    constexpr Point operator--(int) noexcept {
        Point old = *this;
        --y_;
        return old;
    }

    /// I think returning 0 is okay because I feel that indexing should
    /// trade safety for "performance". The safer way is using getX and getY.
 
    constexpr double operator[](std::string_view index) const {
        if (index == "x" || index == "X") {
            return x_;
        }
        else if (index == "y" || index == "Y") {
            return y_;
        }
        return 0;
    }

    constexpr double operator[](int index) const {
        switch (index) {

        case 0: {
            return x_;
        }
        case 1: {
            return y_;
        }

        default: { 
            return 0;
        }

        }
    }

    constexpr std::string toString() const {
        return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
    }

    constexpr double getX() const noexcept {
        return x_;
    }

    constexpr double getY() const noexcept {
        return y_;
    }

    constexpr bool isEqual(const Point& other) const noexcept {
        return x_ == other.getX() && y_ == other.getY();
    }
private:
    double x_;
    double y_;
};

std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << point.toString();
    return out;
}

std::istream& operator>>(std::istream& in, Point& point)
{
    char open, comma, close;
    double x, y;

    in >> open >> x >> comma >> y >> close;

    if (open != '(' || comma != ',' || close != ')')
        in.setstate(std::ios::failbit);

    point = Point(x, y);
    return in;
}

consteval int getTimeNumber(int index) {
    constexpr std::string_view time = __TIME__;

    if (index == 2 || index == 5)
        throw "Attempted to access semicolon";

    return static_cast<int>(time.at(index));
}

consteval void runTest(bool condition, std::string_view message) {
    if (!condition) {
        throw message;
    }
}

consteval bool runTests() {
    static_assert(sizeof(Point) == 16, "Point class must be 16 bytes");

    {
        /// With this, x and y won't be hardcoded
        constexpr int xAxis = getTimeNumber(6);
        constexpr int yAxis = getTimeNumber(7);

        Point p = Point(xAxis, yAxis);

        runTest(p.getX() == xAxis, "getX() test failed");
        runTest(p.getY() == yAxis, "getY() test failed");

        runTest(p[0] == xAxis, "Point[0] failed (X)");
        runTest(p[1] == yAxis, "Point[1] failed (Y)");

        runTest(p["x"] == xAxis && p["X"] == xAxis, "Point[X] failed");
        runTest(p["y"] == yAxis && p["Y"] == yAxis, "Point[Y] failed");

        ++p;

        runTest(p.getX() == xAxis + 1, "prefix increment failed");
        runTest(p.getY() == yAxis, "prefix increment updated y");

        p++;

        runTest(p.getY() == yAxis + 1, "postfix increment failed");
        runTest(p.getX() == xAxis + 1, "postfix increment updated x");

        {
            Point g = Point(xAxis - 999, yAxis - 999);

            runTest(!g.isEqual(p), "isEqual() failed");

            runTest(!(g == p), "== operator failed");
            runTest(g != p, "!= operator failed");
        }

    }

    return true;
}

int main()
{
    static_assert(runTests(), "Tests failed");

    Point p1 = Point(3.2, 9.8);
    Point p2 = Point(5.5, -1.2);

    std::cout << p1 - p2 << "\n";

    std::cout << p1 << "\n";
}