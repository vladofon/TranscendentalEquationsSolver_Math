#pragma once
#include"TableSchema.h"
#include"TableRecord.h"
#include"SchemaFormatter.h"
#include"List.h"
#include"ArrayList.h"

class SchemaParser
{
public:

   SchemaParser(TableSchema& schema)
   {
      this->schema = schema;
   }

   string parseSchema()
   {
      string table = "";

      SchemaInfo schemaInfo = parseSchemaInfo();
      long cellWidth = schemaInfo.getMaxLength();

      for (long row = 0; row < schema.rowsCount(); row++)
      {
         /* add empty cells for balance(symmetry) */
         schema.rebalanceColumns(row);

         /* only one item can be present in a rowHeader list */
         List<string>* rowHeader = new ArrayList<string>();
         List<string>* columnsHeaders = new ArrayList<string>();
         List<List<string>*>* rowColumns = new ArrayList<List<string>*>();

         rowHeader->add(schema.getRow(row).getName());

         parseRowColumnsNames(*columnsHeaders, row);

         parseRowColumns(*rowColumns, row);

         List<List<string>*>* tableRecords = new ArrayList<List<string>*>();

         /* all columns must have the same size! */
         long tableCapacity = rowColumns->get(0)->getSize();

         initializeTableResources(*tableRecords, tableCapacity);

         retrieveRowToTable(*tableRecords, rowColumns);

         long maxColsCountInRow = schemaInfo.getMaxColumnCount();


         /* ===+ creating records in a table +=== */
         SchemaFormatter formatter = SchemaFormatter();

         /* creating row header */
         TableRecord* header = new TableRecord(rowHeader, cellWidth, space, maxColsCountInRow, true, false);
         table += formatter.createRecord(header);

         /* creating row columns headers */
         TableRecord* column = new TableRecord(columnsHeaders, cellWidth, space, maxColsCountInRow, true, false);
         table += formatter.createRecord(column);

         /* creating row body */
         createRecords(table, tableRecords, cellWidth, row, maxColsCountInRow);
      }

      return table;
   }

private:
   TableSchema schema;
   long space = 2;

   class SchemaInfo
   {
   public:
      SchemaInfo(long maxLength, long headerMaxLength, long contentMaxLength, long maxColumnCount)
      {
         this->maxLength = maxLength;
         this->headerMaxLength = headerMaxLength;
         this->contentMaxLength = contentMaxLength;
         this->maxColumnCount = maxColumnCount;
      }

      long getHeaderMaxLength()
      {
         return this->headerMaxLength;
      }

      long getContentMaxLength()
      {
         return this->contentMaxLength;
      }

      long getMaxLength()
      {
         return maxLength;
      }

      long getMaxColumnCount()
      {
         return maxColumnCount;
      }

   private:
      long maxLength;
      long headerMaxLength;
      long contentMaxLength;
      long maxColumnCount;
   };

   SchemaInfo parseSchemaInfo()
   {
      long maxLength = 0;
      long headerMaxLength = 0;
      long contentMaxLength = 0;
      long maxColumnCount = 0;

      for (long row = 0; row < schema.rowsCount(); row++)
      {
         long rowLength = schema.getRow(row).getName().length();
         long rowColumnsCount = schema.getRow(row).colsCount();

         assignIfBigger(maxLength, rowLength);
         assignIfBigger(headerMaxLength, rowLength);
         assignIfBigger(maxColumnCount, rowColumnsCount);

         for (long col = 0; col < schema.getRow(row).colsCount(); col++)
         {
            long colLength = schema.getRow(row).getColumn(col).getName().length();

            assignIfBigger(maxLength, colLength);
            assignIfBigger(headerMaxLength, colLength);

            for (long cell = 0; cell < schema.getRow(row).getColumn(col).cellsCount(); cell++)
            {
               long cellDataLength = schema.getRow(row).getColumn(col).getCell(cell).getData().length();

               assignIfBigger(maxLength, cellDataLength);
               assignIfBigger(contentMaxLength, cellDataLength);
            }
         }
      }

      return SchemaInfo(maxLength, headerMaxLength, contentMaxLength, maxColumnCount);
   }

   void assignIfBigger(long& to, long from)
   {
      if (from > to)
         to = from;
   }

   //////////////////////////
   /* Parsing dependencies */
   //////////////////////////

   void parseRowColumnsNames(List<string>& columnsNames, long rowIndex)
   {
      for (long column = 0; column < schema.getRow(rowIndex).colsCount(); column++)
      {
         columnsNames.add(schema.getRow(rowIndex).getColumn(column).getName());
      }
   }

   void parseRowColumns(List<List<string>*>& rowColumns, long rowIndex)
   {
      for (long col = 0; col < schema.getRow(rowIndex).colsCount(); col++)
      {
         List<string>* column = new ArrayList<string>();
         rowColumns.add(column);

         parseColumnCells(*column, rowIndex, col);
      }
   }

   void parseColumnCells(List<string>& columnCells, long rowIndex, long colIndex)
   {
      for (long cell = 0; cell < schema.getRow(rowIndex).getColumn(colIndex).cellsCount(); cell++)
      {
         columnCells.add(schema.getRow(rowIndex).getColumn(colIndex).getCell(cell).getData());
      }
   }

   void initializeTableResources(List<List<string>*>& tableRecords, long tableCapacity)
   {
      for (long rowNumber = 0; rowNumber < tableCapacity; rowNumber++)
      {
         List<string>* record = new ArrayList<string>();

         tableRecords.add(record);
      }
   }

   void retrieveRowToTable(List<List<string>*>& tableRecords, List<List<string>*>* rowData)
   {
      for (long column = 0; column < rowData->getSize(); column++)
      {
         for (long record = 0; record < tableRecords.getSize(); record++)
         {
            string data = rowData->get(column)->get(record);

            tableRecords.get(record)->add(data);
         }
      }
   }

   void createRecords(string& table, List<List<string>*>* tableRecords, long cellWidth, long rowIndex, long maxColsCountInRow)
   {
      for (long completedRow = 0; completedRow < tableRecords->getSize(); completedRow++)
      {
         List<string>* rowToCreate = tableRecords->get(completedRow);
         SchemaFormatter formatter = SchemaFormatter();

         if (rowIndex == schema.rowsCount() - 1 && completedRow == tableRecords->getSize() - 1)
         {
            TableRecord* cells = new TableRecord(rowToCreate, cellWidth, space, maxColsCountInRow, false, true);
            table += formatter.createRecord(cells);
         }
         else
         {
            TableRecord* cells = new TableRecord(rowToCreate, cellWidth, space, maxColsCountInRow, false, false);
            table += formatter.createRecord(cells);
         }

      }
   }
};