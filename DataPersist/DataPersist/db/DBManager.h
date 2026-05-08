#pragma once
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include "../model/Sample.h"

class DBManager {
public:
    bool Load(const std::string& filepath);
    bool Save(const std::string& filepath) const;

    bool                   Add(const Sample& sample);
    std::optional<Sample>  Get(const std::string& id) const;
    bool                   Update(const Sample& sample);
    bool                   Delete(const std::string& id);
    std::vector<Sample>    GetAll() const;

private:
    std::unordered_map<std::string, Sample> store_;
};
