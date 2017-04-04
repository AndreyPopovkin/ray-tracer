#ifndef RAY_TRACER_PARCER
#define RAY_TRACER_PARCER

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "point.h"
#include <chrono>
#include "polygonG.h"
#include "triangle.h"

class Parcer{
    string filename;
public:
    Parcer(string filename): filename(filename) {}
    std::vector<PolygonG> parce() {
        auto begin = std::chrono::high_resolution_clock::now();
        
        std::vector<PolygonG> ans;
        std::vector<Point> p;
        ifstream in;
        in.open(filename);

        string str;
        std::vector<Point> locP;

        while (std::getline(in, str)) {
            if (str.size() == 0) continue;
            if (str.substr(0, 2) == "v ") {
                str = str.substr(2);
                istringstream stin(str);
                double x, y, z;
                stin >> x >> y >> z;
                p.emplace_back(x, y, z);
            } else if (str.substr(0, 2) == "f ") {
                //std::cout << "!\n";
                int oldptr = 2;
                int ptr = 2;
                locP.clear();
                while (ptr + 3 < (int)str.size()) {
                    while (ptr < (int)str.size() && str[ptr] != '/') ++ptr;
                    locP.push_back(p[std::atoi(str.substr(oldptr, ptr - oldptr).c_str()) - 1]);
                    while (ptr < (int)str.size() && str[ptr] != ' ') ++ptr;
                    ++ptr;
                    oldptr = ptr;
                }
                ans.emplace_back(std::move(locP));
            }
        }

        in.close();

        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "all " << ans.size() << " polygons loaded ";
        std::cerr << "during " << 
            std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() / 1000. << "s" << std::endl;

        return ans;
    }
};

#endif
