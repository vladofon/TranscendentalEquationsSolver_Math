#pragma once
#include <math.h>

class Solver
{
public:

   Solver(int firstNumber, int fnPower, int secondNumber, int thirdNumber)
   {
      this->firstNumber = firstNumber;
      this->fnPower = fnPower;
      this->secondNumber = secondNumber;
      this->thirdNumber = thirdNumber;
   }

   double solve()
   {
      long double index = 0;
      int currentPrecision = 0;
      bool lastSign;
      long double lastNumber;
      long double number;

      lastNumber = separateRoot(index);
      lastSign = (lastNumber > 0) ? true : false;
      index = add(new long double[2]{ index, one / pow(10, currentPrecision) });

      while (currentPrecision != precision)
      {
         number = separateRoot(index);
         bool sign = (number > 0) ? true : false;

         if (sign != lastSign)
         {
            index = (abs(number) < abs(lastNumber)) ? index : add(new long double[2]{ index, (one / pow(10, currentPrecision)) * (-1) });

            currentPrecision++;

            long double tail = (one / pow(10, currentPrecision));

            index = add(new long double[2]{ index, tail });

            lastNumber = separateRoot(index);
            lastSign = (lastNumber > 0) ? true : false;
         }
         else
         {
            lastNumber = number;
            lastSign = sign;
         }

         index += (one / pow(10, currentPrecision));
      }

      return index;//(abs(number) < abs(lastNumber)) ? abs(number) : abs(lastNumber);
   }

   double solveDep()
   {
      long double index = 0;
      int currentPrecision = 0;
      bool lastSign;
      long double lastNumber;
      long double number;

      lastNumber = separateRootDep(index);
      lastSign = (lastNumber > 0) ? true : false;
      index = index + one / pow(10, currentPrecision);

      while (currentPrecision != precision)
      {
         number = separateRootDep(index);
         bool sign = (number > 0) ? true : false;

         if (sign != lastSign)
         {
            index = (abs(number) < abs(lastNumber)) ? index : index + (one / pow(10, currentPrecision)) * (-1);

            long double before = index;

            currentPrecision++;

            long double tail = (one / pow(10, currentPrecision));

            index += tail;

            checkDivisionError(before, index, currentPrecision);

            lastNumber = separateRootDep(index);
            lastSign = (lastNumber > 0) ? true : false;
         }
         else
         {
            lastNumber = number;
            lastSign = sign;
         }

         index += (one / pow(10, currentPrecision));
      }

      return index;//(abs(number) < abs(lastNumber)) ? abs(number) : abs(lastNumber);
   }

private:
   long double firstNumber;
   int fnPower;
   long double secondNumber;
   long double thirdNumber;

   int precision = 5;
   long double one = 1;

   double separateRoot(double number)
   {
      return add(new long double[3]{ pow(number * firstNumber, fnPower), (secondNumber * number), thirdNumber }, 3);
   }

   double separateRootDep(double number)
   {
      return pow(number * firstNumber, fnPower) + (secondNumber * number) + thirdNumber;
   }

   long double add(long double input[], int length = 2)
   {
      long double sum = 0;
      long double sumOfError = 0;

      for (int i = 0; i < length; i++)
      {
         long double y = input[i] - sumOfError;
         long double t = sum + y;
         long double c = (t - sum) - y;

         sum = t;
      }

      return sum;
   }

   bool checkDivisionError(long double before, long double after, int precisionLevel)
   {
      long beforeCeil = roundl(before * pow(10, precisionLevel + 1));
      long afterCeil = roundl(after * pow(10, precisionLevel + 1));

      if (beforeCeil == afterCeil)
      {
         return true;
      }

      return false;
   }
};