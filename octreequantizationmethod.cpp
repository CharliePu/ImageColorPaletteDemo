#include "octreequantizationmethod.h"

OctreeQuantizationMethod::OctreeQuantizationMethod()
{

}

void OctreeQuantizationMethod::addNode(OctreeNode *current, int r, int g, int b, int depth)
{
    int index = ((r >> depth) & 1) | (((g >> depth) & 1) << 1) | (((b >> depth) & 1) << 2);

    if (depth == 0)
    {
        current->red += r;
        current->green += g;
        current->blue += b;
        current->count++;
    }
    else
    {
        if (!current->children[index])
            current->children[index] = new OctreeNode();
        addNode(current->children[index], r, g, b, depth - 1);
    }
}

void OctreeQuantizationMethod::getNodesAtDepth(OctreeNode *current, int depth, QList<OctreeNode*> &list)
{
    if (!current)
        return;

    if (depth > 0)
    {
        for (auto child : current->children)
        {
            getNodesAtDepth(child, depth - 1, list);
        }
    }
    else
    {
        list.append(current);
    }
}


void OctreeQuantizationMethod::process()
{
    OctreeNode root;
    for (QColor color : getImage().getColors())
    {
        addNode(&root, color.red(), color.green(), color.blue(), 2);
    }

    //root = reduceTreeToDepth(&root, 3);

    QList<OctreeNode*> list;
    getNodesAtDepth(&root, 2, list);

    std::sort(list.begin(), list.end(), [](OctreeNode *n1, OctreeNode *n2){
        return n1->count > n2->count;
    });

    for (int i = 0; i < list.size(); ++i)
    {
        colors.append(Color(
                          list.at(i)->red/list.at(i)->count,
                          list.at(i)->green/list.at(i)->count,
                          list.at(i)->blue/list.at(i)->count,
                          0));
    }

    return;
}
