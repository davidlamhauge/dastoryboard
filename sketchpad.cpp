#include "sketchpad.h"

sketchPad::sketchPad(QWidget *parent) :
    QWidget(parent)
{
}

void sketchPad::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void sketchPad::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}
