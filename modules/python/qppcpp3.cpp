#include "qppcpp.hpp"
#include <geom/geom.hpp>
#include <symm/gcell.hpp>

template<class REAL,class CELL>
void py_geom_export(const char * pyname)
{
  qpp::geometry<REAL,CELL>::py_props();
  class_<qpp::geometry<REAL,CELL> >(pyname, init<int, optional<const STRING&> >() )
    .def(init<CELL&, optional<const STRING&> >())
    .def("add_observer",    & qpp::geometry<REAL,CELL>::add_observer )
    .def("remove_observer", & qpp::geometry<REAL,CELL>::remove_observer )
    .def("add",     & qpp::geometry<REAL,CELL>::py_add1)
    .def("add",     & qpp::geometry<REAL,CELL>::py_add2)
    .def("add",     & qpp::geometry<REAL,CELL>::py_add3)
    .def("erase",   & qpp::geometry<REAL,CELL>::py_erase)
    .def("insert",  & qpp::geometry<REAL,CELL>::py_insert1)
    .def("insert",  & qpp::geometry<REAL,CELL>::py_insert2)
    .def("insert",  & qpp::geometry<REAL,CELL>::py_insert3)
    .def("clear",   & qpp::geometry<REAL,CELL>::clear)    
    .def("pos",     & qpp::geometry<REAL,CELL>::py_pos1)    
    .def("pos",     & qpp::geometry<REAL,CELL>::py_pos2)    
    .def("pos",     & qpp::geometry<REAL,CELL>::py_pos3)    
    .def("r",       & qpp::geometry<REAL,CELL>::py_pos1)    
    .def("r",       & qpp::geometry<REAL,CELL>::py_pos2)    
    .def("r",       & qpp::geometry<REAL,CELL>::py_pos3)    
    .def("nat",              & qpp::geometry<REAL,CELL>::nat)
    .def("__getitem__",      & qpp::geometry<REAL,CELL>::py_getitem)
    .def("__setitem__",      & qpp::geometry<REAL,CELL>::py_setitem)
    //.add_property("cell",   
    //make_getter(& qpp::geometry<REAL,CELL>::cell, return_value_policy<reference_existing_object>()), 
    //make_getter(& qpp::geometry<REAL,CELL>::cell, return_self<>()), 
    //& qpp::geometry<REAL,CELL>::py_setcell)
    .def_readwrite("cell",   & qpp::geometry<REAL,CELL>::cell)
    .def_readonly("dim",     & qpp::geometry<REAL,CELL>::DIM)
    .def_readwrite("atom",   & qpp::geometry<REAL,CELL>::py_atoms)
    .def_readwrite("coord",  & qpp::geometry<REAL,CELL>::py_coords)
    .def_readwrite("shadow", & qpp::geometry<REAL,CELL>::py_shadow)
    .def_readwrite("x",      & qpp::geometry<REAL,CELL>::py_x)
    .def_readwrite("y",      & qpp::geometry<REAL,CELL>::py_y)
    .def_readwrite("z",      & qpp::geometry<REAL,CELL>::py_z)

    .def("type",         & qpp::geometry<REAL,CELL>::type_table)
    .def("atom_of_type", & qpp::geometry<REAL,CELL>::atom_of_type)
    .def("type",         & qpp::geometry<REAL,CELL>::py_typeofatom)
    .def("n_types",      & qpp::geometry<REAL,CELL>::n_atom_types)
    
    .def_readwrite("auto_update_types", & qpp::geometry<REAL,CELL>::auto_update_types, 
		   "bool auto_update_types: Whether to update atomic type table after any atom manipulations")
    .def_readwrite("frac", & qpp::geometry<REAL,CELL>::frac, 
		   "bool frac: Whether to undestand the atomic coordinates as fractional")
    .def_readwrite("auto_symmetrize", & qpp::geometry<REAL,CELL>::auto_symmetrize,
		   "bool auto_symmetrize: How to treat atoms added near \'high symmetry points\'.\nIf auto_symmetrize==true, put the new atom in high symmetry point instead of given coordinates, when the distance\n between atom and its image less then symmetrization radius (symmrad)")
    .def_readwrite("default_symmrad", & qpp::geometry<REAL,CELL>::default_symmetrize_radius,
		   "real default_symmrad: symmetrization radius for all atoms")
    .def_readwrite("symmrad", & qpp::geometry<REAL,CELL>::py_symmrad,
		   "Usage: symmrad[at] with string at. Symmetrization radius for atom at")
    .def("symmrad_to_dict", & qpp::geometry<REAL,CELL>::py_symmrad2dict,
	 "Outputs the symmrad values in dictionary form")
    .def_readwrite("tol_geom",  & qpp::geometry<REAL,CELL>::tol_geom, "real tol_geom. The distance at which atoms are considered to be at the same point")
    ;
}

template<class REAL>
void py_observer_export(const char * pyname)
{
  class_<qpp::py_geometry_observer<REAL>,boost::noncopyable>(pyname)
    .def("added",    pure_virtual(& qpp::py_geometry_observer<REAL>::added))
    .def("inserted", pure_virtual(& qpp::py_geometry_observer<REAL>::inserted))
    .def("changed",  pure_virtual(& qpp::py_geometry_observer<REAL>::changed))
    .def("erased",   pure_virtual(& qpp::py_geometry_observer<REAL>::erased))
    .def("shaded",   pure_virtual(& qpp::py_geometry_observer<REAL>::shaded))
    ;
}

void qpp_export3()
{
  py_geom_export<float,qpp::periodic_cell<float> >("geometry_f");
  py_geom_export<double,qpp::periodic_cell<double> >("geometry_d");

  py_geom_export<float, qpp::generalized_cell<float,  qpp::matrix3d<float>  > >("geometry_pgf");
  py_geom_export<double,qpp::generalized_cell<double, qpp::matrix3d<double> > >("geometry_pgd");
  py_geom_export<float, qpp::generalized_cell<float,  qpp::rotrans<float>   > >("geometry_cgf");
  py_geom_export<double,qpp::generalized_cell<double, qpp::rotrans<double>  > >("geometry_cgd");

  enum_<qpp::before_after>("geom_change_state")
    .value("before", qpp::before)
    .value("after",  qpp::after)
    ;
  
  py_observer_export<float>("gobserver_f");
  py_observer_export<double>("gobserver_d");

}
