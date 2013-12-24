#include <QtGui>

#include "sketchpad.h"

SketchPad::SketchPad(QWidget *parent) :
    QWidget(parent)
{
    QSize sz; sz.setWidth(640); sz.setHeight(480);
    resizeImage(&image,sz);
    modified = false;
    sketching = false;
    myPenWidth = 3;
    myPenColor = Qt::gray;
}

void SketchPad::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void SketchPad::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void SketchPad::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void SketchPad::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        lastPoint = e->pos();
        sketching = true;
    }
}

void SketchPad::mouseMoveEvent(QMouseEvent *e)
{
    if ((e->buttons() & Qt::LeftButton) && sketching)
        drawLineTo(e->pos());
}

void SketchPad::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && sketching) {
        drawLineTo(e->pos());
        sketching = false;
    }
}

void SketchPad::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QRect dirtyRect = e->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void SketchPad::resizeEvent(QResizeEvent *e)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(e);
}

void SketchPad::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void SketchPad::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
