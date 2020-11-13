# include <iostream>
# include <vector>

using namespace std;

struct Point{
  int x;
  int y;

  Point(int x, int y) {
    this->x  = x;
    this->y = y;
  }

  Point() {
  }

  bool operator==(const Point& rhs) {
    return (x == rhs.x && y == rhs.y);
  }
};

struct Segment{
  Point from;
  Point to;

  Segment(Point& from, Point& to) {
    this->from = from;
    this->to = to;
  }
  Segment() {
  }
};


bool pointcmp(Point& p1, Point& p2) {
  if (p1.y == p2.y) return p1.x < p2.x;
  return p1.y < p2.y;
}

// Assumes from is same for two segments
bool anglecmp(Segment& s1, Segment& s2) {
  if (s1.from.x != s2.from.x || s2.from.y != s1.from.y) cout<<"Invalid Input\n";
  bool ans = (s1.to.x - s1.from.x)*(s2.to.y - s2.from.y) > (s1.to.y - s1.from.y)*(s2.to.x - s2.from.x);
  return ans;
  // If s1 to s2 is counterclockwise, crossp is positive and s1 < s2
}

bool angleEquals(Segment& s1, Segment& s2) {
  if (!anglecmp(s1, s2) && !anglecmp(s2, s1)) return true;
  return false;
}

int distsq(Point p1, Point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

vector<Point> findconvexhull(vector<Point>& points) {
  if (points.size() < 3) return points;
  Point p0 = points[0];
  int p0ind = 0;
  for (int i=0; i<points.size(); i++) {
    if (pointcmp(points[i], p0)) { // if p0 < p1
      p0 = points[i];
      p0ind = i;
    }
  }
  Point p = p0;
  vector<Point> ans;
  bool jarvisInit = false; // To allow p == p0 for first iteration

  while(!(p==p0) || !jarvisInit) {
    jarvisInit = true;
    ans.push_back(p);
    Point nextPoint;
    bool minInit = false;
    for (int i=0; i<points.size(); i++) {
      if (points[i] == p) continue;
      if(!minInit) {
        nextPoint = points[i];
        minInit = true;
      } else {
        Segment s1(p, points[i]);
        Segment s2(p, nextPoint);
        if (anglecmp(s1, s2)) nextPoint = points[i];
        else if (angleEquals(s1, s2)) {
          if (distsq(p, points[i]) > distsq(p, nextPoint)) nextPoint = points[i];
        }
      }
    }
    p = nextPoint;
  }
  return ans;
}

void print_vec(vector<Point>& vec) {
  for (int i=0; i<vec.size(); i++) {
    cout<<vec[i].x<<','<<vec[i].y<<"   ";
  }
  cout<<'\n';
}

int main() {
  vector<Point> points;
  points.push_back(*(new Point(0, 0)));
  points.push_back(*(new Point(3, 0)));
  points.push_back(*(new Point(3, 3)));
  points.push_back(*(new Point(0, 3)));
  points.push_back(*(new Point(1, 1)));
  points.push_back(*(new Point(3, 1)));
  vector<Point> ans = findconvexhull(points);
  print_vec(ans);
  return 0;
}
