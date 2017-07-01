/**
   @author Rafael Cisneros
*/

#include "Polygonizer.h"

Polygonizer::Polygonizer(Implicit *f) {

  ll = Vector3d(-3.0, -3.0, 0.0);
  ur = Vector3d( 3.0,  3.0, 8.0);
  nx = 8; ny = 8; nz = 8;

  func = f;

  std::cout << "Working" << std::endl;
}

void Polygonizer::start() {

  vol_scan (ll(0), ll(1), ll(2), ur(0), ur(1), ur(2), (ur(0) - ll(0)) / nx, (ur(1) - ll(1)) / ny, (ur(2) - ll(2)) / nz);
}

void Polygonizer::vol_scan(double x0, double y0, double z0, double x1, double y1, double z1, double xinc, double yinc, double zinc) {
  
  VertexPol v[8];
  int k, side = 0;
  bool hit;
  double x, y, z;

  for (z = z0; z <= z1; z += zinc)
    for (y = y0; y <= y1; y += yinc)
      for (x = x0; x <= x1; x += xinc) {

	for (k = 0, hit = false; k < 8; k++) {

	  v[k].p(0) = (k & 1) > 0 ? x : x - xinc;
	  v[k].p(1) = (k & 2) > 0 ? y : y - yinc;
	  v[k].p(2) = (k & 4) > 0 ? z : z - zinc;

	  v[k].fval = func->f_value(v[k].p);

	  if (k == 0)
	    side = sign(v[0].fval);
	  else if (side != sign(v[k].fval))
	    hit = true;
	}

	if (hit) {
	  simplex(v[0], v[1], v[3], v[7]);
	  simplex(v[0], v[5], v[1], v[7]);
	  simplex(v[0], v[3], v[2], v[7]);
	  simplex(v[0], v[2], v[6], v[7]);
	  simplex(v[0], v[4], v[5], v[7]);
	  simplex(v[0], v[6], v[4], v[7]);
	}
      }
}

void Polygonizer::simplex(VertexPol v0, VertexPol v1, VertexPol v2, VertexPol v3) {
  
  if (v0.fval < 0)
    if (v1.fval < 0)
      if (v2.fval < 0)
	if (v3.fval < 0)
	  ;
	else
	  tri(v3, v2, v1, v0);
      else
	if (v3.fval < 0)
	  tri(v2, v0, v1, v3);
	else
	  quad(v2, v3, v0, v1);
    else
      if (v2.fval < 0)
	if (v3.fval < 0)
	  tri(v1, v3, v2, v0);
	else
	  quad(v1, v3, v2, v0);
      else
	if (v3.fval < 0)
	  quad(v1, v2, v0, v3);
	else
	  tri(v0, v3, v2, v1);
  else
    if (v1.fval < 0)
      if (v2.fval < 0)
	if (v3.fval < 0)
	  tri(v0, v1, v2, v3);
	else
	  quad(v0, v3, v1, v2);
      else
	if (v3.fval < 0)
	  quad(v0, v2, v3, v1);
	else
	  tri(v1, v3, v0, v2);
    else
      if (v2.fval < 0)
	if (v3.fval < 0)
	  quad(v0, v1, v2, v3);
	else
	  tri(v2, v3, v1, v0);
      else
	if (v3.fval < 0)
	  tri(v3, v0, v1, v2);
	else
	  ;
}

void Polygonizer::tri(VertexPol v0, VertexPol v1, VertexPol v2, VertexPol v3) {

  Vector3d i0, i1, i2;
  Vector3d n0, n1, n2;
  
  i0 = intersect(v0, v1);
  i1 = intersect(v0, v2);
  i2 = intersect(v0, v3);
  
  n0 = func->f_ngrad(i0);
  n1 = func->f_ngrad(i1);
  n2 = func->f_ngrad(i2);

  adapt_tri(i0, i1, i2, n0, n1, n2, MAX_REC);
}

void Polygonizer::quad(VertexPol v0, VertexPol v1, VertexPol v2, VertexPol v3) {
  
  Vector3d i0, i1, i2, i3;
  Vector3d n0, n1, n2, n3;
  
  i0 = intersect(v0, v2);
  i1 = intersect(v0, v3);
  i2 = intersect(v1, v3);
  i3 = intersect(v1, v2);
  
  n0 = func->f_ngrad(i0);
  n1 = func->f_ngrad(i1);
  n2 = func->f_ngrad(i2);
  n3 = func->f_ngrad(i3);
  
  adapt_tri(i0, i1, i2, n0, n1, n2, MAX_REC);
  adapt_tri(i0, i2, i3, n0, n2, n3, MAX_REC);
}

Vector3d Polygonizer::intersect(VertexPol v0, VertexPol v1) {
  
  double t;
  Vector3d p;
  
  t = v0.fval / (v0.fval - v1.fval);
  p = v0.p + (v1.p - v0.p) * t;
  
  return project(STEP_0, p, func->f_value(p), MAX_REC);
}

Vector3d Polygonizer::project(double s, Vector3d p, double v0, int k) {
  
  double v1;
  
  p = p + func->f_ngrad(p) * (s * sign(v0) * -1.0);
  v1 = func->f_value(p);
  
  if ((abs(v1) < EPS_DIST) || (k-- == 0))
    return p;
  
  if (v0 * v1 < 0.0)
    s /= 2;
  
  return project(s, p, v1, k);
}

void Polygonizer::adapt_tri(Vector3d p0, Vector3d p1, Vector3d p2, Vector3d n0, Vector3d n1, Vector3d n2, int k) {
}

void Polygonizer::output_tri(Vector3d p0, Vector3d p1, Vector3d p2, Vector3d n0, Vector3d n1, Vector3d n2) {
}

Vector3d Polygonizer::midpoint(bool e, Vector3d p0, Vector3d p1) {
}

bool Polygonizer::edge_code(Vector3d n0, Vector3d n1) {
}

int Polygonizer::sign(double v) {
  return (v < 0.0)? -1 : 1;
}
