//
// Created by oleg on 16.10.2020.
//
#include "student.hpp"

#include "parser_printer.hpp"

bool ns::operator==(const ns::person &lhs, const ns::person &rhs) {
  return (equal(lhs.debt, rhs.debt) && lhs.avg == rhs.avg &&
          equal(lhs.group, rhs.group) && lhs.name == rhs.name);
}