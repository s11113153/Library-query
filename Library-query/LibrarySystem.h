//
//  LibrarySystem.h
//  Library-query
//
//  Created by 許佑任 on 2015/7/30.
//  Copyright (c) 2015年 許佑任. All rights reserved.
//

#ifndef __Library_query__LibrarySystem__
#define __Library_query__LibrarySystem__

#include <stdio.h>
#include "DataBase.h"
#include <fstream>
#include <map>

class LibrarySystem {
public:
  enum Command {
    Display, Insert, Delete, Modify, Copy, Filter, Query, Save, Quit, None
  };
  static void launch(DataBase::Build build);
  
private:
  static map<string, Command> commands;

  struct CommandContent {
    Command command;
    vector<string> content;

    struct CheckFormatSize {
      static const int Display = 0;
      static const int Insert  = 6;
      static const int Delete  = 1;
      static const int Modify  = 3;
      static const int Copy    = 0;
      static const int Filter  = 2;
      static const int Query   = 0;
      static const int Save    = 0;
      static const int Quit    = 0;
    };
  };

  static CommandContent getCommand(vector<string> inputs);

  static void printlnLog(string msg);
  static bool proces(CommandContent cc);
  static int getBookFieldIndex(string key);
};


#endif /* defined(__Library_query__LibrarySystem__) */
