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
    void initPad(QString path, int name);

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

    QString filePath() const {return myFilePath; }
    QString fileName() const {return myFileName; }
    QString comment() const {return myComment; }
    bool showComment() const {return myShowComment; }
    QString shot() const {return myShot; }
    bool showShot() const {return myShowShot; }
    int frames() const {return myFrames; }
    bool showFrames() const {return myShowFrames; }

    QImage image;           // 640x480 pix storyboard pad

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

    QString myFilePath;   // full path, including the ending "/"
    QString myFileName;   // the files name, without path
    QString myComment;
    bool myShowComment;
    QString myShot;
    bool myShowShot;
    int myFrames;
    bool myShowFrames;

    bool modified;
    bool sketching;
    int myPenWidth;
    QColor myPenColor;
    QPoint lastPoint;
    QPoint del1;
    QPoint del2;
    QRect deleteRect;   // rectangle that is to be deleted

};

#endif // SKETCHPAD_H
