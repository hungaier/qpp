#ifndef _QPP_ATOM_H
#define _QPP_ATOM_H

#include <string>

namespace qpp{

  enum basis_set_types{
    gaussian,
    slater,
    tabulated,
    plane_waves,
    nobasis
  };

  // when the geometry is just a set of points
  class empty_atom{};

  // --------------------------------------------------
  // basic class for all other types of atoms
  class generic_atom{

  public:

    // Atom always has a name
    // It is supposed to be unique for each type of atoms
    std::string name;

    virtual bool is_classical() =0;

    virtual bool is_polarisible() =0;

    virtual bool has_atomic_basis() =0;

    virtual basis_set_types basis_type() =0;

  };

  // -------------------------------------------------
  // Classical atoms
  class classical_atom : public generic_atom{
  public:
    //fixme - should it be float?
    float Z,mass;

    virtual bool is_classical(){return true;}

    virtual bool is_polarisible(){return false;}

    virtual bool has_atomic_basis(){return false;}

    virtual basis_set_types basis_type(){return nobasis;}

  };

  class polarisible_atom : public classical_atom{
  public:
    float alpha; // polarisibility

    virtual bool is_polarisible(){return true;}

  };

};

#endif
