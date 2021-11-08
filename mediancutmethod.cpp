#include "mediancutmethod.h"
#include <queue>

MedianCutMethod::MedianCutMethod()
{

}

BoundaryNode MedianCutMethod::createNode(QVector<QColor> colors)
{
    std::sort(colors.begin(), colors.end(), [](QColor q1, QColor q2) {
       return q1.red() < q2.red();
    });
    int rRange = colors.back().red() - colors.front().red();

    std::sort(colors.begin(), colors.end(), [](QColor q1, QColor q2) {
       return q1.green() < q2.green();
    });
    int gRange = colors.back().green() - colors.front().green();

    std::sort(colors.begin(), colors.end(), [](QColor q1, QColor q2) {
       return q1.blue() < q2.blue();
    });
    int bRange = colors.back().blue() - colors.front().blue();

    BoundaryNode node;

    node.colors = colors;

    if (rRange > gRange && rRange > bRange)
    {
        node.cutDim = 0;
        node.range = rRange;
    }
    else if (gRange > rRange && gRange > bRange)
    {
        node.cutDim = 1;
        node.range = gRange;
    }
    else
    {
        node.cutDim = 2;
        node.range = bRange;
    }

    return node;
}


void MedianCutMethod::process()
{
    auto cmp = [](BoundaryNode n1, BoundaryNode n2) { return n1.range < n2.range; };

    std::priority_queue<BoundaryNode, std::vector<BoundaryNode>, decltype(cmp)> maxRangeNodeQueue(cmp);

    BoundaryNode root = createNode(getImage().getColors());

    maxRangeNodeQueue.push(root);

    int i = 1;
    while (!maxRangeNodeQueue.empty() && i < getColorNum())
    {
        BoundaryNode maxRangeNode = maxRangeNodeQueue.top();

        switch (maxRangeNode.cutDim) {
        case 0:
            std::sort(maxRangeNode.colors.begin(), maxRangeNode.colors.end(), [](QColor q1, QColor q2) {
                return q1.red() < q2.red();
            });
            break;
        case 1:
            std::sort(maxRangeNode.colors.begin(), maxRangeNode.colors.end(), [](QColor q1, QColor q2) {
                return q1.green() < q2.green();
            });
            break;
        default:
            std::sort(maxRangeNode.colors.begin(), maxRangeNode.colors.end(), [](QColor q1, QColor q2) {
                return q1.blue() < q2.blue();
            });
            break;
        }

        BoundaryNode lowerNode, upperNode;
        if (maxRangeNode.colors.size() > 1)
        {
            lowerNode = createNode(QVector<QColor>(
                                                    maxRangeNode.colors.begin(),
                                                    maxRangeNode.colors.begin() + maxRangeNode.colors.size() / 2));
            upperNode = createNode(QVector<QColor>(
                                                    maxRangeNode.colors.begin() + maxRangeNode.colors.size() / 2,
                                                    maxRangeNode.colors.end()));

        }

        maxRangeNodeQueue.pop();

        if (lowerNode.colors.size() > 0)
            maxRangeNodeQueue.push(lowerNode);

        if (upperNode.colors.size() > 0)
        maxRangeNodeQueue.push(upperNode);

        ++i;
    }

    while(!maxRangeNodeQueue.empty())
    {
        long long r = 0,g = 0,b = 0;
        int count = 0;
        for (auto color : maxRangeNodeQueue.top().colors)
        {
            r+=color.red();
            g+=color.green();
            b+=color.blue();
            ++count;
        }

        maxRangeNodeQueue.pop();

        if (count == 0)
        {
            continue;
        }

        r /= count;
        g /= count;
        b /= count;
        colors.append(Color(r, g, b, count / static_cast<double>(getImage().getColors().size())));
    }
}
