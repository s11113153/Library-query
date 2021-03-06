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

    if (!proces(getCommand(inputs))) {
      break;
    }
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

int LibrarySystem::getBookFieldIndex(string key) {
  if (key == "book_id") return Book::FiledIndex::book_id;
  if (key == "authors") return Book::FiledIndex::authors;
  if (key == "book_name") return Book::FiledIndex::book_name;
  if (key == "publisher") return Book::FiledIndex::publisher;
  if (key == "year") return Book::FiledIndex::year;
  if (key == "place") return Book::FiledIndex::place;
  return -1;
}

// TODO: - [filter, query] not implement
bool LibrarySystem::proces(LibrarySystem::CommandContent cc) {
  size_t size = cc.content.size();

  if (cc.command == None) {
    printlnLog("開頭指令錯誤!!");
    return true;
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
    return true;
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
    printlnLog("insert: [" + to_string(book.book_id) + "] successful!!!");
    return true;
  }

  if (cc.command == Delete && size == CommandContent::CheckFormatSize::Delete) {
    for (int i = 0; i < DataBase::table.book_record.size(); i++) {
      int book_id = atoi(cc.content[0].c_str());
      if (DataBase::table.book_record[i].book_id == book_id) {
          DataBase::table.book_record.erase(DataBase::table.book_record.begin() + i);
          printlnLog("Delete: [" + to_string(book_id) + "] Success!!");
          break;
      }
    }
    return true;
  }

  if (cc.command == Modify && size == CommandContent::CheckFormatSize::Modify) {
    int book_id = atoi(cc.content[0].c_str());
    string key = cc.content[1];
    string value = cc.content[2];
    int bookFieldIndex = getBookFieldIndex(key);
    string msg_ok = "modify successful!!!";
    string msg_no = "modify failure, key not fonud !!!";

    for (int i = 0; i < DataBase::table.book_record.size(); i++) {
      if (DataBase::table.book_record[i].book_id == book_id) {
        switch (bookFieldIndex) {
          case Book::FiledIndex::book_id:
            DataBase::table.book_record[i].book_id = atoi(value.c_str());
            printlnLog(msg_ok);
            return true;
          case Book::FiledIndex::book_name:
            DataBase::table.book_record[i].book_name = value;
            printlnLog(msg_ok);
            return true;
          case Book::FiledIndex::authors:
            DataBase::table.book_record[i].authors = value;
            printlnLog(msg_ok);
            return true;
          case Book::FiledIndex::publisher:
            DataBase::table.book_record[i].publisher = value;
            printlnLog(msg_ok);
            return true;
          case Book::FiledIndex::year:
            DataBase::table.book_record[i].year = atoi(value.c_str());
            printlnLog(msg_ok);
            return true;
          case Book::FiledIndex::place:
            DataBase::table.book_record[i].place = value;
            printlnLog(msg_ok);
            return true;
          default: {
            printlnLog(msg_no);
            return true;
          }
        }
      }
    }
  }

  if (cc.command == Copy && size == CommandContent::CheckFormatSize::Copy) {
    DataBase::table.tmp.clear();
    DataBase::table.tmp = DataBase::table.book_record;
    printlnLog("copy successful!!!");
    return true;
  }

  if (cc.command == Save && size == CommandContent::CheckFormatSize::Save) {
    std::fstream writeFstream;
    char split_char = '#';
    writeFstream.open(DataBase::table.path  , std::ios::out);
    if (!writeFstream) {
      printlnLog("write book_db.dat is failure !!!");
      return true;
    }
    for (int i = 0; i < DataBase::table.book_record.size(); i++) {
      Book book = DataBase::table.book_record[i];
      writeFstream << book.book_id    << split_char;
      writeFstream << book.authors    << split_char;
      writeFstream << book.book_name  << split_char;
      writeFstream << book.publisher  << split_char;
      writeFstream << book.year       << split_char;
      writeFstream << book.place      << endl;
    }
    writeFstream.close();
    printlnLog("save is successful !!!");
    return true;
  }

  if (cc.command == Filter && size == CommandContent::CheckFormatSize::Filter) {
    string key  = cc.content[0];
    string value = cc.content[1];
    DataBase::table.tmp2.clear();

    for (int i = 0; i < DataBase::table.tmp.size(); i++) {
      bool isSearch = false;
      Book book = DataBase::table.tmp[i];
      int bookFieldIndex = getBookFieldIndex(key);

      switch (bookFieldIndex) {
        case Book::FiledIndex::book_id: {
          string strId = to_string(book.book_id);
          if (strId.find(value) != std::string::npos)
              isSearch = true;
          break;
        }

        case Book::FiledIndex::book_name:
          if (book.book_name.find(value) != std::string::npos)
              isSearch = true;
          break;

        case Book::FiledIndex::authors:
          if (book.authors.find(value) != std::string::npos)
              isSearch = true;
          break;

        case Book::FiledIndex::publisher:
          if (book.publisher.find(value) != std::string::npos)
              isSearch = true;
          break;

        case Book::FiledIndex::year: {
          string strYear = to_string(book.year);
          if (strYear.find(value) != std::string::npos)
              isSearch = true;
          break;
        }

        case Book::FiledIndex::place:
          if (book.place.find(value) != std::string::npos)
              isSearch = true;
          break;

        default:
          break;
      }
      if (isSearch) {
        DataBase::table.tmp2.push_back(book);
      }
    }

    DataBase::table.tmp = DataBase::table.tmp2;
    return true;
  }

  if (cc.command == Query && size == CommandContent::CheckFormatSize::Query) {
    for (int i = 0; i < DataBase::table.tmp.size(); i++) {
      Book book = DataBase::table.tmp[i];
      fprintf(stdout,
        "book_id=%d, authors=%s, book_name=%s, publisher=%s, year=%d, place=%s\n",
        book.book_id, book.authors.c_str(), book.book_name.c_str(), book.publisher.c_str(),
        book.year, book.place.c_str()
      );
    }
    return true;
  }

  if (cc.command == Quit && size == CommandContent::CheckFormatSize::Quit) {
    return false;
  }

  printlnLog("command parameter is error!!!");
  return true;
}

