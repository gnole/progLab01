//
// Created by perfest on 17.09.2020.
//

#ifndef TEMPLATE_STUDENT_H
#define TEMPLATE_STUDENT_H


#include <vector>
#include <iostream>
#include <any>

struct Student {
  std::string Name;
  std::any Group;
  std::any Avg;
  std::any Debt;
};


#endif  // TEMPLATE_STUDENT_H