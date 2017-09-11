#include "qppcpp.hpp"
#include <symm/autosymm.hpp>

template<class REAL>
void def_autosymm()
{
  def("best_transform", qpp::py_best_transform<REAL>);
  def("rotate_transform", qpp::rotate_pair<REAL>);
  def("analyze_transform", qpp::py_analyze_transform<REAL>);
  def("find_point_symm", qpp::find_point_symm<REAL>);
  def("bravais_point_group", qpp::bravais_point_group<REAL>);
}

void qpp_export8()
{
  def_autosymm<float>();
  def_autosymm<double>();
}
