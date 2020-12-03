// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_PARSER_PRINTER_HPP_
#define INCLUDE_PARSER_PRINTER_HPP_

#include <any>
#include <iostream>
#include <string>
#include <vector>
#include "./include_student.h"

std::vector<Student> parser(const std::string& fileName);
std::ostream& printer(const std::vector<Student>& students, std::ostream& out);

#endif // INCLUDE_PARSER_PRINTER_HPP_
