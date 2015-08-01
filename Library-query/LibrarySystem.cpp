//
//  LibrarySystem.cpp
//  Library-query
//
//  Created by 許佑任 on 2015/7/30.
//  Copyright (c) 2015年 許佑任. All rights reserved.
//

#include "LibrarySystem.h"

map<string, LibrarySystem::Command> LibrarySystem::commands = {
  {"display",   LibrarySystem::Display },
  {"insert" ,   LibrarySystem::Insert  },
  {"delete" ,   LibrarySystem::Delete  },
  {"modify" ,   LibrarySystem::Modify  },
  {"copy"   ,   LibrarySystem::Copy    },
  {"filter" ,   LibrarySystem::Filter  },
  {"query"  ,   LibrarySystem::Query   },
  {"save"   ,   LibrarySystem::Save    },
  {"quit"   ,   LibrarySystem::Quit    }
};

void LibrarySystem::launch(DataBase::Build build) {
  std::string readLine;

  while (std::getline(std::cin, readLine)) {
    char split_char = ' ';
    vector<string> inputs;
    std::istringstream split(readLine);
    for (; std::getline(split, readLine, split_char); inputs.push_back(readLine));

    if (inputs.empty()) {
      printlnLog("不要輸入空白鍵!!");
      continue;
    }
    proces(getCommand(inputs));
    inputs.clear();
  }
}


LibrarySystem::CommandContent LibrarySystem::getCommand(vector<string> inputs) {
  CommandContent cc;
  cc.command = None;

  if (inputs.empty())
      return cc;

  map<string, Command>::iterator it = commands.find(inputs.at(0));
  if (it != commands.end()) {
    cc.command = it->second;
  }

  if (inputs.size() > 1) {
    inputs.erase(inputs.begin());
    cc.content = inputs;
  }
  return cc;
}


void LibrarySystem::printlnLog(string msg) {
  fprintf(stdout, "%s\n", msg.c_str());
}

void LibrarySystem::proces(LibrarySystem::CommandContent cc) {
  size_t size = cc.content.size();

  if (cc.command == None) {
    printlnLog("開頭指令錯誤!!");
    return;
  }

  if (cc.command == Display && size == CommandContent::CheckFormatSize::Display) {
    for (int i = 0; i < DataBase::table.book_record.size(); i++) {
      Book book = DataBase::table.book_record[i];
      fprintf(stdout,
        "book_id=%d, authors=%s, book_name=%s, publisher=%s, year=%d, place=%s\n",
        book.book_id, book.authors.c_str(), book.book_name.c_str(), book.publisher.c_str(),
        book.year, book.place.c_str()
      );
    }
    return;
  }

  if (cc.command == Insert && size == CommandContent::CheckFormatSize::Insert) {
    Book book;
    book.book_id   = atoi(cc.content[Book::FiledIndex::book_id].c_str());
    book.year      = atoi(cc.content[Book::FiledIndex::year].c_str());
    book.authors   = cc.content[Book::FiledIndex::authors];
    book.book_name = cc.content[Book::FiledIndex::book_name];
    book.publisher = cc.content[Book::FiledIndex::publisher];
    book.place     = cc.content[Book::FiledIndex::place];
    DataBase::table.book_record.push_back(book);
    return;
  }

  if (cc.command == Delete && size == CommandContent::CheckFormatSize::Delete) {
    for (int i = 0; i < DataBase::table.book_record.size(); i++) {
      int book_id = atoi(cc.content[Book::FiledIndex::book_id].c_str());
      if (DataBase::table.book_record[i].book_id == book_id) {
          DataBase::table.book_record.erase(DataBase::table.book_record.begin() + i);
          printlnLog("Delete: [" + to_string(book_id) + "] Success!!");
          break;
      }
    }
    return;
  }
}

