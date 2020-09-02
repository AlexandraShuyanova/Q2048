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

    CELL_COLORS.insert(2, CELL_2);
    CELL_COLORS.insert(4, CELL_4);
    CELL_COLORS.insert(8, CELL_8);
    CELL_COLORS.insert(16, CELL_16);
    CELL_COLORS.insert(32, CELL_32);
    CELL_COLORS.insert(64, CELL_64);
    CELL_COLORS.insert(128, CELL_128);
    CELL_COLORS.insert(256, CELL_256);
    CELL_COLORS.insert(512, CELL_512);
    CELL_COLORS.insert(1024, CELL_1024);
    CELL_COLORS.insert(2048, CELL_2048);
}    




void Widget::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);

    doPainting();
}

void Widget::keyPressEvent(QKeyEvent* event) {
    if (isGameStarted) {
        bool cellChanged = false;

        if (event->key() == Qt::Key_S) {
            for (int i = CELL_QUANTITY-2; i > -1; i--) {
                for (int j = 0; j < CELL_QUANTITY; j++) {

                    if (list[i][j] == 0)
                        continue;

                    else {
                        int saved_i = i;
                        for (int k = i + 1; k < CELL_QUANTITY; k++) {
                            if (list[k][j] == 0) {
                                cellChanged = true;
                                std::swap(list[saved_i][j], list[k][j]);
                                saved_i++;
                            }
                        }
                    }  
                }
            }
            
            for (int j = 0; j < CELL_QUANTITY; j++) {
                for (int i = CELL_QUANTITY - 2; i > -1; i--) {

                    if (list[i][j] == list[i + 1][j] && list[i][j] != 0) {
                        cellChanged = true;
                        list[i + 1][j] = 2 * list[i][j];
                        list[i][j] = 0;
                    }
                }
                for (int i = CELL_QUANTITY-1; i > 0; i--) {
                    if (list[i][j] == 0) {
                        std::swap(list[i - 1][j], list[i][j]);
                    }
                }

            }
            repaint();

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
                                cellChanged = true;
                                std::swap(list[saved_i][j], list[k][j]);
                                saved_i--;
                            }
                        }

                    }

                }

            }
            
            for (int j = 0; j < CELL_QUANTITY; j++) {
                for (int i = 1; i < CELL_QUANTITY; i++) {
                
                    if (list[i][j] == list[i-1][j] && list[i][j] != 0) {
                        cellChanged = true;
                        list[i-1][j] = 2 * list[i][j];
                        list[i][j] = 0;
                    }
                }
                for (int i = 0; i < CELL_QUANTITY-1; i++) {
                    if (list[i][j] == 0) {
                        std::swap(list[i+1][j], list[i][j]);
                    }
                }

            }
            repaint();

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
                                cellChanged = true;
                                std::swap(list[i][saved_j], list[i][k]);
                                saved_j++;
                            }
                        }
                    }
                }
            }
            
            for (int i = 0; i < CELL_QUANTITY; i++) {
                for(int j = CELL_QUANTITY - 1; j > 0; j--){
                        if (list[i][j] == list[i][j - 1] && list[i][j] != 0) {
                            cellChanged = true;
                            list[i][j] = 2 * list[i][j - 1];
                            list[i][j - 1] = 0;
                        }
                }
                for (int j = CELL_QUANTITY - 1; j > 0; j--) {
                    if (list[i][j] == 0) {
                        std::swap(list[i][j], list[i][j - 1]);
                    }
                }
                
            }
            repaint();
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
                                cellChanged = true;
                                std::swap(list[i][k], list[i][saved_j]);
                                saved_j--;
                            }
                        }
                    }
                }
            }
            
            for (int i = 0; i < CELL_QUANTITY; i++) {
                for (int j = 0; j < CELL_QUANTITY-1; j++) {
                    if (list[i][j] == list[i][j + 1] && list[i][j]!=0) {
                        cellChanged = true;
                        list[i][j] = 2 * list[i][j + 1];
                        list[i][j + 1] = 0;
                    }
                }
                for (int j = 0; j < CELL_QUANTITY - 1; j++) {
                    if (list[i][j] == 0) {
                        std::swap(list[i][j], list[i][j + 1]);
                    }
                }

            }
            repaint();

        }
        

        if (cellChanged) {
            randOneCell();
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
                
                if (list[i][j] == 0) {
                    continue;
                }

                QColor cellColor = QColor(CELL_COLORS[list[i][j]]);
                cell.setPen(cellColor);
                cell.setBrush(QBrush(cellColor));
               
                cell.drawRoundRect(cell_X + j * 122, cell_Y + i * 122, CELL_SIZE, CELL_SIZE, CELL_ROUNDED, CELL_ROUNDED);
                cell.setPen(QColor(NUM_COLOR));
                cell.setBrush(QBrush(QColor(NUM_COLOR)));
                cell.drawText(cell_X + j * 122 + 37, cell_Y + i * 122 + 70, QString::number(list[i][j]));
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

void Widget::randOneCell() {
    int random_X = 0;
    int random_Y = 0;
    while (list[random_X][random_Y] != 0) {
        random_X = randInt(0, 3);
        random_Y = randInt(0, 3);
    }
    int num = randInt(0, 1);
    list[random_X][random_Y] = num;
    repaint();
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
    isGameStarted = true;
    repaint();
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


        
        

   



