#pragma once

#include<string>
#include"List.h"
#include"ArrayList.h"
#include"TableRecord.h"

using namespace std;

class SchemaFormatter
{
public:

   string createRecord(TableRecord* recordData)
   {
      RecordInfo* info = new RecordInfo(recordData);

      string recordBody = generateRecordBody(info);

      string border = generateBorder(info);

      return assembleRecord(border, recordBody, info);
   }

private:
   const string SEPARATOR = "+";
   const string ROW_SEPARATOR = "\r\n";
   const string ROW_FILLER = "-";
   const string COL_FILLER = "|";
   const string SPACING = " ";

   class RecordInfo
   {
   public:
      RecordInfo(TableRecord* record)
      {
         this->space = record->getSpace();
         this->tableRecord = record->getTableRecord();
         this->colsCount = record->getSize();
         this->totalColsCount = record->getTotalColsCount();
         this->contentWidth = record->getCellWidth() * record->getTotalColsCount(); // ok
         this->totalCellWidth = record->getCellWidth() * (record->getTotalColsCount() / colsCount); // ok
         this->colsBorders = colsCount - 1; // ok
         this->voidColsBorders = record->getTotalColsCount() - 1; // ok
         this->cellSpaces = space * colsCount; // ok
         this->voidCellSpaces = space * record->getTotalColsCount(); // ok
         this->width = contentWidth + voidCellSpaces + voidColsBorders;
         this->closingCell = record->isClossingCell();
         this->header = record->isHeader();
      }

      List<string>* getTableRecord()
      {
         return tableRecord;
      }

      long getColsCount()
      {
         return colsCount;
      }

      long getTotalColsCount()
      {
         return this->totalColsCount;
      }

      long getContentWidth()
      {
         return contentWidth;
      }

      long getTotalCellWidth()
      {
         return totalCellWidth;
      }

      long getColsBorders()
      {
         return colsBorders;
      }

      long getVoidColsBorders()
      {
         return voidColsBorders;
      }

      long getCellSpaces()
      {
         return cellSpaces;
      }

      long getVoidCellSpaces()
      {
         return voidCellSpaces;
      }

      long getSpace()
      {
         return this->space;
      }

      long getWidth()
      {
         return width;
      }

      bool isClosingCell()
      {
         return closingCell;
      }

      bool isHeader()
      {
         return header;
      }

   private:
      List<string>* tableRecord;

      long colsCount;
      long totalColsCount;
      long contentWidth;
      long totalCellWidth;
      long colsBorders;
      long voidColsBorders;
      long cellSpaces;
      long voidCellSpaces;
      long space;
      long width;

      bool closingCell;
      bool header;
   };

   long calcWhiteSpaces(string str, long width)
   {
      return width - str.length();
   }

   List<long>* calcPaddings(RecordInfo* info)
   {
      List<long>* paddings = new ArrayList<long>();

      for (long cell = 0; cell < info->getColsCount(); cell++)
      {
         long cellPadding = calcWhiteSpaces(info->getTableRecord()->get(cell), info->getTotalCellWidth() + (info->getVoidColsBorders() - info->getColsBorders()));
         paddings->add(cellPadding);
      }

      return paddings;
   }

   string generateContentBody(List<long>* paddings, RecordInfo* info)
   {
      string contentBody = "";

      long colsBordersCounter = info->getColsBorders();

      for (long cell = 0; cell < info->getColsCount(); cell++)
      {
         long cellPadding = paddings->get(cell);
         string cellSpace = repeat(SPACING, (info->getSpace() / 2) + (info->getTotalColsCount() - info->getColsCount()));

         bool isPaddingEven = true;
         if (cellPadding % 2 != 0)
         {
            cellPadding++;
            isPaddingEven = false;
         }

         string content = info->getTableRecord()->get(cell);
         string alignedContent;

         if (info->isHeader())
         {
            string leftPadding = repeat(SPACING, (cellPadding / 2));
            string rightPadding = (!isPaddingEven) ? repeat(SPACING, ((cellPadding - 1) / 2)) : repeat(SPACING, (cellPadding / 2));

            alignedContent = (leftPadding + content + rightPadding);
         }
         else
         {
            alignedContent = (!isPaddingEven) ? (content + repeat(SPACING, cellPadding - 1)) : (content + repeat(SPACING, cellPadding));
         }

         contentBody += (cellSpace + alignedContent + cellSpace);

         if (colsBordersCounter != 0)
         {
            contentBody += COL_FILLER;
            colsBordersCounter--;
         }
      }

      return contentBody;
   }

   string generateRecordBody(RecordInfo* info)
   {
      List<long>* paddings = calcPaddings(info);

      string contentBody = generateContentBody(paddings, info);

      string rowBody = (COL_FILLER + contentBody + COL_FILLER) + ROW_SEPARATOR;

      if (info->isHeader())
      {
         rowBody = generateHeaderRowBody(contentBody, rowBody, info);
      }

      return rowBody;
   }

   string generateBorder(RecordInfo* info)
   {
      string borderBody = repeat(ROW_FILLER, info->getWidth());

      return (SEPARATOR + borderBody + SEPARATOR) + ROW_SEPARATOR;
   }

   string generateHeaderRowBody(string contentBody, string rowBody, RecordInfo* info)
   {
      string verticalPadding = repeat(SPACING, contentBody.length());
      string verticalPaddingBody = (COL_FILLER + verticalPadding + COL_FILLER) + ROW_SEPARATOR;

      verticalPaddingBody = replaceAllCharsFromTo(rowBody, verticalPaddingBody, COL_FILLER);

      return (verticalPaddingBody + rowBody + verticalPaddingBody);
   }

   string assembleRecord(string border, string recordBody, RecordInfo* info)
   {
      return (info->isClosingCell()) ? (border + recordBody + border) : (border + recordBody);
   }

   string repeat(string symbol, long count)
   {
      string result;
      if (count != 0)
         result = symbol;

      for (int i = 0; i < count - 1; i++)
      {
         result += symbol;
      }

      return result;
   }

   string replaceAllCharsFromTo(string from, string to, string character)
   {
      /* must be the same in [from] and [to] ! */
      long size = from.length();

      for (long i = 0; i < size; i++)
      {
         if (from[i] == character.c_str()[0])
         {
            to[i] = character.c_str()[0];
         }
      }

      return to;
   }
};