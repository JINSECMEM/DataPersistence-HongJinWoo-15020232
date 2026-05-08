#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "../db/DBManager.h"

static std::string now_str() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_s(&tm, &t);
    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S");
    return ss.str();
}

int main() {
    const std::string DB_PATH = "samples.db";
    DBManager db;

    // --- 프로그램 시작: DB 로드 ---
    if (db.Load(DB_PATH))
        std::cout << "[Load] " << DB_PATH << " loaded.\n";
    else
        std::cout << "[Load] No existing DB. Starting fresh.\n";

    // --- 런타임 CRUD ---
    std::string ts = now_str();
    db.Add({ "S001", "AlphaWafer", SampleStatus::created,    ts, ts });
    db.Add({ "S002", "BetaWafer",  SampleStatus::in_process, ts, ts });
    db.Add({ "S003", "GammaWafer", SampleStatus::defect,     ts, ts });

    if (auto s = db.Get("S002")) {
        s->status     = SampleStatus::completed;
        s->updated_at = now_str();
        db.Update(*s);
    }

    db.Delete("S003");

    std::cout << "\n[Samples]\n";
    for (const auto& s : db.GetAll())
        std::cout << "  " << s.id << " | " << s.name
                  << " | " << StatusToString(s.status) << "\n";

    // --- 프로그램 종료: DB 저장 ---
    if (db.Save(DB_PATH))
        std::cout << "\n[Save] " << DB_PATH << " saved.\n";
    else
        std::cout << "\n[Save] Failed to save DB.\n";

    return 0;
}
