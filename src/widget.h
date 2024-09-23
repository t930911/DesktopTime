#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QAction>
#include <QPixmap>
#include <QPoint>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void mouseMoveEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    QPixmap createTextIcon(const QString &text, const QSize &size);

public slots:
    void updateTime();

    void onTopButton();

    void onExitButton();

    void onEnMoveButton();
private:
    Ui::Widget *ui;
    QPoint m_dragPos;
    QTimer *m_timer;
    QString m_time;
    QString m_date;
    QString m_week;
    QAction *m_topButton;
    QAction *m_exitButton;
    QAction *m_enMoveButton;
    bool m_isTop;
    bool m_isEnableMove;
};

#endif // WIDGET_H
