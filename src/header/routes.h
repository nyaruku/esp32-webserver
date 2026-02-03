#include <vector>
#include <map>
#include <sstream>
#include <string>

namespace routes {
    std::vector<std::map<std::string, std::string>> storage;

    void set(std::string path, std::string content) {
        std::map<std::string, std::string> m;
        m[path] = std::string(content);
        storage.push_back(m);
        m.clear();
    }

    std::string get(std::string path) {
        for (const std::map<std::string, std::string> map : storage) {
            for (const auto& [key, value] : map) {
                if (path == key) {
                    return value;
                }
            }
        }
        return "";
    }
}