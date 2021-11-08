#ifndef UNIFORMQUANTIZATIONMETHOD_H
#define UNIFORMQUANTIZATIONMETHOD_H

#include "quantizationmethod.h"

struct ColorGroup
{
    long long r;
    long long g;
    long long b;
    int count;
    ColorGroup(): r(0), g(0), b(0), count(0) {}
};

class UniformQuantizationMethod : public QuantizationMethod
{
public:
    UniformQuantizationMethod();

    // QuantizationMethod interface
protected:
    void process() override;

private:
};

#endif // UNIFORMQUANTIZATIONMETHOD_H
