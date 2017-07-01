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

class Polygon {

 public:

  Polygon(Vector3d p0, Vector3d p1, Vector3d p2, Vector3d n0, Vector3d n1, Vector3d n2);

  std::vector<Vector3d> p, n;
};

struct VertexPol {

  Vector3d p, n;
  double fval;
};

class Polygonizer {
 public:
  
  Polygonizer(Implicit *f);

  std::list<Polygon> getPolygons() { return polygons; }
  
  void start();

  void vol_scan(double x0, double y0, double z0, double x1, double y1, double z1, double xinc, double yinc, double zinc);
  
  void simplex(VertexPol v0, VertexPol v1, VertexPol v2, VertexPol v3);

  void tri(VertexPol v0, VertexPol v1, VertexPol v2, VertexPol v3);
  void quad(VertexPol v0, VertexPol v1, VertexPol v2, VertexPol v3);
  
  Vector3d intersect(VertexPol v0, VertexPol v1);
  Vector3d project(double s, Vector3d p, double v0, int k);
  
  void adapt_tri(Vector3d p0, Vector3d p1, Vector3d p2, Vector3d n0, Vector3d n1, Vector3d n2, int k);
  void output_tri(Vector3d p0, Vector3d p1, Vector3d p2, Vector3d n0, Vector3d n1, Vector3d n2);
  
  Vector3d midpoint(bool e, Vector3d p0, Vector3d p1);
  bool edge_code(Vector3d n0, Vector3d n1);

  int sign(double v);
  
 private:
  
  static const int MAX_REC = 3;
  static const double STEP_0 = 0.125;
    
  static const double EPS_DIST = 0.00001;
  static const double DOT_TOL = 0.5;
  
  Vector3d ll;
  Vector3d ur;
  double nx, ny, nz;
  
  std::list<Polygon> polygons;

  Implicit *func;
};
