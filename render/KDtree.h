#ifndef RAY_TRACER_KDTREE
#define RAY_TRACER_KDTREE

#include "../geometry/object.h"
#include "KDtreeVertex.h"
#include <vector>
#include <chrono>
#include "../geometry/ray.h"
#include <atomic>

class KDtree{
public:
    KDtreeVertex* root;
    std::atomic<int> counter;
    void build(std::vector<Object*>& objects);
    std::pair<Ray, bool> traceRay(const Ray&, const KDtreeVertex* = nullptr);
    ~KDtree();
};

#endif
