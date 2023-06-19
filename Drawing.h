#pragma once
#include "ui_IMGPro.h"
//#include"mainWindow.h"
#include "Useui.h"
#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
//#include<qlabel.h>

void ui_init(Ui::IMGProClass* ui_ptr);
extern Ui::IMGProClass* Dui;//������һ��


// ����״̬��
class DrawingState:public QLabel {
	Q_OBJECT
public:
    virtual void draw() = 0;
    DrawingState(QWidget* parent = 0)
    {
        m_StartPoint = m_EndPoint = QPoint(0, 0);
        m_Pixmap = QPixmap(500, 500);
    };
 

public://����ͼ��չ��
    QPixmap m_Pixmap;
    QPoint m_StartPoint;
    QPoint m_EndPoint;
    QPixmap GetPixmap() { return m_Pixmap; }

public:
  void setStartPoint(QPoint point) {
		m_StartPoint = point;
	}
    void setEndPoint(QPoint point) {
		m_EndPoint = point;
    }
//    /*void setPixmap(QPixmap pixmap) {
//		m_Pixmap = pixmap;
//	}*/
//    QPixmap getPixmap() {
//		return m_Pixmap;
//	}
//    QPoint getStartPoint() {
//		return m_StartPoint;
//	}
//    QPoint getEndPoint() {
//		return m_EndPoint;
//	}

};

// ����״̬��
class DrawingLINESTRING : public DrawingState {
public:
    
    void draw() override;
    //QMessageBox::critical(Dui->centralWidget, QStringLiteral("����"), QStringLiteral("����"));

};//��

class DrawingPOLYGON : public DrawingState {
public:
    QVector<QPoint> polygonPoints; // ���ڴ洢����εĸ�������
    void draw() override {
        
    };
};//�����

class DrawingPOINT:public DrawingState {
public:
    void draw() override {
        //QMessageBox::critical(Dui->centralWidget, QStringLiteral("��"), QStringLiteral("����"));
    };
};//��

class DrawingSECTOR:public DrawingState {
public:
    void draw() override {};
};//����

class DrawingCIRCLE :public DrawingState {
public:
    void draw() override {
        m_Pixmap.fill(Qt::white);
        QPainter painter(&m_Pixmap);
        QRect rect(m_StartPoint, m_EndPoint);
        painter.setPen(Qt::green);
        painter.drawEllipse(rect);
    };
};//Բ��

class DrawingTEXT :public DrawingState {
public:
    void draw() override;
};//�ı�

class DrawingBITMAP :public DrawingState {
public:
    void draw() override;
};//λͼ




// ��������
class DrawingContext:public QWidget {
    Q_OBJECT
private:
    DrawingState* currentState;//��ǰ״̬
    QVector<QPoint> polygonPoints; // ���ڴ洢����εĸ�������
public:
    DrawingContext(QWidget* parent = 0) : currentState(nullptr) {}//��ʼ��
    // ���õ�ǰ״̬
    void setCurrentState(DrawingState* state) {
        currentState = state;
    }
    // ִ�л��Ʋ���
    void draw();
    // �¼�������
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* event);


};

//���󽻻�
class Widget : public QWidget
{
    Q_OBJECT
private:
    bool m_MouseDown;
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
public:
    Widget(QWidget* parent = 0);
    ~Widget();
private slots:
};

