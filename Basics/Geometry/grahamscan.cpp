# include <iostream>
# include <vector>
# include <stack>
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
};

struct Segment{
  Point from;
  Point to;

  Segment(Point& from, Point& to) {
    this->from = from;
    this->to = to;
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
  cout<<"Chose root "<<p0.x<<", "<<p0.y<<'\n';
  vector<Segment> rootsegmentstemp;
  for (int i=0; i<points.size(); i++) {
    if (i != p0ind) rootsegmentstemp.push_back(*(new Segment(p0, points[i])));
  }
  sort(rootsegmentstemp.begin(), rootsegmentstemp.end(), anglecmp);

  // If multiple elemts have the same angle retain only the farthest one from p0
  vector<Segment> rootsegments;
  for (int i=0; i<rootsegmentstemp.size(); ) {
    Segment retained = rootsegmentstemp[i];
    while (angleEquals(rootsegmentstemp[i], retained)) {
      if (distsq(retained.to, p0) < distsq(rootsegmentstemp[i].to, p0)) retained = rootsegmentstemp[i];
      i++;
      if (i >= rootsegmentstemp.size()) break;
    }
    rootsegments.push_back(retained);
  }

  stack<Point> convexhull;
  convexhull.push(p0);
  convexhull.push(rootsegments[0].to);
  convexhull.push(rootsegments[1].to);

  for (int i=2; i<rootsegments.size(); i++) {
    cout<<"New point "<<rootsegments[i].to.x<<", "<<rootsegments[i].to.y<<'\n';
    Point pj = convexhull.top(); // pj is top and pi is next to yop
    convexhull.pop(); // temp
    Point pi = convexhull.top();
    convexhull.push(pj);
    // We know p1 < pi always wrt p0 hence p0, p1 is never removed out of stack
    while (!anglecmp(*(new Segment(pi, pj)), *(new Segment(pi, rootsegments[i].to)))) { // pk >= pj remove pj add pk
      convexhull.pop();
      pj = convexhull.top();
      convexhull.pop(); // temp;
      pi = convexhull.top();
      convexhull.push(pj);
    }
    convexhull.push(rootsegments[i].to);
  }

  vector<Point> ans;
  while (convexhull.size() > 0) {
    ans.push_back(convexhull.top());
    convexhull.pop();
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
  points.push_back(*(new Point(0, 0)));
  points.push_back(*(new Point(3, 3)));
  points.push_back(*(new Point(0, 3)));
  points.push_back(*(new Point(1, 1)));
  points.push_back(*(new Point(3, 1)));
  vector<Point> ans = findconvexhull(points);
  print_vec(ans);
  return 0;
}
