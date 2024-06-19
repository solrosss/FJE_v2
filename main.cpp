#include <iostream>
#include <string>
#include "fje.h"
#include "icon_family.h"

int main(int argc, char* argv[]) {
    std::string json_file, style, icon_family;

    if (argc != 7) {
        std::cerr << "Usage: " << argv[0] << " -f <json file> -s <style> -i <icon family>" << std::endl;
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i++)
    {
        if (argv[i] == "-f")
        {
            json_file = argv[++i];
        }
        else if (argv[i] == "-s")
        {
            style = argv[i + 1];
        }
        else if (argv[i] == "-i")
        {
            icon_family = argv[i + 1];
        }
        else
        {
            std::cerr << "Unknown argument: " << argv[i] << std::endl;
            return EXIT_FAILURE;
        }
    }

    IconFamily iconFamily;
    if (icon_family == "pokerface")
        iconFamily.setIcon("♢", "♤");
    else 
        iconFamily.setIcon(" ", " ");

    try {
        FJE fje(json_file, style, iconFamily);
        fje.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
