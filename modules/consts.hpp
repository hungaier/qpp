#ifndef QPP_CONSTS_H
#define QPP_CONSTS_H

#include<cmath>

namespace qpp {

  const float pi = 3.141592653589793238463e0;
  const float ang_to_bohr = 1.88973e0; // 1 Angstrom to 1 Bohr
  const float bohr_to_angs = 1.0 / ang_to_bohr;
  const float infty = HUGE_VALF;
  const float def_isovalue_mo = 0.02; // (electrons/(bohr)^3)^2
  const float def_isovalue_dens = 0.008; // electrons/(bohr)^3
  const float hartree_to_ev = 27.211;

}

#endif
