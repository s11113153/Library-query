//
//  DataBase.h
//  Library-query
//
//  Created by 許佑任 on 2015/7/30.
//  Copyright (c) 2015年 許佑任. All rights reserved.
//

#ifndef __Library_query__DataBase__
#define __Library_query__DataBase__

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include "Book.h"
#include <vector>
#include <sstream>

using namespace std;

class DataBase {
  private:
    DataBase();
  public:
    static class Table {
      public:
        static string path;
        static vector<Book> book_record;
        static vector<Book> tmp;
        static vector<Book> tmp2;
    } table;

    class Build {
      public:
        Build(std::string table_path, void(*callback)(int, std::string));
      private:
        Build * build_instance;
    };
  public:
    static Build * load(std::string, void(*callback)(int, std::string));
};

#endif /* defined(__Library_query__DataBase__) */
