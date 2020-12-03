// Copyright 2018 Your Name <your_email>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <parser_printer.hpp>
#include <fstream>
#include <print_any.hpp>


bool operator == (const Student& s1, const Student& s2) {
  if (s1.Name != s2.Name) return false;
  if (s1.Group.type() != s2.Group.type()) {
    return false;
  } else {
    std::stringstream equality_str1;
    std::stringstream equality_str2;
    equality_str1 = print_any(s1.Group);
    equality_str2 = print_any(s2.Group);
    if (equality_str1.str() != equality_str2.str()) return false;
  }
  if (s1.Avg.type() != s2.Avg.type()) {
    return false;
  } else {
    std::stringstream equality_str1;
    std::stringstream equality_str2;
    equality_str1 = print_any(s1.Avg);
    equality_str2 = print_any(s2.Avg);
    if (equality_str1.str() != equality_str2.str()) return false;
  }
  if (s1.Debt.type() != s2.Debt.type()) {
    return false;
  } else {
    std::stringstream equality_str1;
    std::stringstream equality_str2;
    equality_str1 = print_any(s1.Debt);
    equality_str2 = print_any(s2.Debt);
    if (equality_str1.str() != equality_str2.str()) return false;
  }
  return true;
}

TEST(TEST, parser_printer_test) {
  using json = nlohmann::json;
  json j = {
      { "items", {
      {
          {"name", "Ivanov Petr"},
          {"group", "1"},
          {"avg", "4.25"},
          {"debt", nullptr}
      },
      {
          {"name", "Sidorov Ivan"},
          {"group", 31},
          {"avg", 4},
          {"debt", "C++"}
      },
      {
          {"name", "Pertov Nikita"},
          {"group", "IU8-31"},
          {"avg", 3.33},
          {"debt", {"C++", "Linux", "Network"}},
      }
                }
      },
      {"_meta", {"count", 3}}
  };
  std::ofstream json_file("file.json");
  json_file << j << std::endl;

  std::vector<Student> expectedStudents;
  Student stud_1 = {"Ivanov Petr", std::string("1"),
                    std::string("4.25"), false};
  expectedStudents.push_back(stud_1);
  Student stud_2 = {"Sidorov Ivan", 31, 4,
                    std::string("C++")};
  expectedStudents.push_back(stud_2);
  std::vector<std::string> debt_s3 = {"C++", "Linux", "Network"};
  Student stud_3 = {"Pertov Nikita", std::string("IU8-31"),
                    3.33, debt_s3};
  expectedStudents.push_back(stud_3);

  std::vector<Student> parsed_students;
  parsed_students = parser("file.json");
  EXPECT_TRUE(parsed_students == expectedStudents);

  // WRITING EXPECTING FILE
  std::ofstream expectedFile("expectedFile.txt");
  expectedFile << "| name          | group  | avg  | debt          |\n"; // 1
  expectedFile << "|---------------|--------|------|---------------|\n"; // 2
  expectedFile << "| Ivanov Petr   | 1      | 4.25 | null          |\n"; // 3
  expectedFile << "|---------------|--------|------|---------------|\n"; // 4
  expectedFile << "| Sidorov Ivan  | 31     | 4    | C++           |\n"; // 5
  expectedFile << "|---------------|--------|------|---------------|\n"; // 6
  expectedFile << "| Pertov Nikita | IU8-31 | 3.33 | 3 items       |\n"; // 7
  expectedFile << "|---------------|--------|------|---------------|\n"; // 8
  expectedFile.close();

  // WRITING PARSED FILE
  std::ofstream outFile("parsedFile.txt");
    printer(parsed_students, outFile);
  outFile.close();

  // EQUATION
  std::ifstream ex_file("expectedFile.txt");
  std::ifstream pa_file("parsedFile.txt");
  while (pa_file) {
    std::string ex_str;
    std::string pr_str;
    ex_file >> ex_str;
    pa_file >> pr_str;
    EXPECT_TRUE(ex_str == pr_str);
  }
}

