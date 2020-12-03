// Copyright 2020 "typeperfest" <perfect2111@gmail.com>
#include "parser_printer.hpp"
#include "print_any.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <nlohmann/json.hpp>
#include <string>

std::vector<Student> parser(const std::string& fileName)
{
  std::ifstream file(fileName);
  if (!file)
  {
    std::cout << "There is no such file with that name"
              << std::endl;
    throw std::runtime_error("file isn't exist");
  }

  using json = nlohmann::json;

  json data;
  file >> data;

  std::vector<Student> students;
  for (const auto& student : data.at("items")) {
    Student currentStudent;
    //NAME
    currentStudent.Name = student.at("name");
    //END_NAME

    //GROUP
    if (student.at("group").is_string())
    {
      std::string for_cast = static_cast<std::string>(student.at("group"));
     currentStudent.Group = for_cast;
    } else if (student.at("group").is_number_integer()) {
      currentStudent.Group = static_cast<int>(student.at("group"));
    }
    //END_GROUP

    // AVG
    if (student.at("avg").is_string()) {
      std::string for_cast = static_cast<std::string>(student.at("avg"));
      currentStudent.Avg = for_cast;
    } else if (student.at("avg").is_number_integer()) {
      currentStudent.Avg = static_cast<int>(student.at("avg"));
    } else if (student.at("avg").is_number_float()) {
      currentStudent.Avg = static_cast<double>(student.at("avg"));
    }
    // END_AVG

    // DEBT
    if (student.at("debt").is_string())
    {
      std::string for_cast = static_cast<std::string>(student.at("debt"));
      currentStudent.Debt = for_cast;
    } else if (student.at("debt").is_array()) {
      currentStudent.Debt =
          static_cast<std::vector<std::string>>(student.at("debt"));
    } else if (student.at("debt").is_null()) {
      bool Flag = false;
      currentStudent.Debt = Flag;
    }
    // END_DEBT

    // student.at("name").get_to(currentStudent.Name);
    // student.at("group").get_to(currentStudent.Group);
    // student.at("avg").get_to(currentStudent.Avg);
    // student.at("debt").get_to(currentStudent.Debt);
    students.push_back(currentStudent);
  }
  return students;
}

std::ostream& printer(const std::vector<Student>& students, std::ostream& out) {
  // FIRST STRING
  out << '|';
  out << std::setfill(' ') << " name" << std::setw(11);
  out << '|';
  out << std::setfill(' ') << " group" << std::setw(3);
  out << '|';
  out << std::setfill(' ') << " avg" << std::setw(3);
  out << '|';
  out << std::setfill(' ') << " debt" << std::setw(11);
  out << '|';
  out << std::endl;

  // SECOND STRING
  out << '|';
  out << std::setfill('-') << std::setw(16);
  out << '|';
  out << std::setfill('-') << std::setw(9);
  out << '|';
  out << std::setfill('-') << std::setw(7);
  out << '|';
  out << std::setfill('-') << std::setw(16);
  out << '|';
  out << std::endl;

  // LAST STRINGS
  for (const auto& student : students) {
    // TOP STRING
    out << '|' << ' ' << std::setfill(' ')
              << std::left << std::setw(14)
              << student.Name << '|' << ' ';
    out << std::setfill(' ') << std::setw(7)
              << print_any(student.Group).str()
              << '|' << ' ';
    out << std::setfill(' ') << std::setw(5)
              << print_any(student.Avg).str() << '|' << ' ';
    out << std::setfill(' ') << std::setw(14)
              << print_any(student.Debt).str()
              << '|';
    out << std::endl;

    // BOTTOM STRING
    out << '|';
    out << std::setfill('-') << std::right << std::setw(16);
    out << '|';
    out << std::setfill('-') << std::setw(9);
    out << '|';
    out << std::setfill('-') << std::setw(7);
    out << '|';
    out << std::setfill('-') << std::setw(16);
    out << '|';
    out << std::endl;
  }
  return out;
}
