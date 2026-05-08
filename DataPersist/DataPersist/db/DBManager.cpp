#include "DBManager.h"
#include <fstream>
#include <sstream>

bool DBManager::Load(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open())
        return false;

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        Sample s;
        std::string statusStr;
        std::getline(ss, s.id,         ',');
        std::getline(ss, s.name,       ',');
        std::getline(ss, statusStr,    ',');
        std::getline(ss, s.created_at, ',');
        std::getline(ss, s.updated_at);
        s.status = StringToStatus(statusStr);
        store_[s.id] = s;
    }
    return true;
}

bool DBManager::Save(const std::string& filepath) const {
    std::ofstream file(filepath);
    if (!file.is_open())
        return false;

    file << "id,name,status,created_at,updated_at\n";
    for (const auto& [id, s] : store_)
        file << s.id << ',' << s.name << ',' << StatusToString(s.status)
             << ',' << s.created_at << ',' << s.updated_at << '\n';
    return true;
}

bool DBManager::Add(const Sample& sample) {
    if (store_.count(sample.id))
        return false;
    store_[sample.id] = sample;
    return true;
}

std::optional<Sample> DBManager::Get(const std::string& id) const {
    auto it = store_.find(id);
    if (it == store_.end())
        return std::nullopt;
    return it->second;
}

bool DBManager::Update(const Sample& sample) {
    auto it = store_.find(sample.id);
    if (it == store_.end())
        return false;
    it->second = sample;
    return true;
}

bool DBManager::Delete(const std::string& id) {
    return store_.erase(id) > 0;
}

std::vector<Sample> DBManager::GetAll() const {
    std::vector<Sample> result;
    result.reserve(store_.size());
    for (const auto& [id, s] : store_)
        result.push_back(s);
    return result;
}
