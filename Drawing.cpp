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
	//QMessageBox::critical(Dui->centralWidget, QStringLiteral("����"), QStringLiteral("����"));
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
    //QMessageBox::critical(Dui->centralWidget, QStringLiteral("����"), QStringLiteral("����"));
    if (event->button() == Qt::LeftButton && currentState)
    {//���Ϊ���
            if (auto polygonState = dynamic_cast<DrawingPOLYGON*>(currentState)) 
            {//��ת��ʧ�����˳�
                 // ���ƶ����
                QPainter painter(&currentState->m_Pixmap);       
                painter.setPen(Qt::green);
                painter.drawPolygon(polygonState->polygonPoints.data(), polygonState->polygonPoints.size());
                //draw();
            }
            else {
                // ����һ����
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
    // �����Ҫ��ʵ������ƶ�����
}

void DrawingContext::keyPressEvent(QKeyEvent* event) {
    // �����Ҫ��ʵ�ְ�������
}

void DrawingContext::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event); // ���ø����paintEvent��ȷ��Ĭ�ϻ�ͼ����Ҳ��ִ��

    if (currentState)
    {
        QPixmap temp = currentState->GetPixmap();
        QPainter painter(this);
        //currentState->draw(painter); // ���õ�ǰ״̬��draw�������ڻ�ͼ�豸�ϻ��Ƶ����������
        painter.drawPixmap(0, 0, temp);
    }
}

