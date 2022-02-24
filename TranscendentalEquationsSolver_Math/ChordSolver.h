#pragma once
#include  "Solver.h"
#include  "Derivative.h"


class ChordSolver : public Solver
{
public:

   ChordSolver(Equation* equation) : Solver(equation)
   {
      this->func = new DerivativeFunction(equation);
      this->derivative = new Derivative(this->func);
   }

   long double solve(int precision) override
   {
      Step* point = findRoot();



      return 0;
   }
   Equation* equation1 = nullptr;
private:
   Derivative* derivative;
   DerivativeFunction* func;

   long double calculate(long double a, long double b, int precision)
   {

   }

   bool chooseWay(long double pointLocation)
   {
      if (derivative->firstOrder(pointLocation) > 0)
      {
         return true;
      }

      return false;
   }


};