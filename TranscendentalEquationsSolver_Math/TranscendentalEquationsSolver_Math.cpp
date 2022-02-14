#include <iostream>
#include <string>
#include"Solver.h"
#include"EquationFormatter.h"

using namespace std;

int main()
{
   Solver* solver = new Solver(1, 3, -6, 4, 20);
   //cout.precision(16);

   EquationFormatter* formatter = new EquationFormatter();
   string result = formatter->format(solver->solve());

   cout << result;
}

