#include "widget.h"
#include "ui_widget.h"
#include <QFont>
#include <QDateTime>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_timer(new QTimer(this)),
    m_isTop(false),
    m_isEnableMove(true)

{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);

    m_time = QDateTime::currentDateTime().toString("--:--");
    m_date = QDateTime::currentDateTime().toString("--/--");
    m_week = QString("星期--");
    connect(m_timer,&QTimer::timeout,this,&Widget::updateTime);
    m_timer->start(1000);

    m_topButton = new QAction("置顶",this);
    m_exitButton = new QAction("退出",this);
    m_enMoveButton = new QAction("固定",this);

    connect(m_topButton,&QAction::triggered,this,&Widget::onTopButton);
    connect(m_enMoveButton,&QAction::triggered,this,&Widget::onEnMoveButton);
    connect(m_exitButton,&QAction::triggered,this,&Widget::onExitButton);

    addAction(m_topButton);
    addAction(m_enMoveButton);
    addAction(m_exitButton);

    setContextMenuPolicy(Qt::ActionsContextMenu);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_isEnableMove) return;
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_dragPos);
        event->accept();
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(!m_isEnableMove) return;

    if(event->button() == Qt::LeftButton)
    {
        m_dragPos=event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QFont font;
    font.setFamily("HarmonyOS Sans SC");
    font.setPixelSize(68/2);
    painter.setFont(font);

    painter.setRenderHints(QPainter::Antialiasing);	// 反锯齿;
    painter.setBrush(QBrush(Qt::black));
    painter.setPen(Qt::transparent);

    QRect rect = this->rect();
    rect.setWidth(rect.width());
    rect.setHeight(rect.height());
    painter.drawRoundedRect(rect, rect.height()/2, rect.height()/2);

    QPainter painter2(this);
    painter2.setFont(font);
    painter2.setPen(Qt::white);
    painter2.drawLine(26/2,rect.height()/2, (24+76)/2,rect.height()/2);
    rect.setRect(0,0,64*3/2,64/2);
    painter2.translate((96+20)/2,16/2);
    painter2.drawText(rect,Qt::AlignCenter,m_time);


    font.setPixelSize(24/2);
    painter2.setFont(font);
    painter2.setPen(Qt::red);
    painter2.translate(-148/2,-18/2);
    painter2.drawText(rect,Qt::AlignCenter,m_date);

    font.setPixelSize(22/2);
    painter2.setFont(font);
    painter2.setPen(Qt::white);
    painter2.translate(0,36/2);
    painter2.drawText(rect,Qt::AlignCenter,m_week);


    QWidget::paintEvent(event);
}

void Widget::updateTime()
{
      m_time = QDateTime::currentDateTime().toString("HH:mm");
//    ui->label->setText(time);

      m_date = QDateTime::currentDateTime().toString("MM/dd");
//    ui->label_2->setText(dat);

      QStringList list= {"一","二","三","四","五","六","日"};
      int weekday = QDate::currentDate().dayOfWeek();
      m_week = QString("星期%1").arg(list[weekday-1]);

      this->update();
}

void Widget::onTopButton()
{
    m_isTop = !m_isTop;
    if(m_isTop)
    {
        m_topButton->setIcon(createTextIcon("√", QSize(32, 32)));
        setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
        show();
    }
    else
    {
        m_topButton->setIcon(createTextIcon(" ", QSize(32, 32)));
        setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
        show();
    }
}

void Widget::onExitButton()
{
    QApplication::quit();
}

void Widget::onEnMoveButton()
{
    m_isEnableMove  = !m_isEnableMove;
    if(m_isEnableMove)
    {
        m_enMoveButton->setIcon(createTextIcon(" ", QSize(32, 32)));
    }
    else
    {
        m_enMoveButton->setIcon(createTextIcon("√", QSize(32, 32)));
    }
}

QPixmap Widget::createTextIcon(const QString &text, const QSize &size)
{
    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent); // 透明背景
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.drawText(pixmap.rect(), Qt::AlignCenter, text); // 在中心绘制文本
    return pixmap;
}
