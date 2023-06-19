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
extern Ui::IMGProClass* Dui;//声明有一个


// 抽象状态类
class DrawingState:public QLabel {
	Q_OBJECT
public:
    virtual void draw() = 0;
    DrawingState(QWidget* parent = 0)
    {
        m_StartPoint = m_EndPoint = QPoint(0, 0);
        m_Pixmap = QPixmap(500, 500);
    };
 

public://用于图像展现
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

// 具体状态类
class DrawingLINESTRING : public DrawingState {
public:
    
    void draw() override;
    //QMessageBox::critical(Dui->centralWidget, QStringLiteral("错误"), QStringLiteral("错误"));

};//线

class DrawingPOLYGON : public DrawingState {
public:
    QVector<QPoint> polygonPoints; // 用于存储多边形的各个顶点
    void draw() override {
        
    };
};//多边形

class DrawingPOINT:public DrawingState {
public:
    void draw() override {
        //QMessageBox::critical(Dui->centralWidget, QStringLiteral("点"), QStringLiteral("错误"));
    };
};//点

class DrawingSECTOR:public DrawingState {
public:
    void draw() override {};
};//扇形

class DrawingCIRCLE :public DrawingState {
public:
    void draw() override {
        m_Pixmap.fill(Qt::white);
        QPainter painter(&m_Pixmap);
        QRect rect(m_StartPoint, m_EndPoint);
        painter.setPen(Qt::green);
        painter.drawEllipse(rect);
    };
};//圆形

class DrawingTEXT :public DrawingState {
public:
    void draw() override;
};//文本

class DrawingBITMAP :public DrawingState {
public:
    void draw() override;
};//位图




// 上下文类
class DrawingContext:public QWidget {
    Q_OBJECT
private:
    DrawingState* currentState;//当前状态
    QVector<QPoint> polygonPoints; // 用于存储多边形的各个顶点
public:
    DrawingContext(QWidget* parent = 0) : currentState(nullptr) {}//初始化
    // 设置当前状态
    void setCurrentState(DrawingState* state) {
        currentState = state;
    }
    // 执行绘制操作
    void draw();
    // 事件处理函数
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* event);


};

//键鼠交互
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

