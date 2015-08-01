//
//  DataBase.cpp
//  Library-query
//
//  Created by 許佑任 on 2015/7/30.
//  Copyright (c) 2015年 許佑任. All rights reserved.
//

#include "DataBase.h"


// ------------------------------------------------
// MARK: - Database Table Book
vector<Book>  DataBase::Table::book_record = {};
vector<Book>  DataBase::Table::tmp = {};
vector<Book>  DataBase::Table::tmp2 = {};
string        DataBase::Table::path = "";
// ------------------------------------------------



// -----------------------------------------------------------------------------------------
// MARK: - Build class func
DataBase::Build * build_instance = NULL;

bool pushToBookRecord(string bookData[], size_t size) {
  bool b = (size == Book::FiledIndex::FiledSize) ? true : false;
  if (!b) return false;

  Book book;
  book.book_id   = std::stoi(bookData[Book::FiledIndex::book_id]);
  book.year      = std::stoi(bookData[Book::FiledIndex::year]);
  book.authors   = bookData[Book::FiledIndex::authors];
  book.place     = bookData[Book::FiledIndex::place];
  book.publisher = bookData[Book::FiledIndex::publisher];
  book.book_name = bookData[Book::FiledIndex::book_name];
  DataBase::table.book_record.push_back(book);
  return true;
}

DataBase::Build::Build(string table_path, void(*callback)(int, std::string msg)) {
  std::fstream inFstream;
  inFstream.open(table_path, std::ios::in);
  if (!inFstream) {
    callback(EXIT_FAILURE, "load path is failure!!!");
  }
  char c[1024];

  while (inFstream.getline(c, sizeof(c), '\n')) {
    char split_char = '#';
    std::string bookData[Book::FiledIndex::FiledSize];
    std::string readLine = string(c);
    std::istringstream split(readLine);

    for (int index = 0;
         std::getline(split, readLine, split_char);
         bookData[index++] = readLine
    );

    if (!pushToBookRecord(bookData, sizeof(bookData) / sizeof(bookData[0]))) {
      callback(EXIT_FAILURE, "格式不符合\n");
    }
  }
}
// -----------------------------------------------------------------------------------------



// ---------------------------------------------------------------------------------
// MARK: - Database class static func
DataBase::Build * DataBase::load(string table_path, void (*callback)(int, string)) {
  if (build_instance == NULL)
      build_instance = new Build(table_path, callback);

  table.path = table_path;
  callback(EXIT_SUCCESS, "載入完成\n");
  return build_instance;
}
// ---------------------------------------------------------------------------------


