#ifndef JSON_ITERATOR_H
#define JSON_ITERATOR_H

#include <string>
#include <stack>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JSONIterator {
public:
    JSONIterator(const json& jsonData) {
        stack.push({jsonData, ""});
    }

    bool hasNext() const {
        return !stack.empty();
    }

    std::pair<std::string, json> next() {
        if (stack.empty()) {
            throw std::out_of_range("No more elements");
        }
        auto [current, path] = stack.top();
        stack.pop();
        if (current.is_object()) {
            for (auto it = current.rbegin(); it != current.rend(); ++it) {
                stack.push({it.value(), path + "/" + it.key()});
            }
        } else if (current.is_array()) {
            for (int i = current.size() - 1; i >= 0; --i) {
                stack.push({current[i], path + "[" + std::to_string(i) + "]"});
            }
        }
        return {path, current};
    }

private:
    std::stack<std::pair<json, std::string>> stack;
};

#endif // JSON_ITERATOR_H
