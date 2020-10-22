//
// Created by oleg on 14.09.2020.
//

#ifndef STUDENT_HPP_
#define STUDENT_HPP_

#include <any>
#include <iostream>
//#include <nlohmann/json.hpp>

#include "/root/.hunter/_Base/9a3594a/3181922/48401e9/Install/include/nlohmann/json.hpp"

struct person {
  std::string name;
  std::any group;
  double avg;
  std::any debt;
  friend bool operator==(const person& lhs, const person& rhs);
};

#endif  // STUDENT_HPP_
