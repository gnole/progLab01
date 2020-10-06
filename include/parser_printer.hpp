//
// Created by oleg on 02.10.2020.
//

#ifndef PARSER_PRINTER_HPP_
#define PARSER_PRINTER_HPP_

#include <any>
#include <iostream>
#include <vector>
#include "student.hpp"

  std::string print_any(const std::any &object);
  std::vector<ns::person> PARSER(const std::string &fileName);
  void PRINTER(const std::vector<ns::person> &students);


#endif // PARSER_PRINTER_HPP_
