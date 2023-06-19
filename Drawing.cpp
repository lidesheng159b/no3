#include<iostream>
#include"Drawing.h"
using namespace std;

Ui::IMGProClass* Dui = nullptr;

void ui_init(Ui::IMGProClass* ui_ptr)
{
    Dui = ui_ptr;
}

void DrawingLINESTRING::draw()
{
	//QMessageBox::critical(Dui->centralWidget, QStringLiteral("错误"), QStringLiteral("错误"));
   /* m_Pixmap.fill(Qt::white);
    QPainter painter(&m_Pixmap);
    QRect rect(m_StartPoint, m_EndPoint);
    painter.setPen(Qt::red);
    painter.drawRect(rect);*/

}



//--------------------------------------------------------
void DrawingContext::draw() {
    if (currentState)
    {
        currentState->draw();
    }
}

void DrawingContext::mousePressEvent(QMouseEvent* event) {
    //QMessageBox::critical(Dui->centralWidget, QStringLiteral("错误"), QStringLiteral("错误"));
    if (event->button() == Qt::LeftButton && currentState)
    {//检查为左键
            if (auto polygonState = dynamic_cast<DrawingPOLYGON*>(currentState)) 
            {//若转换失败则退出
                 // 绘制多边形
                QPainter painter(&currentState->m_Pixmap);       
                painter.setPen(Qt::green);
                painter.drawPolygon(polygonState->polygonPoints.data(), polygonState->polygonPoints.size());
                //draw();
            }
            else {
                // 绘制一个点
                QPainter painter(this);
                painter.setPen(Qt::black);
                painter.drawPoint(event->pos());
                //draw();
                update();
            }
        
    }
}

void DrawingContext::mouseReleaseEvent(QMouseEvent* event) {
    if (currentState)
        currentState->setEndPoint(event->pos());
    //draw();
}

void DrawingContext::mouseMoveEvent(QMouseEvent* event) {
    // 如果需要，实现鼠标移动处理
}

void DrawingContext::keyPressEvent(QKeyEvent* event) {
    // 如果需要，实现按键处理
}

void DrawingContext::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event); // 调用父类的paintEvent，确保默认绘图操作也会执行

    if (currentState)
    {
        QPixmap temp = currentState->GetPixmap();
        QPainter painter(this);
        //currentState->draw(painter); // 调用当前状态的draw函数，在绘图设备上绘制点或其他内容
        painter.drawPixmap(0, 0, temp);
    }
}

