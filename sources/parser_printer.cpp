//
// Created by oleg on 02.10.2020.
//
#include "parser_printer.hpp"

#include <fstream>
#include <iomanip>
#include <string>
#include <typeinfo>

#include "/root/.hunter/_Base/9a3594a/3181922/48401e9/Install/include/nlohmann/json.hpp"
#include "any"
//#include
//"../../.hunter/_Base/9a3594a/020aca2/48401e9/Install/include/nlohmann/json.hpp"
#include "student.hpp"

bool equal(const std::any& lhs, const std::any& rhs) {
  if (lhs.type() != rhs.type())
    return false;

  else if (lhs.type() == typeid(std::string))
    return std::any_cast<std::string>(lhs) == std::any_cast<std::string>(rhs);

  else if (lhs.type() == typeid(int))
    return std::any_cast<int>(lhs) == std::any_cast<int>(rhs);

  else if (lhs.type() == typeid(float))
    return std::any_cast<float>(lhs) == std::any_cast<float>(rhs);

  else if (lhs.type() == typeid(bool))
    return "null";

  else if (lhs.type() == typeid(std::vector<std::string>))
    return std::any_cast<std::vector<std::string>>(lhs) ==
           std::any_cast<std::vector<std::string>>(rhs);

  else
    throw std::runtime_error("comparison of any unimplemented for type");
}

std::vector<ns::person> PARSER(const std::string& fileName) {
  std::ifstream file(fileName);
  if (!file) {
    std::cout << "There is no such file with that name" << std::endl;
    throw std::runtime_error("file isn't exist");
  }

  using json = nlohmann::json;

  json data;
  file >> data;

  std::vector<ns::person> students;
  for (const auto& student : data.at("items")) {
    ns::person currentStudent;
    // NAME
    currentStudent.name = student.at("name");
    // END_NAME

    // GROUP
    if (student.at("group").is_string()) {
      currentStudent.group = static_cast<std::string>(student.at("group"));
    } else if (student.at("group").is_number_integer()) {
      currentStudent.group = static_cast<int>(student.at("group"));
    }
    // END_GROUP

    // AVG
    if (student.at("avg").is_string()) {
      std::size_t offset = 0;
      std::string avgScoreRead = student.at("avg");
      currentStudent.avg = std::stod(avgScoreRead, &offset);
    } else if (student.at("avg").is_number_integer()) {
      currentStudent.avg = static_cast<float>(student.at("avg"));
    } else if (student.at("avg").is_number_float()) {
      currentStudent.avg = student.at("avg");
    }
    // END_AVG

    // DEBT
    if (student.at("debt").is_string()) {
      currentStudent.debt = static_cast<std::string>(student.at("debt"));
    } else if (student.at("debt").is_array()) {
      currentStudent.debt =
          static_cast<std::vector<std::string>>(student.at("debt"));
    } else if (student.at("debt").is_null()) {
      bool Flag = false;
      currentStudent.debt = Flag;
    }
    // END_DEBT

    students.push_back(currentStudent);
  }
  return students;
}

std::string print_any(const std::any& object) {
  std::string out_str;
  if (object.type() == typeid(std::string)) {
    out_str = std::any_cast<std::string>(object);
  } else if (object.type() == typeid(int)) {
    out_str = std::to_string(std::any_cast<int>(object));
    // out_str = (std::any_cast<json>(object)).get<int>();
  } else if (object.type() == typeid(float)) {
    out_str = std::any_cast<float>(object);
  } else if (object.type() == typeid(std::vector<std::string>)) {
    std::vector<std::string> str_vec =
        std::any_cast<std::vector<std::string>>(object);
    int size = str_vec.size();
    if (size > 1) {
      out_str = std::to_string(size) + " items";
    } else if (size == 1) {
      out_str = str_vec[0];
    }
  } else if (object.type() == typeid(bool)) {
    out_str = "null";
  } else {
    std::bad_cast ex;
    throw ex;
  }

  return out_str;
}

void PRINTER(const std::vector<ns::person>& students) {
  // FIRST STRING
  std::cout << '|';
  std::cout << std::setfill(' ') << " name" << std::setw(11);
  std::cout << '|';
  std::cout << std::setfill(' ') << " group" << std::setw(3);
  std::cout << '|';
  std::cout << std::setfill(' ') << " avg" << std::setw(3);
  std::cout << '|';
  std::cout << std::setfill(' ') << " debt" << std::setw(11);
  std::cout << '|';
  std::cout << std::endl;

  // SECOND STRING
  std::cout << '|';
  std::cout << std::setfill('-') << std::setw(16);
  std::cout << '|';
  std::cout << std::setfill('-') << std::setw(9);
  std::cout << '|';
  std::cout << std::setfill('-') << std::setw(7);
  std::cout << '|';
  std::cout << std::setfill('-') << std::setw(16);
  std::cout << '|';
  std::cout << std::endl;

  // LAST STRINGS
  for (const auto& student : students) {
    // TOP STRING
    std::cout << '|' << ' ' << std::setfill(' ') << std::left << std::setw(14)
              << student.name << '|' << ' ';
    std::cout << std::setfill(' ') << std::setw(7) << print_any(student.group)
              << '|' << ' ';
    std::cout << std::setfill(' ') << std::setw(5) << student.avg << '|' << ' ';
    std::cout << std::setfill(' ') << std::setw(14) << print_any(student.debt)
              << '|';
    std::cout << std::endl;

    // BOTTOM STRING
    std::cout << '|';
    std::cout << std::setfill('-') << std::right << std::setw(16);
    std::cout << '|';
    std::cout << std::setfill('-') << std::setw(9);
    std::cout << '|';
    std::cout << std::setfill('-') << std::setw(7);
    std::cout << '|';
    std::cout << std::setfill('-') << std::setw(16);
    std::cout << '|';
    std::cout << std::endl;
  }
}
