//
// Created by oleg on 14.09.2020.
//

#ifndef STUDENT_HPP_
#define STUDENT_HPP_
#include <iostream>
#include "../../.hunter/_Base/9a3594a/020aca2/48401e9/Install/include/nlohmann/json.hpp"
#include <any>
namespace ns{
  struct person {
      std::string name;
      std::any group;
      double avg;
      std::any debt;
  };
}

#endif //STUDENT_HPP_
