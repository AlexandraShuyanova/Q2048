#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>


QT_BEGIN_NAMESPACE
namespace Ui {
    class Widget; 
}
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT


public:
   Widget(QWidget *parent = nullptr);
  

private:
    const int GRID_SIZE = 500;
    const int GRID_X = 20;
    const int GRID_Y = 155;
    int CELL_QUANTITY = 4;
    QList <QList<int>> list = {};
    const QString GRID_COLOR = "#aa9779";
    const int GRID_ROUNDED = 3;
    const QString EMPTY_CELL = "#d0b795";
    const QString CELL_2 = "#eff4cc";
    const QString CELL_4 = "#dedc93";
    const QString CELL_8 = "#efa845";
    const QString CELL_16 = "#ee8244";
    const QString NUM_COLOR = "#000000";
    const int CELL_SIZE = 106;
    const int CELL_ROUNDED = 4;
    int cell_X = 33;
    int cell_Y = 168;
    bool isGameStarted = false;

    Ui::Widget *ui;
    void doPainting();
    int randInt(int, int);
    void setList();

private slots:
    void randCells();

protected:
    void paintEvent(QPaintEvent* e);
    virtual void keyPressEvent(QKeyEvent *event);
};
#endif // WIDGET_H


