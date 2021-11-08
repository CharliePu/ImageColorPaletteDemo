#ifndef MEDIANCUTMETHOD_H
#define MEDIANCUTMETHOD_H

#include <quantizationmethod.h>

struct BoundaryNode
{
    QVector<QColor> colors;
    short cutDim;
    int range;
};

class MedianCutMethod: public QuantizationMethod
{
public:
    MedianCutMethod();

private:
    BoundaryNode createNode(QVector<QColor> colors);

    // QuantizationMethod interface
protected:
    void process() override;
};

#endif // MEDIANCUTMETHOD_H
