/*
 * geometry.h
 *
 *  Created on: Jul 29, 2018
 *      Author: kucala
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include<vector>

enum class Dimension
{
  NONE,
  ONE_D,
  TWO_D,
  THREE_D
};

enum class Geometry_Type
{
  Line,
  Rectangle,
  Triangle
};

//base class
class Geometry
{
public:
  Geometry(const Geometry_Type & type) : my_type_(type){
    switch (type){

    case Geometry_Type::Line:
      dimension_ = Dimension::ONE_D;
      num_points_ = 2;
      local_coords_vec_.resize(num_points_);
      global_coords_vec_.resize(num_points_);
      break;
    case Geometry_Type::Rectangle:
      dimension_ = Dimension::TWO_D;
      num_points_ = 4;
      local_coords_vec_.resize(num_points_);
      global_coords_vec_.resize(num_points_);

      break;
    case Geometry_Type::Triangle:
      dimension_ = Dimension::TWO_D;
      num_points_ = 3;
      local_coords_vec_.resize(num_points_);
      global_coords_vec_.resize(num_points_);

      break;
    default:
      throw("Invalid Geometry_Type");
      break;
    }
  }
  virtual ~Geometry(){};

  int num_points() { return num_points_; }
  Geometry_Type & get_type() { return my_type_; }

  const std::vector<double> get_local_coords_vec() { return local_coords_vec_; }
  const std::vector<double> get_global_coords_vec() { return global_coords_vec_; }


protected:
  int num_points_ = 0;
  Dimension dimension_ = Dimension::NONE;
  Geometry_Type my_type_;

  std::vector<double> local_coords_vec_;
  std::vector<double> global_coords_vec_;

};

//
class Rectangle : public Geometry
{
public:
  Rectangle() : Geometry(Geometry_Type::Rectangle) {}
  Rectangle(const double width, const double height) :
      width_(width),
      height_(height),
      area_(width * height),
      Geometry(Geometry_Type::Rectangle) {}
  ~Rectangle(){};

  double & width() { return width_; }
  double & height() { return height_; }
  double & area() { return area_; }
  void populate_local_coords();
protected:
  double width_ = 1;
  double height_ = 1;
  double area_ = 1;

};

//
class Line : public Geometry
{
public:
  Line() : Geometry(Geometry_Type::Line) {}
  Line(const double length) :
    length_(length),
    Geometry(Geometry_Type::Line)
  {
    populate_local_coords(); //populate the local coords

  }
  ~Line(){};

  double & length() { return length_; }

  void populate_local_coords();
  void populate_global_coords(const double &x0, const double &x1);
  std::vector<Line*> mesh_linear(const int n_elems);

protected:
  double length_ = 1;

};

void Line::populate_local_coords()
{
  local_coords_vec_[0] = 0;
  local_coords_vec_[1] = 1;
}

void Line::populate_global_coords(const double &x0, const double &x1)
{
  global_coords_vec_[0] = x0;
  global_coords_vec_[1] = x1;
}

std::vector<Line*> Line::mesh_linear(const int n_elems)
{
  std::vector<Line*> elem_list(n_elems);
  const double x0 = global_coords_vec_[0];
  const int n_pts = n_elems + 1;

  const double dx = (global_coords_vec_[num_points_] - x0) / n_pts;

  for(unsigned i = 0; i < n_elems; ++i){
    Line elem(dx);
    elem.populate_global_coords(x0 + dx*(i), x0 + dx*(i+1));
    elem_list[i] = &elem;
  }

  return elem_list;
}

#endif /* GEOMETRY_H_ */
