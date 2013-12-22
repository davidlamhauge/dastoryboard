#include <QtGui>

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

void sketchPad::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void sketchPad::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        sketching = true;
    }
}

void sketchPad::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && sketching)
        drawLineTo(event->pos());
}

void sketchPad::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && sketching) {
        drawLineTo(event->pos());
        sketching = false;
    }
}

void sketchPad::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void sketchPad::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void sketchPad::drawLineTo(const QPoint &endPoint)
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

void sketchPad::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
