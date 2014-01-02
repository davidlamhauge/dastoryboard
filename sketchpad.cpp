#include <QtGui>

#include "sketchpad.h"

SketchPad::SketchPad(QWidget *parent) :
    QWidget(parent)
{
    QSize sz; sz.setWidth(640); sz.setHeight(480);
    resizeImage(&image,sz);
}

void SketchPad::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void SketchPad::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void SketchPad::initPad(QString path, int name)
{
    myFilePath = path;   // full path, including the ending "/"
    QString s;
    s.setNum(name);
    s += ".png";
    myFileName = s;   // the files name, without path
    myComment = "";
    myShowComment = false;
    myShot = "";
    myShowShot = false;
    myFrames = 50;
    myShowFrames = false;

    modified = false;
    sketching = false;
    myPenWidth = 3;
    myPenColor = Qt::gray;
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
    if (e->button() == Qt::RightButton){
        del1 = e->pos();
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
    if (e->button() == Qt::RightButton){
        del2 = e->pos();
        if (del1.x() < del2.x() && del1.y() < del2.y()){
            for (int i = del1.x(); i < del2.x();i++)
                for (int j = del1.y();j < del2.y();j++)
                    image.setPixel(i,j,qRgb(255,255,255));
        }
        update();
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
