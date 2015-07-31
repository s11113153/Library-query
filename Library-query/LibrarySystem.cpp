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
    Command command = getCommand(inputs.at(0));
    proces(command, inputs, inputs.size() - 1);
    inputs.clear();
  }
}

void LibrarySystem::printlnLog(string msg) {
  fprintf(stdout, "%s\n", msg.c_str());
}

void LibrarySystem::proces(
        LibrarySystem::Command command, vector<string> inputs, size_t size) {

  if (command == None) {
    printlnLog("開頭指令錯誤!!");
    return;
  }

  if (command == Display && size == LibrarySystem::CommandFormatSize::Display) {
    for (int i = 0; i < DataBase::table.book_record.size(); i++) {
      Book book = DataBase::table.book_record[i];
      fprintf(stdout,
        "book_id=%d, authors=%s, book_name=%s, publisher=%s, year=%d, place=%s\n",
        book.book_id, book.authors.c_str(), book.book_name.c_str(), book.publisher.c_str(),
        book.year, book.place.c_str()
      );
    }
  }

  if (command == Insert && size == LibrarySystem::CommandFormatSize::Insert) {
  }
}

