#pragma once
#include <string>

enum class SampleStatus { created, in_process, completed, defect };

std::string StatusToString(SampleStatus status);
SampleStatus StringToStatus(const std::string& str);

struct Sample {
    std::string id;
    std::string name;
    SampleStatus status = SampleStatus::created;
    std::string created_at;
    std::string updated_at;
};
