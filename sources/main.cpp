
#include "../../.hunter/_Base/9a3594a/020aca2/48401e9/Install/include/nlohmann/json.hpp"
#include "parser_printer.hpp"
#include "student.hpp"
#include <string>

int main(int argc, char* argv[]) {
  std::vector<ns::person> students;
  const std::string fileName = "/home/oleg/CLionProjects/untitled6/file.json";
  students = PARSER(fileName);
  PRINTER(students);
  return 0;


//#ifndef DEBUG
//    if (argc > 2)
//    {
//      std::cout << "Too many arguments" << std::endl;
//      exit(0);
//    }
//    if (argc == 1)
//    {
//      std::cout << "You need to enter a name of file" << std::endl;
//      exit(0);
//    }
//    std::string fileName(argv[1]);
//#endif
//
//    std::vector<ns::person> students;
//
//#ifdef DEBUG
//    const std::string fileName = "file.json";
//#endif
//
//    students = PARSER(fileName);
//    PRINTER(students);
//
//    return 0;
}