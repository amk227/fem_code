/*
 * main.C
 *
 *  Created on: Jul 29, 2018
 *      Author: kucala
 */

#include<iostream>
#include"geometry/geometry.h"
#include"mesh/mesh.h"

using namespace std;
//writing simple diffusion code du/dt + c*d2u/dx2 = 0

int main()
{

  //create geometry
  const double x0 = 0;
  const double x1 = 1;

  Line my_geom(x1);
  my_geom.populate_global_coords(x0, x1);

  //mesh the geometry
  Mesh my_mesh(&my_geom);
  my_mesh.mesh_linear<Line>(100);

  return 0;
}
