// Copyright 2020
#include "parser_printer.hpp"
#include <iostream>
// int argc, char* argv[]

#define DEBUG

int main()
{
#ifndef DEBUG
  if (argc > 2)
  {
    std::cout << "Too many arguments" << std::endl;
    exit(0);
  }
  if (argc == 1)
  {
    std::cout << "You need to enter a name of file" << std::endl;
    exit(0);
  }
    std::string fileName(argv[1]);
#endif

  std::vector<Student> students;

#ifdef DEBUG
  const std::string fileName = "file.json";
#endif
  try {
      students = parser(fileName);
  }
  catch (const std::exception& ex)
  {
      std::cerr << ex.what();
      return 1;
  }
  printer(students, std::cout);
  return 0;
}
