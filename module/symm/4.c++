#include <symm/shenflis.hpp>
#include <lace/lace3d.hpp>
#include <iostream>
#include <cmath>

typedef lace::vector3d<double> vec3d;
typedef lace::matrix3d<double> mat3d;

using qpp::pi;

bool eq3(double x, double y, double z)
{
  return (x-y)*(x-y) + (y-z)*(y-z) < 1e-8;
}

bool find_sigma(mat3d G, vec3d &n)
{

  mat3d R;
  R = 0e0;
  R(0,0) = R(1,1) = R(2,2) = 1e0;

  R = (R-G)*.5e0;

  bool it_is = true;
  if ( R(0,0)<0 || R(1,1)<0 || R(2,2)<0 )
    {
      return false;
    }
  
  n(0) = std::sqrt(R(0,0));
  n(1) = std::sqrt(R(1,1));
  n(2) = std::sqrt(R(2,2));

  if (R(0,1)<0) n(1)*=-1;
  if (R(0,2)<0) n(2)*=-1;
  
  it_is = ( eq3( R(1,0), R(0,1), n(0)*n(1)) &&
	    eq3( R(2,0), R(0,2), n(0)*n(2)) &&
	    eq3( R(2,1), R(1,2), n(1)*n(2)) );
  return it_is;
  
}

bool find_rotation(mat3d G, vec3d &n, double &phi)
{
  if (G.det()<0) 
    return false;
  else
    {
      mat3d S,A;
      S = .5*(G + G.T());
      A = .5*(G - G.T());
      
      n.x() = A.yz();
      n.y() = A.zx();
      n.z() = A.xy();

      double sphi = n.norm();
      n = n/sphi;
      phi = std::asin(sphi);

      double cphi,nsq;
      int i;
      for (i=0; i<3; i++)
	if ( (nsq = n(i)*n(i)) <= 1e0/3 ) break;
 
      cphi = ( S(i,i) - nsq)/(1e0 - nsq);
      if (cphi<0)
	phi = pi - phi;

      return true;
    }
}

bool find_sigrot(mat3d G, vec3d &n, double &phi)
{
  if (G.det()>0) 
    return false;
  else
    {
      mat3d S,A;
      S = .5*(G + G.T());
      A = .5*(G - G.T());
      
      n.x() = A.yz();
      n.y() = A.zx();
      n.z() = A.xy();

      double sphi = n.norm();
      n = n/sphi;
      phi = std::asin(sphi);

      double cphi,nsq;
      int i;
      for (i=0; i<3; i++)
	if ( (nsq = n(i)*n(i)) <= 1e0/3 ) break;
 
      cphi = ( S(i,i) + nsq)/(1e0 - nsq);
      if (cphi<0)
	phi = pi - phi;

      return true;
    }
}

int main()
{
  qpp::shoenflis<double>::point_group G;

  int ans;
  do
    {
      std::cout << "Currently " << G.size() << " operations\n";
      std::cout << "1.Add rotation\n2.Add plane\n3.Add inversion\n4.Done\n";
      std::cin >> ans;
      if (ans==1)
	{
	  vec3d n;
	  int N;
	  std::cout << "Enter rotation axis:\n";
	  std::cin >> n(0) >> n(1) >> n(2);
	  n = n/norm(n);
	  std::cout << "Enter axis order:\n";
	  std::cin >> N;
	  G.generator(RotMtrx(n,2*pi/N));
	}
      else if (ans==2)
	{
	  vec3d n;
	  std::cout << "Enter some vector perpendicular to the plane:\n";
	  std::cin >> n(0) >> n(1) >> n(2);
	  mat3d S(1,0,0,
		  0,1,0,
		  0,0,1);
	  for (int i=0; i<3; i++)
	    for (int j=0; j<3; j++)
	      S(i,j) -= 2*n(i)*n(j);
	  G.generator(S);
	}
      else if (ans==3)
	G.generator(mat3d(-1, 0, 0,
			   0,-1, 0,
			   0, 0,-1));
    }
  while (0<ans && ans<4);

  std::cout.precision(6);
  for (int i=0; i<G.size(); i++)
    {
      vec3d n;
      double phi;
      std::cout << "Operation #" << i << " " << G.notion(i) << "\n" << G(i)  << "\n";
      if ( find_sigma(G(i),n))
	std::cout << "sigma " << n << "\n";
      if ( find_rotation(G(i),n,phi) )
	std::cout << "rot " << n << " " << phi*180/pi << "\n";
      if ( find_sigrot(G(i),n,phi) )
	std::cout << "S " << n << " " << phi*180/pi << "\n";
    }
}
