#include <vector>
#include <map>
#include <sstream>

namespace mustache {
    namespace config {
        bool mustacheRendering = true;
    }
    namespace utility {
        void replaceAll(std::string& str, const std::string& from, const std::string& to) {
            if(from.empty())
                return;
            size_t start_pos = 0;
            while((start_pos = str.find(from, start_pos)) != std::string::npos) {
                str.replace(start_pos, from.length(), to);
                start_pos += to.length();
            }
        }
    }
    std::vector<std::map<std::string, std::string>> storage;
    void set(const char* mustache, const char* content) {
        std::map<std::string, std::string> m;
        m[mustache] = std::string(content);
        storage.push_back(m);
        m.clear();
    }
    std::string renderMustache(std::string content) {
        std::string debug;
        std::string newContent;
        std::istringstream f(content);
        std::string line;    
        while (std::getline(f, line)) {
            for (const std::map<std::string, std::string> map : storage) {
                for (const auto& [key, value] : map) {
                    utility::replaceAll(line, "{{" + key + "}}", value);
                }
            }
            newContent += line + "\n";
        }
        return newContent;
    }
}