# include <iostream>
# include <vector>
using namespace std;

struct Point{
  int x;
  int y;
   Point(int x, int y) {
    this->x = x;
    this->y = y;
   }
};

bool cmpx(const Point& p1, const Point& p2) {
  return p1.x < p2.x;
}

bool cmpy(const Point& p1, const Point& p2) {
  return p1.y < p2.y;
}

double distsq(Point p1, Point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

double findClosest(vector<Point>& points) {
  double mindist = numeric_limits<double>::max();
  for (int i=0; i<points.size(); i++) {
    for (int j=(i + 1); j<points.size(); j++) {
      mindist = min(mindist, distsq(points[i], points[j]));
    }
  }
  return mindist;
}


double closestrec(vector<Point>& sortbyx, vector<Point>&sortbyy) {
  if (sortbyx.size() <= 3) return findClosest(sortbyx);
  int mid = sortbyx.size()/2;
  Point midPoint = sortbyx[mid];
  vector<Point> sortbyxleft;
  vector<Point> sortbyyleft;
  vector<Point> sortbyxright;
  vector<Point> sortbyyright;


  for (int i=0; i<sortbyx.size(); i++) {
    if (sortbyx[i].x < midPoint.x) {
      sortbyxleft.push_back(sortbyx[i]);
    } else if (sortbyx[i].x > midPoint.x) {
      sortbyxright.push_back(sortbyx[i]);
    }
  }

  for (int i=0; i<sortbyy.size(); i++) {
    if (sortbyy[i].x < midPoint.x) {
      sortbyyleft.push_back(sortbyy[i]);
    } else if (sortbyy[i].x > midPoint.x) {
      sortbyyright.push_back(sortbyy[i]);
    }
  }

  double mindist = closestrec(sortbyxleft, sortbyyleft);
  mindist = min(mindist, closestrec(sortbyxright, sortbyyright));

  vector<Point> sortbyymid;
  for(int i=0; i<sortbyy.size(); i++) {
    if (sortbyy[i].x > (midPoint.x - mindist) && sortbyy[i].x < (midPoint.x + mindist)) {
      sortbyymid.push_back(sortbyy[i]);
    }
  }
  for (int i=0; i<sortbyymid.size(); i++) {
    int j = i;
    while ((sortbyymid[j].y - sortbyymid[i].y) < mindist) {
      if (i != j) {
        mindist = min(mindist, distsq(sortbyymid[i], sortbyymid[j]));
      }
      j++;
      if (j >= sortbyymid.size()) break;
    }
  }
  return mindist;
}

double closestPoints(vector<Point>& points) {
  vector<Point> sortbyx;
  vector<Point> sortbyy;
  for (int i=0; i<points.size(); i++) {
    sortbyx.push_back(points[i]);
    sortbyy.push_back(points[i]);
  }
  sort(sortbyx.begin(), sortbyx.end(), cmpx);
  sort(sortbyy.begin(), sortbyy.end(), cmpy);
  return closestrec(sortbyx, sortbyy);
}

int main() {
  vector<Point> points;
  points.push_back(Point(12, 30));
  points.push_back(Point(40, 50));
  points.push_back(Point(5, 1));
  points.push_back(Point(12, 10));
  points.push_back(Point(3, 4));
  cout<<closestPoints(points)<<'\n';
  return 0;
}
