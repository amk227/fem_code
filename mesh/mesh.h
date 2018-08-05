/*
 * mesh.h
 *
 *  Created on: Aug 4, 2018
 *      Author: kucala
 */

#ifndef MESH_MESH_H_
#define MESH_MESH_H_
#include"../geometry/geometry.h"

class Mesh{
public:
  Mesh(Geometry * geom) : my_base_geom_(geom) {};
  ~Mesh(){};

  Geometry * get_base_geom() { return my_base_geom_; };
  template <typename T>
  void mesh_linear(const int n_elems);

protected:
  Geometry * my_base_geom_ = nullptr;
  std::vector< Line* > elem_list_;
};

template <typename T>
void Mesh::mesh_linear(const int n_elems)
{
  elem_list_ = dynamic_cast<Line*>(my_base_geom_)->mesh_linear(n_elems);
}


#endif /* MESH_MESH_H_ */
