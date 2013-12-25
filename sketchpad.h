#ifndef SKETCHPAD_H
#define SKETCHPAD_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>


class SketchPad : public QWidget
{
    Q_OBJECT
public:
    explicit SketchPad(QWidget *parent = 0);

    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    QImage image;

signals:
    
public slots:
    void clearImage();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool sketching;
    int myPenWidth;
    QColor myPenColor;
    QPoint lastPoint;

};

#endif // SKETCHPAD_H
