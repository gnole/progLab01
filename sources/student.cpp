// Copyright 2018 Your Name <your_email>

#include <header.hpp>
using nlohmann::json;

void from_json(const json& j, Student& s) {
    j.at("name").get_to(s.Name);
    j.at("group").get_to(s.Group);
    j.at("avg").get_to(s.Avg);
    j.at("debt").get_to(s.Debt);
}

int main() {
    //...
    std::ifstream file{jsonPath};
    if (!file) {
        throw std::runtime_error{"unable to open json: " + jsonPath};
    }

    json data;
    file >> data;

    std::vector<Student> students;
    for (auto const& student : data.at("items")) {
        students.push_back(Student{student});
    }
    //...
}