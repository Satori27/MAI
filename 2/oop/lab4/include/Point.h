template <class T>
class Point {
    public:
    T x;
    T y;
    Point() = default;

    Point(T _x, T _y) : x(_x), y(_y) {}
};