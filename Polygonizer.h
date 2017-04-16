/**
   @author Rafael Cisneros
*/

#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <Eigen/Core>
#include "Implicit.h"

using namespace Eigen;

class Polygon
{
 public:

  Polygon(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f n0, Vector3f n1, Vector3f n2);

  std::vector<Vector3f> p, n;
};

struct VertexPol
{
  Vector3f p, n;
  double fval;
};

class Polygonizer
{
 public:
  
  Polygonizer();

  std::list<Polygon> getPolygons() { return polygons; }
  
  void start();

  void vol_scan(double x0, double y0, double z0, double x1, double y1, double z1, double xinc, double yinc, double zinc);
  
  void simplex(VertexPol v0, VertexPol v1, VertexPol v2, VertexPol v3);

  void tri(VertexPol v0, VertexPol v1, VertexPol v2, VertexPol v3);
  void quad(VertexPol v0, VertexPol v1, VertexPol v2, VertexPol v3);
  
  Vector3f intersect(VertexPol v0, VertexPol v1);
  
  void output_tri(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f n0, Vector3f n1, Vector3f n2);
  void adapt_tri(Vector3f p0, Vector3f p1, Vector3f p2, Vector3f n0, Vector3f n1, Vector3f n2, int k);
  
  bool edge_code(Vector3f n0, Vector3f n1);
  
  Vector3f midpoint(bool e, Vector3f p0, Vector3f p1);
  Vector3f project(double s, Vector3f p, double v0, int k);
  
  int sign(double v);
  
 private:
  
  static const int MAX_REC = 3;
  static const double STEP_0 = 0.125;
    
  static const double EPS_DIST = 0.00001;
  static const double DOT_TOL = 0.5;
  
  Vector3f ll;
  Vector3f ur;
  double nx, ny, nz;
  
  std::list<Polygon> polygons;

  //Implicit function;
};
