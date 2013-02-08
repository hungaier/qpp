#include <iostream>
#include <symm/shenflis.hpp>
#include <lace/lace3d.hpp>
#include <cmath>

typedef lace::vector3d<double> vec3d;
typedef lace::matrix3d<double> mat3d;

void preamble()
{
  std::cout << "\\documentclass[12pt]{report} \n \n\\usepackage{longtable} \n\\usepackage{mathtext}   \n\\usepackage{amssymb} \n\\usepackage[T2A]{fontenc}  \n\\usepackage{indentfirst} \n\\usepackage{amsbsy} \n\\usepackage{epsf} \n \n\\setlength\\belowcaptionskip{10pt} \n\\renewcommand{\\baselinestretch}{1.5} \n\\begin{document} \n \n\\newcommand{\\rr}{\\boldsymbol{r}} \n\\newcommand{\\kk}{\\boldsymbol{k}} \n\\newcommand{\\RR}{\\boldsymbol{R}} \n\\newcommand{\\fsp}{\\mbox{ }} \n\\renewcommand{\\le}{\\leqslant} \n\\renewcommand{\\ge}{\\geqslant} \n\\newcommand{\\ds}{\\displaystyle} \n\\newcommand{\\eps}{\\varepsilon} \n\\newcommand{\\fmbr}{\\begin{array}{c}} \n\\newcommand{\\fm}{\\end{array}} \n\\newcommand{\\ra}{{\\rightarrow}} \n\\newcommand{\\eq}{\\begin{equation}} \n\\newcommand{\\eeq}{\\end{equation}} \n\\newcommand{\\arsh}{\\mathop{\\rm arsh}\\nolimits} \n \n";
}

//typedef lace::dcomplex VALTYPE;
typedef double VALTYPE;
//typedef lace::dcomplex VALTYPE;

void print_multab(qpp::shoenflis<VALTYPE>::point_group &G)
{
  
  std::cout << "\\center{The group multiplication table:}\n\n";
  std::cout << "\\begin{tabular}{c | ";
  for (int i=0; i<G.size(); i++)
    std::cout << "c "; 
  std::cout <<  "} \n";
  
  for (int j=0; j<G.size(); j++)
    std::cout << "& " << "$" << G.notion(j) << "$";
  std::cout << "\\\\ \n \\hline \n ";

  for (int i=0; i<G.size(); i++)
    {
      std::cout << "$" << G.notion(i) << "$";
      for (int j=0; j<G.size(); j++)
	std::cout << "& " << "$" << G.notion(G.multab(i,j)) << "$";
      std::cout << "\\\\\n";
    }
  std::cout << "\\end{tabular}\n\n";

  std::cout << "\\\\\nClasses of conjugated elements:\n\\\\\n";
  for (int i=0; i<G.n_class(); i++)
    {
      std::cout << "\\{";
      for (int j = 0; j<G.dim_class(i); j++)
	std::cout << " $" << G.notion(G.g_class(i,j)) << "$";
      std::cout << "\\}";
      if (i<G.n_class()-1) 
	std::cout << ",";
      else
	std::cout << "\n\n";
    }

  //  for (int i=0; i<G.size(); i++)
  //{
  //  std::cout  << " $"  << G.notion(i) << "\\in"; 
  //  std::cout << "\\{";
  //  for (int j = 0; j<G.n_class(G.class_of(i)); j++)
  //	std::cout <<  G.notion(G.g_class(G.class_of(i),j));
  //  std::cout << "\\}$\n\n";
  //}
}

void print_matrix(lace::matrix<VALTYPE,lace::rectang> &A)
{
  std::cout << "\\left(\\begin{array}{";
  for(int j=0; j<A.size(1); j++) std::cout << "c";
  std::cout <<"}";
  
  for (int i=0; i<A.size(0); i++)
    {
      std::cout << A(i,0);
      for (int j=1; j<A.size(1); j++)
	std::cout << "&" << A(i,j);
      std::cout << "\\\\\n";
    }
  
  std::cout << "\\end{array}\\right)";
}

void print_class(qpp::shoenflis<VALTYPE>::point_group &G, int cl)
{
  std::cout << "$\\{";
  for (int j = 0; j<G.dim_class(cl); j++)
    std::cout << G.notion(G.g_class(cl,j));
  std::cout << "\\}$";
}

void print_chi(qpp::shoenflis<VALTYPE>::point_group &G)
{
  std::cout << "Character table:\n\n\n";
  std::cout.precision(7);

  std::cout << "\\begin{tabular}{c | ";
  for (int i=0; i<G.n_class(); i++)
    std::cout << "c "; 
  std::cout <<  "} \n";
  
  for (int j=0; j<G.n_class(); j++)
    {
      std::cout << "& "<<j;
      //      print_class(G,j);
    }
  std::cout << "\\\\ \n \\hline \n ";

  for (int i=0; i<G.n_irrep(); i++)
    {
      std::cout << G.irrep_notion(i);
      for (int j=0; j<G.n_class(); j++)
	std::cout << "& " << G.chi(i,j);
      std::cout << "\\\\\n";
    }
  std::cout << "\\end{tabular}\n\n";
}

void print_regrep(qpp::shoenflis<VALTYPE>::point_group &G)
{
  for (int g=0; g<G.size(); g++)
    {
      std::cout << "$$\nR(" << G.notion(g) << ")=";

      lace::matrix<VALTYPE,lace::rectang> R;
      R = G.regrep(g);

      print_matrix(R);

      std::cout << "\n$$\n\n";
    }
}

void check_regrep(qpp::shoenflis<VALTYPE>::point_group &G)
{
  for (int g=1; g<G.size(); g++)
    {
      std::cout << "$$\nR(" << G.notion(g-1) << ")*R(" << G.notion(g) <<")=";

      lace::matrix<VALTYPE,lace::rectang> R0,R1,R2,R3;
      R0 = G.regrep(g-1);
      R1 = G.regrep(g);
      R2 = R0*R1;

      print_matrix(R0);
      std::cout << "*";
      print_matrix(R1);
      std::cout << "=";
      print_matrix(R2);
      std::cout << "=R(" << G.notion(G.multab(g-1,g)) << ")=";
      R3 = G.regrep(G.multab(g-1,g));
      print_matrix(R3);

      std::cout << "\n$$\n\n";
    }
}

void print_end()
{
  std::cout << "\\end{document} \n";
}

int main()
{
  qpp::shoenflis<VALTYPE>::point_group G(qpp::shoenflis<VALTYPE>::C_nv(3));
  //  std::cout <<"hello\n";
  G.build_all();
  //G.build_multab();

  preamble();
  print_multab(G);
  print_chi(G);
  //check_regrep(G);
  print_end();
}
