#ifndef RAY_TRACER_PARCER
#define RAY_TRACER_PARCER

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "point.h"
#include "triangle.h"

class Parcer{
    string filename;
public:
    Parcer(string filename): filename(filename) {}
    std::pair<std::vector<Triangle>, std::vector<Tetragon> > parce() {
        std::vector<Triangle> ans;
        std::vector<Tetragon> ans2;
        std::vector<Point> p;
        ifstream in;
        in.open(filename);

        string str;

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
                int p1, p2, p3, p4;
                int oldptr = 2;
                int ptr = 2;
                while (ptr < (int)str.size() && str[ptr] != '/') ++ptr;
                p1 = std::atoi(str.substr(oldptr, ptr - oldptr).c_str());
                while (ptr < (int)str.size() && str[ptr] != ' ') ++ptr;
                ++ptr;
                oldptr = ptr;
                while (ptr < (int)str.size() && str[ptr] != '/') ++ptr;
                p2 = std::atoi(str.substr(oldptr, ptr - oldptr).c_str());
                while (ptr < (int)str.size() && str[ptr] != ' ') ++ptr;
                ++ptr;
                oldptr = ptr;
                while (ptr < (int)str.size() && str[ptr] != '/') ++ptr;
                p3 = std::atoi(str.substr(oldptr, ptr - oldptr).c_str());
                while (ptr < (int)str.size() && str[ptr] != ' ') ++ptr;
                if (ptr + 3 >= (int)str.size())
                    ans.emplace_back(p[p1 - 1], p[p2 - 1], p[p3 - 1]);
                else {  
                    ++ptr;
                    oldptr = ptr;
                    while (ptr < (int)str.size() && str[ptr] != '/') ++ptr;
                    p4 = std::atoi(str.substr(oldptr, ptr - oldptr).c_str());
                    ans2.emplace_back(p[p1 - 1], p[p2 - 1], p[p3 - 1], p[p4 - 1]);
                }
                //cout << ans.back() << "\n";
            }
        }

        in.close();
        return {ans, ans2};
    }
};

#endif
