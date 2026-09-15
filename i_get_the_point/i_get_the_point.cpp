#include <iostream>
#include <cmath>

#include <string>

class Point {
public:
    explicit Point(double x, double y) : x_(x), y_(y) {}

    double operator-(const Point& other) const {
        return std::sqrt(std::pow(other.getX() - x_, 2) + std::pow(other.getY() - y_, 2));
    }

    bool operator==(const Point& other) const noexcept {
        return isEqual(other);
    }

    bool operator!=(const Point& other) const noexcept {
        return !isEqual(other);
    }

    Point operator/(const Point& other) const noexcept {
        return Point((x_ + other.getX()) / 2, (y_ + other.getY() / 2));
    }

    Point operator*(double mult) const noexcept {
        return Point(x_ * mult, y_ * mult);
    }

    double operator[](std::string_view index) const {
        if (index == "x" || index == "X") {
            return x_;
        }
        else if (index == "y" || index == "Y") {
            return y_;
        }
        throw std::runtime_error("Invalid index");
    }

    std::string toString() const {
        return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
    }

    double getX() const noexcept {
        return x_;
    }

    double getY() const noexcept {
        return y_;
    }

    bool isEqual(const Point& other) const noexcept {
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

void runTests() {
    // ran out of time
}

int main()
{
    Point p1 = Point(3.2, 9.8);
    Point p2 = Point(5.5, -1.2);

    std::cout << p1 - p2 << "\n";

    std::cout << p1 << "\n";
}