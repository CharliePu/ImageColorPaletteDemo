#include "uniformquantizationmethod.h"
#include <QtMath>

UniformQuantizationMethod::UniformQuantizationMethod():
    QuantizationMethod()
{

}


void UniformQuantizationMethod::process()
{
    QVector<ColorGroup> colorGroups;

    // 估算要将颜色空间分成多少格，格子数必须大于等于要求提取颜色数
    int divideNum = qCeil(qPow(getColorNum(), 1.0 / 3.0));
    long long totalCount = 0;
    colorGroups.resize(divideNum * divideNum * divideNum);

    for (auto color : getImage().getColors())
    {
        int red = color.red();
        int green = color.green();
        int blue = color.blue();
        size_t index = qFloor(red / 256.0 * divideNum)
                + qFloor(green / 256.0  * divideNum) * divideNum
                + qFloor(blue / 256.0 * divideNum) * divideNum * divideNum;

        colorGroups[index].r += red;
        colorGroups[index].g += green;
        colorGroups[index].b += blue;
        colorGroups[index].count++;
        totalCount++;
    }

    std::sort(colorGroups.begin(), colorGroups.end(), [](ColorGroup cg1, ColorGroup cg2)
    {
        return cg1.count > cg2.count;
    });

    int i = 0;
    for (auto colorGroup : colorGroups)
    {
        if (i >= getColorNum() || colorGroup.count == 0)
            break;

        colors.push_back(Color(
                          colorGroup.r/colorGroup.count,
                          colorGroup.g/colorGroup.count,
                          colorGroup.b/colorGroup.count,
                             colorGroup.count/static_cast<double>(totalCount)));

        i++;
    }
}
