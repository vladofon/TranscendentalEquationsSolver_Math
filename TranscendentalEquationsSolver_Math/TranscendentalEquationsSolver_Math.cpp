#include <iostream>
#include <string>
#include"Solver.h"
#include"EquationFormatter.h"
#include"Derivative.h"
#include<math.h>

using namespace std;

int main()
{
   // ax^b +- bx^c +- d == 0
   //Solver* solver = new Solver(1, 3, -4, 1, -1);

   //EquationFormatter* formatter = new EquationFormatter();
   //string result = formatter->format(solver->solve());

   //cout << result;

   class Function : public DerivativeFunction
   {
      long double function(long double x) override
      {
         return pow(x, 3) - (6 * pow(x, 2) + 20);
      }
   };

   DerivativeFunction* func = new Function;

   Derivative* derivative = new Derivative;

   cout << derivative->firstOrder(func, 10) << endl;

}

