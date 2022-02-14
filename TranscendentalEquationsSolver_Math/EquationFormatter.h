#pragma once
#include<string>
#include <sstream>
#include <iomanip>
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
      List<string>* thirdColumn = new ArrayList<string>();

      firstColumn = parseIndexesByPrecision(steps);
      secondColumn = parseNumbers(steps);
      thirdColumn = parsePrecision(steps);

      schema->fillColumn(0, 0, firstColumn);
      schema->fillColumn(0, 1, secondColumn);
      schema->fillColumn(0, 2, thirdColumn);

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
      schema->getRow(0).createColumn("precision");
   }

   List<string>* parseNumbers(List<Step*>* numbers)
   {
      List<string>* stringNumbers = new ArrayList<string>();

      long size = numbers->getSize();
      for (long i = 0; i < size; i++)
      {
         if (numbers->get(i)->isEmpty != true)
         {
            ostringstream strs;
            strs << numbers->get(i)->number;

            string str = strs.str();

            if (numbers->get(i)->sign == true)
               str = " " + str;

            stringNumbers->add(str);
         }
         else
         {
            stringNumbers->add("not exists");
         }
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

   List<string>* parsePrecision(List<Step*>* indexes)
   {
      List<string>* stringNumbers = new ArrayList<string>();

      long size = indexes->getSize();
      for (long i = 0; i < size; i++)
      {
         string precisionString = to_string(indexes->get(i)->precision);
         stringNumbers->add("10^" + precisionString);
      }

      return stringNumbers;
   }

   List<string>* parseIndexesByPrecision(List<Step*>* indexes)
   {
      List<string>* stringIndexes = new ArrayList<string>();

      long size = indexes->getSize();
      for (long i = 0; i < size; i++)
      {
         if (indexes->get(i)->isEmpty != true)
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
               ostringstream sout;
               sout << std::setprecision(99) << indexes->get(i)->index;
               //cout << strs.str() << endl;

               string result = sout.str().substr(0, indexSizeBeforeFloatPoint + precision + 2);
               stringIndexes->add(result);
            }
         }
         else
         {
            stringIndexes->add("not exists");
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