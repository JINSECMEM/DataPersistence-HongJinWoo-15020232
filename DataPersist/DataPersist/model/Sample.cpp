#include "Sample.h"

std::string StatusToString(SampleStatus status) {
    switch (status) {
    case SampleStatus::created:    return "created";
    case SampleStatus::in_process: return "in_process";
    case SampleStatus::completed:  return "completed";
    case SampleStatus::defect:     return "defect";
    }
    return "created";
}

SampleStatus StringToStatus(const std::string& str) {
    if (str == "in_process") return SampleStatus::in_process;
    if (str == "completed")  return SampleStatus::completed;
    if (str == "defect")     return SampleStatus::defect;
    return SampleStatus::created;
}
