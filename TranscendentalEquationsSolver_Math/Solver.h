#pragma once
#include"Step.h"
#include"List.h"
#include<math.h>

class EquationMember
{
public:
   int multiplier;
   int power;
   bool isVariable;

   long double represent(long double value)
   {
      if (isVariable)
      {
         return multiplier * pow(value, power);
      }
      else
      {
         return pow(multiplier, power);
      }
   }
};

class Equation
{
public:

   EquationMember get(int index)
   {
      return equation->get(index);
   }

   long size()
   {
      return equation->getSize();
   }

private:

   List<EquationMember>* equation;
};

class Solver
{
protected:

   Solver(Equation* equation, int totalPrecision)
   {
      this->totalPrecision = totalPrecision;
      this->equation = equation;
   }

   List<Step*>* findRoot(Equation equation, int startPoint = 0)
   {

   }

private:
   Equation* equation;
   int totalPrecision;

   long double nextIndex(int stepPrecision)
   {
      return (1 / pow(10, stepPrecision));
   }

   Step* makeStep(long double index, int stepPrecision)
   {
      Step* newStep = new Step;

      newStep->number = separateRoot(index);
      newStep->sign = (newStep->number > 0) ? true : false;
      newStep->precision = stepPrecision;
      newStep->index = index;

      return newStep;
   }

   long double separateRoot(long double number)
   {
      long membersCount = equation->size();
      long double* members = new long double[membersCount];

      for (long i = 0; i < membersCount; i++)
      {
         members[i] = equation->get(i).represent(number);
      }

      return add(members, membersCount);
   }

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