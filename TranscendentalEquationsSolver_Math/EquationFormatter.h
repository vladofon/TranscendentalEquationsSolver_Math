#pragma once
#include<string>
#include"List.h"
#include"ArrayList.h"
#include "TableSchema.h"
#include "SchemaParser.h"
#include "Step.h"


using namespace std;

class EquationFormatter
{
public:
   EquationFormatter(TableSchema* schema)
   {
      this->schema = schema;
   }

   EquationFormatter()
   {
      // If constructor empty define default schema
      this->schema = new TableSchema();
      initDefaultSchema();
   }

   string format(List<Step*>* steps)
   {
      List<string>* firstColumn = new ArrayList<string>();
      List<string>* secondColumn = new ArrayList<string>();

      firstColumn = parseIndexesByPrecision(steps);
      secondColumn = parseNumbers(steps);

      schema->fillColumn(0, 0, firstColumn);
      schema->fillColumn(0, 1, secondColumn);

      SchemaParser* parser = new SchemaParser(*schema);
      return parser->parseSchema();
   }

private:
   TableSchema* schema;

   void initDefaultSchema()
   {
      schema->createRow("=======+ Solver results +=======");
      schema->getRow(0).createColumn("x");
      schema->getRow(0).createColumn("f(x)");
   }

   List<string>* parseNumbers(List<Step*>* numbers)
   {
      List<string>* stringNumbers = new ArrayList<string>();

      long size = numbers->getSize();
      for (long i = 0; i < size; i++)
      {
         string str = to_string(numbers->get(i)->number);

         if (str[0] != '-')
            str = " " + str;

         stringNumbers->add(str);
      }

      return stringNumbers;
   }

   List<string>* parseIndexes(List<Step*>* indexes)
   {
      List<string>* stringNumbers = new ArrayList<string>();

      long size = indexes->getSize();
      for (long i = 0; i < size; i++)
      {
         stringNumbers->add(to_string(indexes->get(i)->index));
      }

      return stringNumbers;
   }

   List<string>* parseIndexesByPrecision(List<Step*>* indexes)
   {
      List<string>* stringIndexes = new ArrayList<string>();

      long size = indexes->getSize();
      for (long i = 0; i < size; i++)
      {
         long double index = indexes->get(i)->index;
         int precision = indexes->get(i)->precision;

         int indexSizeBeforeFloatPoint = numberLength(index);

         if (precision == 0)
         {
            stringIndexes->add(to_string((long)index));
         }
         else
         {
            string result = to_string(index).substr(0, indexSizeBeforeFloatPoint + precision + 2);
            stringIndexes->add(result);
         }
      }

      return stringIndexes;
   }

   int numberLength(long number)
   {
      long size = 0;

      while (number / 10 != 0)
         size++;

      return size;
   }
};