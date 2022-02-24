#pragma once
#include "Solver.h"

class DerivativeFunction
{
public:
   Equation* equation;

   DerivativeFunction(Equation* equation)
   {
      this->equation = equation;
   }

   long double function(long double x)
   {
      long double* members = new long double[equation->size()];

      for (int i = 0; i < equation->size(); i++)
      {
         members[i] = equation->get(i).represent(x);
      }

      return add(members, equation->size());
   }

private:
   long double add(long double input[], int length = 2)
   {
      long double sum = 0;
      long double sumOfError = 0;

      for (int i = 0; i < length; i++)
      {
         long double y = input[i] - sumOfError;
         long double t = sum + y;
         sumOfError = (t - sum) - y;

         sum = t;
      }

      return sum;
   }
};

class Derivative
{
public:
   DerivativeFunction* d;

   Derivative(DerivativeFunction* d)
   {
      this->d = d;
   }

   long double firstOrder(long double x)
   {
      return (d->function(x + precision) - d->function(x - precision)) / (2 * precision);
   }

   long double secondOrder(long double x)
   {
      return (d->function(x + precision) - 2 * d->function(x) + d->function(x - precision)) / (precision * precision);
   }

private:

   double precision = 0.1;
};