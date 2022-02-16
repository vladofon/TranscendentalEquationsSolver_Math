#pragma once

class DerivativeFunction
{
public:

   virtual long double function(long double x) = 0;
};

class Derivative
{
public:

   long double firstOrder(DerivativeFunction* d, long double x)
   {
      return (d->function(x + precision) - d->function(x - precision)) / (2 * precision);
   }

   long double secondOrder(DerivativeFunction* d, long double x)
   {
      return (d->function(x + precision) - 2 * d->function(x) + d->function(x - precision)) / (precision * precision);
   }

private:

   double precision = 0.1;
};