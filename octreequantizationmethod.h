#ifndef OCTREEQUANTIZATIONMETHOD_H
#define OCTREEQUANTIZATIONMETHOD_H

#include "quantizationmethod.h"

struct OctreeNode
{
    long long red;
    long long green;
    long long blue;
    int count;

    OctreeNode *children[8];

    OctreeNode(): red(0), green(0), blue(0), count(0), children() {}

    ~OctreeNode()
    {
        for (OctreeNode *node : children)
        {
            if (node)
            {
                delete node;
            }
        }
    }
};

class OctreeQuantizationMethod : public QuantizationMethod
{
public:
    OctreeQuantizationMethod();

private:
    void addNode(OctreeNode *current, int r, int g, int b, int depth);

    void getNodesAtDepth(OctreeNode *current, int depth, QList<OctreeNode*> &list);

    // QuantizationMethod interface
protected:
    void process() override;
};

#endif // OCTREEQUANTIZATIONMETHOD_H
