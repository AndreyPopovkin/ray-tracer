#include "KDtreeVertex.h"

KDtreeVertex::KDtreeVertex(std::vector<Object*>& objects, 
                            bool fixed, const Point& min_, const Point& max_, int step) {
    //std::cout << objects.size() << "\n";
    /*
    if (step > 3) {
        // ends splitting process
        elements = new std::vector<Object*>(objects);
        l = r = nullptr;
        return;
    }
    */
    if (objects.size() == 0 && !fixed) throw 1;
    if (!fixed) {
        minPos.setx(objects[0]->minPos(0));
        minPos.sety(objects[0]->minPos(1));
        minPos.setz(objects[0]->minPos(2));
        maxPos.setx(objects[0]->maxPos(0));
        maxPos.sety(objects[0]->maxPos(1));
        maxPos.setz(objects[0]->maxPos(2));
        for (auto item : objects) {
            minPos.setx(std::min(minPos.getx(), item->minPos(0)));
            minPos.sety(std::min(minPos.gety(), item->minPos(1)));
            minPos.setz(std::min(minPos.getz(), item->minPos(2)));
            maxPos.setx(std::max(maxPos.getx(), item->maxPos(0)));
            maxPos.sety(std::max(maxPos.gety(), item->maxPos(1)));
            maxPos.setz(std::max(maxPos.getz(), item->maxPos(2)));
        }
    } else {
        minPos = min_;
        maxPos = max_;
    }
    //std::cout << "{" << objects.size() << ' ' << step << '\n' << minPos << "\n" << maxPos << "}\n";
    double bestReit = 0;
    double bestPos = 0;
    int bestAxis = -1;
    int size = objects.size();
    std::vector<double> objMinPos;
    std::vector<double> objMaxPos;
    objMinPos.reserve(size);
    objMaxPos.reserve(size);
    for (int axis = 0; axis <= 2; ++axis) {
        objMinPos.clear();
        objMaxPos.clear();
        for (auto item : objects) {
            objMinPos.push_back(item->minPos(axis));
            objMaxPos.push_back(item->maxPos(axis));
        }
        std::sort(objMinPos.begin(), objMinPos.end());
        std::sort(objMaxPos.begin(), objMaxPos.end());
        int ptr1 = 0;
        int ptr2 = 0;
        for (ptr1 = 1; ptr1 < size; ++ptr1) {
            while (objMinPos[ptr1] - KDtreeVertexEPS > objMaxPos[ptr2]) ++ptr2;
            //std::cout << "! " << objMinPos[ptr1] - KDtreeVertexEPS << ' ' << objMinPos[ptr1] << ' ' << minPos.getx() << "\n";
            double tmpF = f(objMinPos[ptr1] - KDtreeVertexEPS, axis, ptr1, size - ptr2);
            //std::cout << ptr1 << ' ' << ptr2 << ' ' << tmpF << "\n";
            if (bestAxis == -1 || bestReit + KDtreeVertexEPS > tmpF) {
                bestAxis = axis;
                bestPos = objMinPos[ptr1] - KDtreeVertexEPS;
                bestReit = tmpF;
            }
        }
    }
    //std::cout << bestReit << ' ' << SAH_C_i * size << "\n";
    if (bestAxis == -1 || bestReit >= SAH_C_i * size) {
        // ends splitting process
        elements = new std::vector<Object*>(objects);
        l = r = nullptr;
    } else {
        // continue
        elements = nullptr;
        splitAxis = bestAxis;
        position = bestPos;
        std::vector<Object*> left;
        std::vector<Object*> right;
        left.reserve(size);
        right.reserve(size);
        for (auto item : objects) {
            if (item->minPos(bestAxis) < bestPos)
                left.push_back(item);
            if (item->maxPos(bestAxis) > bestPos)
                right.push_back(item);
        }
        Point leftMax = maxPos;
        Point rightMin = minPos;
        leftMax.setByAxis(bestAxis, bestPos);
        rightMin.setByAxis(bestAxis, bestPos);
        l = new KDtreeVertex(left, 1, minPos, leftMax, step + 1);
        r = new KDtreeVertex(right, 1, rightMin, maxPos, step + 1);
    }
}

double KDtreeVertex::vertexArea(const Vector& dimentions) {
    return dimentions.getx() * dimentions.gety() * dimentions.getz();
            /*
            dimentions.getx() * dimentions.gety() +
            dimentions.gety() * dimentions.getz() +
            dimentions.getz() * dimentions.getx();
            */
}

double KDtreeVertex::f(double x, int axis, int n_l, int n_r, bool check) {
    // f(x) = C_t + C_i *   (SA_L(x) * N_L(x) + SA_R(x) * N_R(X))   / SA_parent
    Point minCenter = minPos;
    Point maxCenter = maxPos;
    //std::cout << n_l << ' ' << n_r << "\n";
    minCenter.setByAxis(axis, x);
    maxCenter.setByAxis(axis, x);
    //std::cout << minCenter << ' ' << maxCenter << "\n";
    //std::cout << minPos << ' ' << maxPos << "\n";
    double leftCost = vertexArea(maxCenter - minPos) * n_l;
    double rightCost = vertexArea(maxPos - minCenter) * n_r;
    if (check) {
        std::cout << "!!! " << n_l << ' ' << n_r << "\n";
        std::cout << leftCost << ' ' << rightCost << ' ' << (vertexArea(maxCenter - minPos) + vertexArea(maxPos - minCenter)) << "\n";
    }
    //std::cout << (maxPos - minCenter) << "\n";
    //std::cout << leftCost << ' ' << rightCost << ' ' << (vertexArea(maxCenter - minPos) + vertexArea(maxPos - minCenter)) << "\n";
    if (rightCost < 0) throw 1;
    return SAH_C_t + SAH_C_i * (leftCost + rightCost) / 
        (vertexArea(maxCenter - minPos) + vertexArea(maxPos - minCenter));
}

void KDtreeVertex::print() {
    std::cout << "----begin\n";
    std::cout << minPos << ' ' << maxPos << "\n";
    std::cout << position << ' ' << splitAxis << ' ' << l << ' ' << r << "\n";
    if (elements != nullptr) std::cout << elements->size() << "\n";
    else std::cout << "0\n";
    std::cout << "----end\n";
}

Point KDtreeVertex::construct(const int* args, int shift, int far) const {
    return construct_(
        ( (args[(shift + 0) % 3] == -1) ? far : args[(shift + 0) % 3] ),
        ( (args[(shift + 1) % 3] == -1) ? far : args[(shift + 1) % 3] ),
        ( (args[(shift + 2) % 3] == -1) ? far : args[(shift + 2) % 3] )
    );
}

Point KDtreeVertex::construct_(const int x, const int y, const int z) const {
    return Point(
            (x ? minPos.getx() : maxPos.getx()),
            (y ? minPos.gety() : maxPos.gety()),
            (z ? minPos.getz() : maxPos.getz())
        );
}

bool KDtreeVertex::intersect(const Ray& ray) const {
    Tetragon tr;
    for (int far = 0; far <= 1; ++far) {
        for (int shift = 0; shift < 3; ++shift) {
            for (int i = 0; i < 4; ++i)
                tr.p[i] = construct(intersectArgs[i], shift, far);
            if (tr.intersect(ray).second) {
                return 1;
            }
        }
    }

    return 0;
}