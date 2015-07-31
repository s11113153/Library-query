//
//  main.cpp
//  Library-query
//
//  Created by 許佑任 on 2015/7/30.
//  Copyright (c) 2015年 許佑任. All rights reserved.
//

#include <iostream>
#include "DataBase.h"
#include "LibrarySystem.h"
#include <string>


using namespace std;

void callback(int status, string msg);
void log(string tag, string msg);

const string TABLE_PATH = "/Users/xuyouren/Desktop/book_db.dat";

DataBase::Build *build;

int main(int argc, const char * argv[]) {
  build = DataBase::load(TABLE_PATH, callback);  
  LibrarySystem::launch(*build);
  return EXIT_SUCCESS;
}


void log(string tag, string msg) {
  fprintf(stdout, "%s: %s", tag.c_str(), msg.c_str());
}

void callback(int status, string msg) {
  std::cerr << msg;
  if (status == EXIT_FAILURE) exit(EXIT_FAILURE);
}
