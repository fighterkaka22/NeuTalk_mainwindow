#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    ClickLabel(QWidget * parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event); // 鼠标按压事件
    void mouseHoverEvent(QMouseEvent *event); // 鼠标按压事件
signals:
    void clicked(); // 单击信号
    //这里写悬停函数
};
#endif // CLICKLABEL_H
