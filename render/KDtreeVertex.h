#ifndef RAY_TRACER_KDTREEVERTEX
#define RAY_TRACER_KDTREEVERTEX

#include "../geometry/object.h"
#include <vector>
#include <algorithm>
#include "../geometry/point.h"
#include "../geometry/vector.h"
#include "../geometry/ray.h"
#include "../geometry/tetragon.h"

const double KDtreeVertexEPS = 1E-9;


/*
 *  SAH:
 *  f(x) = C_t + C_i *   (SA_L(x) * N_L(x) + SA_R(x) * N_R(X))   / SA_parent
 *  C_t -- стоимость пересечения луча с самим боксом
 *  C_i -- стоимость пересечения луча и обьекта
 *  SA_L, SA_R -- площади левого и правого узлов
 *  N_L, N_R -- количество элементов
 *  SA_parent -- площадь отца
 */

const double SAH_C_t = 2;
const double SAH_C_i = 1;


const int intersectArgs[4][3] = {
    {0, 0, -1},
    {0, 1, -1},
    {1, 1, -1},
    {1, 0, -1}
};

class KDtreeVertex{
public:
    // elements = nullptr, if vertex isn't a leaf
    // in this way splitAxis and position must be defined
    // another way they contain no interest
    std::vector<Object*>* elements;
    int splitAxis;
    double position;
    // sorry, it's of course for higher speed
    Point minPos, maxPos;
    KDtreeVertex *l, *r;

    explicit KDtreeVertex(std::vector<Object*>& objects, bool fixed=0, 
                            const Point& min_=Point(), const Point& max_=Point(), int step=0);
    ~KDtreeVertex();

    void print();
    double vertexArea(const Vector& dimentions);
    double f(double x, int axis, int n_l, int n_r, bool=0);

    

    bool intersect(const Ray&) const;
    Point construct_(const int x, const int y, const int z) const;
    Point construct(const int* args, int shift, int far) const;
};

#endif
