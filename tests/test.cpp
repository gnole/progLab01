// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include <fstream>
#include <nlohmann/json.hpp>

#include "parser_printer.hpp"

using nlohmann::json;

TEST(Parser, PARSER) {
  json j =
      "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Ivanov Petr\",\n"
      "      \"group\": \"1\",\n"
      "      \"avg\": \"4.25\",\n"
      "      \"debt\": null\n"
      "    }\n,"
      "    {\n"
      "      \"name\": \"Sidorov Ivan\",\n"
      "      \"group\": 31,\n"
      "      \"avg\": 4,\n"
      "      \"debt\": \"C++\"\n"
      "    }\n,"
      "    {\n"
      "      \"name\": \"Pertov Nikita\",\n"
      "      \"group\": \"IU8-31\",\n"
      "      \"avg\": 3.33,\n"
      "      \"debt\": [\"C++\", \"Linux\", \"Network\"]\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 3\n"
      "  }\n"
      "}\n"_json;

  ns::person student_0;
  student_0.name = "Ivanov Petr";
  student_0.group = "1";
  student_0.avg = "4.25";
  student_0.debt = "null";

  ns::person student_1;
  student_1.name = "Sidorov Ivan";
  student_1.group = "31";
  student_1.avg = "4";
  student_1.debt = "C++";

  ns::person student_2;
  student_2.name = "Pertov Nikita";
  student_2.group = "IU8-31";
  student_2.avg = "3.33";
  student_2.debt = "3 items";

  ASSERT_EQ(student_0, PARSER(j.at("items").at(0)));
  ASSERT_EQ(student_1, PARSER(j.at("items").at(1)));
  ASSERT_EQ(student_2, PARSER(j.at("items").at(2)));

  j = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": [\"Ivanov Petr\", \"Andrew\"],\n"
      "      \"group\": \"1\",\n"
      "      \"avg\": \"4.25\",\n"
      "      \"debt\": null\n"
      "    }\n,"
      "    {\n"
      "      \"name\": \"Sidorov Ivan\",\n"
      "      \"group\": 31,\n"
      "      \"avg\": [4, \"1.25\"],\n"
      "      \"debt\": \"C++\"\n"
      "    }\n,"
      "    {\n"
      "      \"name\": \"Pertov Nikita\",\n"
      "      \"group\": [\"IU8-31\", 5],\n"
      "      \"avg\": 3.33,\n"
      "      \"debt\": [\"C++\", \"Linux\", \"Network\"]\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 3\n"
      "  }\n"
      "}\n"_json;

  ASSERT_ANY_THROW(PARSER(j.at("items")[0]));
  ASSERT_ANY_THROW(PARSER(j.at("items")[1]));
  ASSERT_ANY_THROW(PARSER(j.at("items")[2]));
}

// TEST(Parser, get_vector_from_json) {
//  json j =
//      "{\n"
//      "  \"items\": [\n"
//      "    {\n"
//      "      \"name\": \"Ivanov Petr\",\n"
//      "      \"group\": \"1\",\n"
//      "      \"avg\": \"4.25\",\n"
//      "      \"debt\": null\n"
//      "    }\n,"
//      "    {\n"
//      "      \"name\": \"Sidorov Ivan\",\n"
//      "      \"group\": 31,\n"
//      "      \"avg\": 4,\n"
//      "      \"debt\": \"C++\"\n"
//      "    }\n,"
//      "    {\n"
//      "      \"name\": \"Pertov Nikita\",\n"
//      "      \"group\": \"IU8-31\",\n"
//      "      \"avg\": 3.33,\n"
//      "      \"debt\": [\"C++\", \"Linux\", \"Network\"]\n"
//      "    }\n"
//      "  ],\n"
//      "  \"_meta\": {\n"
//      "    \"count\": 3\n"
//      "  }\n"
//      "}\n"_json;
//
//  Student student_0;
//  student_0.Name = "Ivanov Petr";
//  student_0.Group = "1";
//  student_0.Avg = "4.25";
//  student_0.Debt = "null";
//
//  Student student_1;
//  student_1.Name = "Sidorov Ivan";
//  student_1.Group = "31";
//  student_1.Avg = "4";
//  student_1.Debt = "C++";
//
//  Student student_2;
//  student_2.Name = "Pertov Nikita";
//  student_2.Group = "IU8-31";
//  student_2.Avg = "3.33";
//  student_2.Debt = "3 items";
//
//  std::vector students_vec{student_0, student_1, student_2};
//  ASSERT_EQ(students_vec, get_vector_from_json(j));
//}
//
// TEST(Parser, meta_count) {
//  json j =
//      "{\n"
//      "  \"items\": [\n"
//      "    {\n"
//      "      \"name\": \"Ivanov Petr\",\n"
//      "      \"group\": \"1\",\n"
//      "      \"avg\": \"4.25\",\n"
//      "      \"debt\": null\n"
//      "    }\n,"
//      "    {\n"
//      "      \"name\": \"Sidorov Ivan\",\n"
//      "      \"group\": 31,\n"
//      "      \"avg\": 4,\n"
//      "      \"debt\": \"C++\"\n"
//      "    }\n,"
//      "    {\n"
//      "      \"name\": \"Pertov Nikita\",\n"
//      "      \"group\": \"IU8-31\",\n"
//      "      \"avg\": 3.33,\n"
//      "      \"debt\": [\"C++\", \"Linux\", \"Network\"]\n"
//      "    }\n"
//      "  ],\n"
//      "  \"_meta\": {\n"
//      "    \"count\": 3\n"
//      "  }\n"
//      "}\n"_json;
//
//  Student student_0;
//  student_0.Name = "Ivanov Petr";
//  student_0.Group = "1";
//  student_0.Avg = "4.25";
//  student_0.Debt = "null";
//
//  Student student_1;
//  student_1.Name = "Sidorov Ivan";
//  student_1.Group = "31";
//  student_1.Avg = "4";
//  student_1.Debt = "C++";
//
//  Student student_2;
//  student_2.Name = "Pertov Nikita";
//  student_2.Group = "IU8-31";
//  student_2.Avg = "3.33";
//  student_2.Debt = "3 items";
//
//  std::vector students_vec{student_0, student_1, student_2};
//
//  ASSERT_EQ(true, is_valid_meta(j, students_vec));
//
//  students_vec.push_back(student_0);
//  ASSERT_EQ(false, is_valid_meta(j, students_vec));
}