#include "KDtree.h"

void KDtree::build(std::vector<Object*>& objects) {
    auto begin = std::chrono::high_resolution_clock::now();

    root = new KDtreeVertex(objects);

    auto end = std::chrono::high_resolution_clock::now();
    std::cerr << "KDtree built during " << 
        std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() / 1000. << "s" << std::endl;

    //root->print();
}

std::pair<Ray, bool> KDtree::traceRay(const Ray& ray, const KDtreeVertex* vert) {
    if (vert == nullptr) {
        vert = root;
    }
    if (vert == nullptr) throw 1;

    // test for intersecting with bounding-box
    if (!(vert->intersect(ray))) return {Ray(), 0};

    // leaf, intersect
    if (vert->elements != nullptr) {
        double distToNearest2 = -1;
        Ray answer;
        for (const auto& item : (*(vert->elements))) {        
            auto intersection = item->intersect(ray);
            if (intersection.second) {
                double distance2 = (intersection.first.source - ray.source).len2();
                if (distToNearest2 < 0 || distance2 < distToNearest2) {
                    distToNearest2 = distance2;
                    answer = intersection.first;
                }
            }
        }
        counter.fetch_add(vert->elements->size());
        return {answer, distToNearest2 >= 0};
    }

    // no leaf, check direction
    if (ray.direction.valAlongAxis(vert->splitAxis) > 0) {
        auto lans = traceRay(ray, vert->l);
        if (lans.second) return lans;
        return traceRay(ray, vert->r);
    } else {
        auto rans = traceRay(ray, vert->r);
        if (rans.second) return rans;
        return traceRay(ray, vert->l);
    }
}