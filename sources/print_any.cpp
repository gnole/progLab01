// Copyright 2020 typeperfest
#include <print_any.hpp>
#include <iomanip>
#include <vector>

std::stringstream print_any(const std::any& object)
{
  std::stringstream out_str;
  if (object.type() == typeid(std::string))
  {
    out_str << std::any_cast<std::string>(object);
  } else if (object.type() == typeid(int)) {
    out_str << std::to_string(std::any_cast<int>(object));
  } else if (object.type() == typeid(double)) {
    out_str << std::setprecision(3)
            << std::any_cast<double>(object);
  } else if (object.type() == typeid(std::vector<std::string>)) {
    std::vector<std::string> str_vec
        = std::any_cast<std::vector<std::string>>(object);
    int size = str_vec.size();
    if (size > 1)
    {
      out_str << std::to_string(size) << " items";
    } else if (size == 1) {
      out_str << str_vec[0];
    }
  } else if (object.type() == typeid(bool)) {
    out_str << "null";
  } else {
    std::bad_cast ex;
    throw ex;
  }
  return out_str;
}
