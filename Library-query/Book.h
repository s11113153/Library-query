//
//  Book.h
//  Library-query
//
//  Created by 許佑任 on 2015/7/30.
//  Copyright (c) 2015年 許佑任. All rights reserved.
//

#ifndef __Library_query__Book__
#define __Library_query__Book__

#include <stdio.h>

struct Book {
  uint16_t book_id;
  std::string authors;
  std::string book_name;
  std::string publisher;
  uint16_t    year;
  std::string place;

  struct FiledIndex {
    static const int FiledSize = 6;
    static const int book_id = 0;
    static const int authors = 1;
    static const int book_name = 2;
    static const int publisher = 3;
    static const int year = 4;
    static const int place = 5;
  };
};

#endif /* defined(__Library_query__Book__) */
