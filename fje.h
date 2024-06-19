#ifndef FJE_H
#define FJE_H

#include <fstream>
#include <memory>
#include <stdexcept>
#include "json_iterator.h"
#include "visualizer.h"
#include "tree_visualizer.h"
#include "rectangle_visualizer.h"
#include "icon_family.h"

class FJE {
public:
    FJE(const std::string& jsonFile, const std::string& style, const IconFamily& iconFamily)
        : iconFamily(iconFamily) {
        std::ifstream file(jsonFile);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file");
        }
        file >> jsonData;
        jsonIterator = std::make_unique<JSONIterator>(jsonData);
        visualizer = getVisualizer(style);
    }

    void run() const {
        visualizer->visualize(*jsonIterator, iconFamily);
    }

private:
    std::unique_ptr<Visualizer> getVisualizer(const std::string& style) const {
        if (style == "tree") {
            return std::make_unique<TreeVisualizer>();
        } else if (style == "rectangle") {
            return std::make_unique<RectangleVisualizer>();
        } else {
            throw std::invalid_argument("Unsupported style");
        }
    }

    json jsonData;
    std::unique_ptr<JSONIterator> jsonIterator;
    std::unique_ptr<Visualizer> visualizer;
    const IconFamily& iconFamily;
};

#endif // FJE_H
