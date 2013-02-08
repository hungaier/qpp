#include <cassert>
#include <cstring>
#include <lace/lace.hpp>
#include <string>
#include <sstream>
#include <boost/format.hpp>
//#include <lace/matrix_expressions.hpp>

using _lace_expressions::matrix_expression;

template<class Z>
std::string zfmt(Z z, int dig = 10 , int prec = 5)
{
  std::basic_ostringstream<char> _fmt;
  _fmt << "%" << dig << "." << prec << "f";

  std::basic_ostringstream<char> _ifmt;
  _ifmt << "%-" << dig << "." << prec << "f";

  std::basic_ostringstream<char> __s;
  if ( z.im() >= 0e0 )
    __s << (boost::format(_fmt.str()) % z.re()) << "+i*" << (boost::format(_ifmt.str()) % z.im());
  else
    __s << (boost::format(_fmt.str()) % z.re()) << "-i*" << (boost::format(_ifmt.str()) % (-z.im()));
  return  __s.str();
}

template <class VALTYPE,lace::matrix_type MT >
void prnmtr(lace::matrix<VALTYPE,MT> &A)
{
  for(int i=0; i<A.size(0); i++)
    {
      for(int j=0; j<A.size(1); j++)
	std::cout << boost::format("%10.5f ") % A(i,j);
      std::cout << "\n";
    }
}

template <class VALTYPE,lace::vector_type VT >
void prnvtr(lace::vector<VALTYPE,VT> &A)
{
  for(int i=0; i<A.size(); i++)
    std::cout << boost::format("%10.5f ") % A(i);
  std::cout << "\n";
}


int main()
{
  int n=10;
  lace::matrix<lace::dcomplex> A(n);
  lace::vector<lace::dcomplex> x(n),y(n),x1(n);

  for (int i=0; i<n;i++)
    x(i)=i;

  A=0e0;
  for (int i=0; i<n;i++)
    A(i,i)=i+1;
  for (int i=0; i<n-1;i++)
    A(i,i+1)=1e0;

  std::cout << "A\n";
  prnmtr(A);
  std::cout << "x\n";
  prnvtr(x);
  
  y=A*x;
  std::cout << "y\n";
  prnvtr(y);
  
  lace::solve_lu(A,y,x1);
  std::cout << "x after solve_lu\n";
  prnvtr(x1);
  std::cout << "lapack status = " << _lace_storage::lapack_info() << "\n";

}
