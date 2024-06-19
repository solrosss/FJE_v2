#ifndef ICON_FAMILY_H
#define ICON_FAMILY_H

#include <string>

class IconFamily {
public:
    void setIcon(std::string intermediate_icon, std::string leaf_icon) {
        intermediateIcon = intermediate_icon;
        leafIcon = leaf_icon;
    }

    const std::string& getIntermediateIcon() const {
        return intermediateIcon;
    }

    const std::string& getLeafIcon() const {
        return leafIcon;
    }

private:
    std::string intermediateIcon;
    std::string leafIcon;
};

#endif // ICON_FAMILY_H
