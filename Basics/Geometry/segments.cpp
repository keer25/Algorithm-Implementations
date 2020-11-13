# include <iostream>
# include <vector>
# include <set>
using namespace std;

struct Point {
  int x;
  int y;
  int segind;

  Point(int x, int y, int segind) {
    this->x = x;
    this->y = y;
    this->segind = segind;
  }

  Point(int x, int y) {
    this->x = x;
    this->y = y;
    this->segind = -1;
  }

  Point(){}

  bool operator==(const Point& rhs) const {
    if (x != rhs.x) return false;
    if (y != rhs.y) return false;
    return true;
  }

  // If it needs ot be defined outside, operator<(two params) no need to mention event then
  bool operator<(const Point& rhs) const {
    if (x == rhs.x) return y < rhs.y;
    return x < rhs.x;
  }
};

// Returns p1p0 < p2p0
bool anglecmp(const Point& p1, const Point& p2, const Point& p0) {
  return (p1.x - p0.x)*(p2.y - p0.y) > (p2.x - p0.x)*(p1.y - p0.y);
}

struct Segment {
  Point from;
  Point to;

  Segment(Point from, Point to) {
    // Enforces from < to, for convenienc when traversing all points
    if (to < from) {
      Point temp = from;
      from = to;
      to = temp;
    } else if (to == from) {
      cout<<"Invalid Zero Length Segment!\n";
    }
    this->from = from;
    this->to = to;
  }

  Segment() {}

  bool operator<(const Segment& rhs) const {
    Segment s1;
    Segment s2;
    if (from.x == rhs.from.x) {
      bool ans = from.y < rhs.from.y;
      return ans;
    } else if (from.x < rhs.from.x) {
      s1 = *this;
      s2.from = from;
      s2.to = rhs.from;
    } else {
      s1.from  = rhs.from;
      s1.to = from;
      s2 = rhs;
    }
    // true if s1 < s2
    bool ans = anglecmp(s1.to, s2.to, s1.from);
    // If crossp is 0 then it can be considered equal
    return ans;
  }
};

bool checkIntersection(const Segment& s1, const Segment& s2) {
  int mins2x = min(s2.from.x, s1.from.x);
  int maxs2x = max(s2.from.x, s2.from.x);
  if ((s1.from.x < mins2x && s1.to.x < mins2x) || (s1.from.x > maxs2x && s1.to.x > maxs2x)) {
    return false;
  }
  int mins2y = min(s2.from.y, s2.to.y);
  int maxs2y = max(s2.from.y, s2.to.y);
  if ((s1.from.y < mins2y && s1.to.y < mins2y) || (s1.from.x > maxs2y && s1.to.x > maxs2y)) {
    return false;
  }

  if (anglecmp(s1.from, s2.to, s2.from) == anglecmp(s1.to, s2.to, s2.from)) return false;
  if (anglecmp(s2.from, s1.to, s1.from) == anglecmp(s2.to, s1.to, s1.from)) return false;
  return true;
}

void printseg(const Segment& s) {
  cout<<s.from.x<<", "<<s.from.y<<"    "<<s.to.x<<", "<<s.to.y<<"\n";
}

// Assumes no zero length segments
bool anySegmentIntersects(vector<Segment> segments) {
  vector<Point> presorted;
  set<Segment> searchtree;
  // Have a point struct which references to the segment
  for(int i=0; i<segments.size(); i++) {
    segments[i].from.segind = i;
    segments[i].to.segind = i;
    presorted.push_back(segments[i].from);
    presorted.push_back(segments[i].to);
  }
  sort(presorted.begin(), presorted.end());

  // Under the assumption that there are not zero length segments
  for (int i=0; i<presorted.size(); i++) {
      int segind = presorted[i].segind;
      cout<<"Proccessing point "<<presorted[i].x<<", "<<presorted[i].y<<'\n';
      if (presorted[i] == segments[segind].from) {
        auto segit = searchtree.insert(segments[segind]); // Get the iterator and use it to get above below
        auto below = segit.first; // <=
        auto above = segit.first; // >
        if (below != searchtree.begin()) below--;
        if (above != searchtree.end()) above++;
      if (below != searchtree.end()) {
        if (checkIntersection(*(below), segments[segind])) return true;
      }
      if (above != searchtree.end()) {
        if (checkIntersection(*(above), segments[segind])) return true;
      }
    } else {
      auto segit = searchtree.find(segments[segind]); // find uses ==
      auto below = segit; // <=
      auto above = segit; // >
      if (below != searchtree.begin()) below--;
      if (above != searchtree.end()) above++;

      if (above != searchtree.end() && below != searchtree.end()) {
        if (checkIntersection(*(above), *(below))) return true;
      }
      searchtree.erase(segments[segind]);

    }
  }
  return false;
}

int main() {
  Point p1(0, 0);
  Point p2(1, 1);
  Point p3(0, 1);
  Point p4(1, 0);

  Segment s1(p1, p2);
  Segment s2(p3, p4);
  vector<Segment> segments;
  segments.push_back(s1);
  segments.push_back(s2);
  cout<<anySegmentIntersects(segments)<<'\n';
  segments.clear();
  segments.push_back(Segment(p1, p3));
  segments.push_back(Segment(p2, p4));
  cout<<anySegmentIntersects(segments)<<'\n';
  return 0;
}
