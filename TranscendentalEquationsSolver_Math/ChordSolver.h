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

      int currentPrecision = 0;
      while (currentPrecision != precision)
      {
         long double ksi = findRoot()->index;
         currentPrecision++;
      }

      return 0;
   }

private:
   Derivative* derivative;
   DerivativeFunction* func;

   long double calculate(long double a, long double b)
   {
      long double functionA = equation->getFunctionFrom(a);
      long double functionB = equation->getFunctionFrom(b);

      return a - (functionA / (functionB - functionA)) * (b - a);
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