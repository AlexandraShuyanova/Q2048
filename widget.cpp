#include "widget.h"
#include "ui_widget.h"

#include <qlineedit.h>
#include <QLabel>
#include <QPainter>
#include <QGlobal.h>
#include <QTime>
#include <QString>
#include <QKeyEvent>




Widget::Widget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->scoreLine->setReadOnly(true);
    ui->scoreLine->setStyleSheet("background-color: rgb(170, 151, 121);"
        "border-radius: 3px; ");

    ui->bestScoreLine->setReadOnly(true);
    ui->bestScoreLine->setStyleSheet("background-color: rgb(170, 151, 121);"
        "border-radius: 3px;");
    
    ui->goal->setStyleSheet("color: rgb(53, 47, 37)");
    ui->startBtn->setStyleSheet(" background-color:rgb(103, 91, 73);"
        "border-radius: 3px;"
        "color:rgb(250, 255, 201);");

    connect(ui->startBtn, &QPushButton::clicked, this, &Widget::randCells);
}    




void Widget::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);

    doPainting();
}

void Widget::keyPressEvent(QKeyEvent* event) {
    if (isGameStarted) {

        if (event->key() == Qt::Key_S) {
            for (int i = CELL_QUANTITY-2; i > -1; i--) {
                for (int j = 0; j < CELL_QUANTITY; j++) {

                    if (list[i][j] == 0)
                        continue;

                    else {
                        int saved_i = i;
                        for (int k = i + 1; k < CELL_QUANTITY; k++) {
                            if (list[k][j] == 0) {
                                int temp = list[saved_i][j];
                                list[saved_i][j] = list[k][j];
                                list[k][j] = temp;
                                saved_i++;
                            }
                        }
                    }  
                }
            }      
        } 
        else if (event->key() == Qt::Key_W) {
            for (int i = 1; i < CELL_QUANTITY; i++) {
                for (int j = 0; j < CELL_QUANTITY; j++) {

                    if (list[i][j] == 0)
                        continue;

                    else {
                        int saved_i = i;
                        for (int k = i - 1; k > -1; k--) {
                            if (list[k][j] == 0) {
                                int temp = list[saved_i][j];
                                list[saved_i][j] = list[k][j];
                                list[k][j] = temp;
                                saved_i--;
                            }
                        }

                    }

                }

            }
        }
        else if (event->key() == Qt::Key_D) {
            for (int i = 0; i < CELL_QUANTITY; i++) {
                for (int j = CELL_QUANTITY-2; j > -1; j--) {

                    if (list[i][j] == 0)
                        continue;

                    else {
                        int saved_j = j;
                        for (int k = j + 1; k < CELL_QUANTITY; k++) {
                            if (list[i][k] == 0) {
                                int temp = list[i][saved_j];
                                list[i][saved_j] = list[i][k];
                                list[i][k] = temp;
                                saved_j++;
                            }
                        }
                    }
                }
            }
        }
        else if (event->key() == Qt::Key_A) {
            for (int i = 0; i < CELL_QUANTITY; i++) {
                for (int j = 1; j < CELL_QUANTITY; j++) {

                    if (list[i][j] == 0)
                        continue;

                    else {
                        int saved_j = j;
                        for (int k = j - 1; k > -1; k--) {
                            if (list[i][k] == 0) {
                                int temp = list[i][saved_j];
                                list[i][saved_j] = list[i][k];
                                list[i][k] = temp;
                                saved_j--;
                            }
                        }
                    }
                }
            }
        }

    }
    repaint();
}

void Widget::doPainting() {
    QPainter painter(this);
    painter.setPen(QColor(GRID_COLOR));
    painter.setBrush(QBrush(QColor(GRID_COLOR)));

    painter.drawRoundRect(GRID_X, GRID_Y, GRID_SIZE, GRID_SIZE, GRID_ROUNDED, GRID_ROUNDED);
    QPainter cell(this);



    cell.setPen(QColor(EMPTY_CELL));

    cell.setBrush(QBrush(QColor(EMPTY_CELL)));


    for (int i = 0; i < CELL_QUANTITY; i++) {
        cell_X = 33;
        for (int j = 0; j < CELL_QUANTITY; j++) {
            cell.drawRoundRect(cell_X, cell_Y, CELL_SIZE, CELL_SIZE, CELL_ROUNDED, CELL_ROUNDED);
            cell_X += 122;
        }
        cell_Y += 122;
    }
    cell_Y = 168;
    cell_X = 33;




    if (list.size()) {
        QFont font = cell.font();
        font.setPixelSize(48);
        cell.setFont(font);

        for (int i = 0; i < CELL_QUANTITY; i++) {
            for (int j = 0; j < CELL_QUANTITY; j++) {
                bool isTwo = false;
                if (list[i][j] == 0) {
                    continue;
                }
                QString num = QString::number(list[i][j]);

                if (num == "2") {
                    isTwo = true;
                    cell.setPen(QColor(CELL_2));
                    cell.setBrush(QBrush(QColor(CELL_2)));
                }
                else {
                    cell.setPen(QColor(CELL_4));
                    cell.setBrush(QBrush(QColor(CELL_4)));
                }
                cell.drawRoundRect(cell_X + j * 122, cell_Y + i * 122, CELL_SIZE, CELL_SIZE, CELL_ROUNDED, CELL_ROUNDED);
                cell.setPen(QColor(NUM_COLOR));
                cell.setBrush(QBrush(QColor(NUM_COLOR)));
                isTwo ? cell.drawText(cell_X + j * 122 + 37, cell_Y + i * 122 + 70, "2") : cell.drawText(cell_X + j * 122 + 37, cell_Y + i * 122 + 70, "4");
            }
        }
    }
}

int Widget::randInt(int low, int high)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    
    int rand = qrand() % ((high + 1) - low) + low;
    if (high == 1 && rand == 0)
        return 2;
    else if (high == 1 && rand == 1)
        return 4;
    else
        return rand;
}

void Widget::randCells() {
    setList();

    int random_X_1 = 0;
    int random_Y_1 = 0;
    int random_X_2 = 0;
    int random_Y_2 = 0;

    while (random_X_1 == random_X_2 && random_Y_1 == random_Y_2)
    {
        random_X_1 = randInt(0, 3);
        random_Y_1 = randInt(0, 3);
        random_X_2 = randInt(0, 3);
        random_Y_2 = randInt(0, 3);
    }

    int first_num = randInt(0, 1);
    int second_num = randInt(0, 1);

    list[random_X_1][random_Y_1] = first_num;
    list[random_X_2][random_Y_2] = second_num;
        
    repaint();
    isGameStarted = true;
}

void Widget::setList() {
    list.clear();

    for (int i = 0; i < CELL_QUANTITY; i++) {
        QList<int> row;
        for (int j = 0; j < CELL_QUANTITY; j++) {
            row.append(0); 
        }
        list.append(row);
    }

}
        
        

   



