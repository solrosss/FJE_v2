#ifndef TREE_VISUALIZER_H
#define TREE_VISUALIZER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "visualizer.h"

class TreeVisualizer : public Visualizer {
public:
    void visualize(JSONIterator& jsonIterator, const IconFamily& iconFamily) const override {
        std::vector<std::string> stack;
        while (jsonIterator.hasNext()) {
            auto [path, node] = jsonIterator.next();
            std::vector<std::string> pathParts = split(path, '/');
            std::string name = pathParts.back();
            bool isLastChild = isLast(pathParts, path);

            while (stack.size() > pathParts.size()) {
                stack.pop_back();
            }

            if (stack.size() < pathParts.size()) {
                stack.push_back(isLastChild ? "    " : "│   ");
            }

            for (const auto& part : stack) {
                std::cout << part;
            }

            if (!pathParts.empty()) {
                std::cout << (isLastChild ? "└─" : "├─");
            }

            if (node.is_object() || node.is_array()) {
                std::cout << iconFamily.getIntermediateIcon() << name << std::endl;
            } else {
                std::cout << iconFamily.getLeafIcon() << name << ": " << node << std::endl;
            }
        }
    }

private:
    std::vector<std::string> split(const std::string& str, char delimiter) const {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    bool isLast(const std::vector<std::string>& pathParts, auto path) const {
        // 判断当前路径是否是父节点的最后一个子节点
        if (pathParts.empty()) {
            return true;
        }
        std::string parentPath = join(pathParts.begin(), pathParts.end() - 1, '/');
        for (const auto& item : jsonItems) {
            if (item.first.find(parentPath) == 0 && item.first != path) {
                return false;
            }
        }
        return true;
    }

    std::string join(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end, char delimiter) const {
        std::ostringstream result;
        if (begin != end) {
            result << *begin++;
        }
        while (begin != end) {
            result << delimiter << *begin++;
        }
        return result.str();
    }

    std::vector<std::pair<std::string, json>> jsonItems;
};

#endif // TREE_VISUALIZER_H
