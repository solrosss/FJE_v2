#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <string>
#include "json_iterator.h"
#include "icon_family.h"

class Visualizer {
public:
    virtual void visualize(JSONIterator& jsonIterator, const IconFamily& iconFamily) const = 0;
    virtual ~Visualizer() = default;
};

#endif // VISUALIZER_H
