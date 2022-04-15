#include <mainwindow.h>
#include <ui_mainwindow.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGame()
{
    score=0;
    ui->lcdNowPts->display(score);
    defBoard();
    t=1;

    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            board[i][j]->setText(QString());
            board[i][j]->setStyleSheet("QLabel{border:2px solid;border-radius:5px;}");
        }
    }

    int x_init=generateRandom(4);
    int y_init=generateRandom(4);
    board[x_init][y_init]->setText(QString::number(2));

    connect(ui->buttonUp,&QPushButton::clicked,this,&MainWindow::up);
    connect(ui->buttonDown,&QPushButton::clicked,this,&MainWindow::down);
    connect(ui->buttonLeft,&QPushButton::clicked,this,&MainWindow::left);
    connect(ui->buttonRight,&QPushButton::clicked,this,&MainWindow::right);
    connect(ui->buttonNewGame,&QPushButton::clicked,this,&MainWindow::newGame);
}

void MainWindow::defBoard()
{
    board[0][0]=ui->l00;
    board[0][1]=ui->l01;
    board[0][2]=ui->l02;
    board[0][3]=ui->l03;
    board[1][0]=ui->l10;
    board[1][1]=ui->l11;
    board[1][2]=ui->l12;
    board[1][3]=ui->l13;
    board[2][0]=ui->l20;
    board[2][1]=ui->l21;
    board[2][2]=ui->l22;
    board[2][3]=ui->l23;
    board[3][0]=ui->l30;
    board[3][1]=ui->l31;
    board[3][2]=ui->l32;
    board[3][3]=ui->l33;
}

int MainWindow::generateRandom(int n)
{
    srand(time(NULL));
    return rand()%n;
}

void MainWindow::up()
{
    QVector<int> pts_to_add;
    QVector<QPoint> empty_position;
    for (int j=0;j<4;j++)
    {
        for (int k=0;k<3;k++)
        {
            for (int i=0;i<3;i++)
            {
                if (board[i][j]->text().isEmpty()&&!board[i+1][j]->text().isEmpty())
                {
                    board[i][j]->setText(board[i+1][j]->text());
                    board[i+1][j]->setText(QString());
                }
            }
        }
    }

    for (int j=0;j<4;j++)
    {
        for (int i=0;i<3;i++)
        {
            if (board[i][j]->text()==board[i+1][j]->text()&&!board[i][j]->text().isEmpty())
            {
                int n=board[i][j]->text().toInt()+board[i+1][j]->text().toInt();
                board[i][j]->setText(QString::number(n));
                board[i+1][j]->setText(QString());
                pts_to_add.append(n);
            }
        }
    }

    for (int j=0;j<4;j++)
    {
        for (int k=0;k<3;k++)
        {
            for (int i=0;i<3;i++)
            {
                if (board[i][j]->text().isEmpty()&&!board[i+1][j]->text().isEmpty())
                {
                    board[i][j]->setText(board[i+1][j]->text());
                    board[i+1][j]->setText(QString());
                }
            }
        }
    }

    for (int i=0;i<pts_to_add.count();i++)
    {
        score+=pts_to_add[i];
    }
    pts_to_add.clear();
    pts_to_add.squeeze();
    ui->lcdNowPts->display(score);

    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            if (board[i][j]->text().isEmpty())
            {
                empty_position.append(QPoint(i,j));
            }
        }
    }
    int empty_num=empty_position.count();
    int board_new=generateRandom(empty_num);
    board[empty_position[board_new].x()][empty_position[board_new].y()]->setText(QString::number(2));
    empty_position.clear();
    empty_position.squeeze();

    check();
}

void MainWindow::down()
{
    QVector<int> pts_to_add;
    QVector<QPoint> empty_position;
    for (int j=0;j<4;j++)
    {
        for (int k=0;k<3;k++)
        {
            for (int i=0;i<3;i++)
            {
                if (board[i+1][j]->text().isEmpty()&&!board[i][j]->text().isEmpty())
                {
                    board[i+1][j]->setText(board[i][j]->text());
                    board[i][j]->setText(QString());
                }
            }
        }
    }

    for (int j=0;j<4;j++)
    {
        for (int i=0;i<3;i++)
        {
            if (board[i][j]->text()==board[i+1][j]->text()&&!board[i][j]->text().isEmpty())
            {
                int n=board[i][j]->text().toInt()+board[i+1][j]->text().toInt();
                board[i+1][j]->setText(QString::number(n));
                board[i][j]->setText(QString());
                pts_to_add.append(n);
            }
        }
    }

    for (int j=0;j<4;j++)
    {
        for (int k=0;k<3;k++)
        {
            for (int i=0;i<3;i++)
            {
                if (board[i+1][j]->text().isEmpty()&&!board[i][j]->text().isEmpty())
                {
                    board[i+1][j]->setText(board[i][j]->text());
                    board[i][j]->setText(QString());
                }
            }
        }
    }

    for (int i=0;i<pts_to_add.count();i++)
    {
        score+=pts_to_add[i];
    }
    pts_to_add.clear();
    pts_to_add.squeeze();
    ui->lcdNowPts->display(score);

    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            if (board[i][j]->text().isEmpty())
            {
                empty_position.append(QPoint(i,j));
            }
        }
    }
    int empty_num=empty_position.count();
    int board_new=generateRandom(empty_num);
    board[empty_position[board_new].x()][empty_position[board_new].y()]->setText(QString::number(2));
    empty_position.clear();
    empty_position.squeeze();

    check();
}

void MainWindow::left()
{
    QVector<int> pts_to_add;
    QVector<QPoint> empty_position;
    for (int i=0;i<4;i++)
    {
        for (int k=0;k<3;k++)
        {
            for (int j=0;j<3;j++)
            {
                if (board[i][j]->text().isEmpty()&&!board[i][j+1]->text().isEmpty())
                {
                    board[i][j]->setText(board[i][j+1]->text());
                    board[i][j+1]->setText(QString());
                }
            }
        }
    }

    for (int i=0;i<4;i++)
    {
        for (int j=0;j<3;j++)
        {
            if (board[i][j]->text()==board[i][j+1]->text()&&!board[i][j]->text().isEmpty())
            {
                int n=board[i][j]->text().toInt()+board[i][j+1]->text().toInt();
                board[i][j]->setText(QString::number(n));
                board[i][j+1]->setText(QString());
                pts_to_add.append(n);
            }
        }
    }

    for (int i=0;i<4;i++)
    {
        for (int k=0;k<3;k++)
        {
            for (int j=0;j<3;j++)
            {
                if (board[i][j]->text().isEmpty()&&!board[i][j+1]->text().isEmpty())
                {
                    board[i][j]->setText(board[i][j+1]->text());
                    board[i][j+1]->setText(QString());
                }
            }
        }
    }

    for (int i=0;i<pts_to_add.count();i++)
    {
        score+=pts_to_add[i];
    }
    pts_to_add.clear();
    pts_to_add.squeeze();
    ui->lcdNowPts->display(score);

    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            if (board[i][j]->text().isEmpty())
            {
                empty_position.append(QPoint(i,j));
            }
        }
    }
    int empty_num=empty_position.count();
    int board_new=generateRandom(empty_num);
    board[empty_position[board_new].x()][empty_position[board_new].y()]->setText(QString::number(2));
    empty_position.clear();
    empty_position.squeeze();

    check();
}

void MainWindow::right()
{
    QVector<int> pts_to_add;
    QVector<QPoint> empty_position;
    for (int i=0;i<4;i++)
    {
        for (int k=0;k<3;k++)
        {
            for (int j=0;j<3;j++)
            {
                if (board[i][j+1]->text().isEmpty()&&!board[i][j]->text().isEmpty())
                {
                    board[i][j+1]->setText(board[i][j]->text());
                    board[i][j]->setText(QString());
                }
            }
        }
    }

    for (int i=0;i<4;i++)
    {
        for (int j=0;j<3;j++)
        {
            if (board[i][j]->text()==board[i][j+1]->text()&&!board[i][j]->text().isEmpty())
            {
                int n=board[i][j]->text().toInt()+board[i][j+1]->text().toInt();
                board[i][j+1]->setText(QString::number(n));
                board[i][j]->setText(QString());
                pts_to_add.append(n);
            }
        }
    }

    for (int i=0;i<4;i++)
    {
        for (int k=0;k<3;k++)
        {
            for (int j=0;j<3;j++)
            {
                if (board[i][j+1]->text().isEmpty()&&!board[i][j]->text().isEmpty())
                {
                    board[i][j+1]->setText(board[i][j]->text());
                    board[i][j]->setText(QString());
                }
            }
        }
    }

    for (int i=0;i<pts_to_add.count();i++)
    {
        score+=pts_to_add[i];
    }
    pts_to_add.clear();
    pts_to_add.squeeze();
    ui->lcdNowPts->display(score);

    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            if (board[i][j]->text().isEmpty())
            {
                empty_position.append(QPoint(i,j));
            }
        }
    }
    int empty_num=empty_position.count();
    int board_new=generateRandom(empty_num);
    board[empty_position[board_new].x()][empty_position[board_new].y()]->setText(QString::number(2));
    empty_position.clear();
    empty_position.squeeze();

    check();
}

void MainWindow::newGame()
{
    score=0;
    ui->lcdNowPts->display(score);
    defBoard();
    t=1;

    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            board[i][j]->setText(QString());

        }
    }

    int x_init=generateRandom(4);
    int y_init=generateRandom(4);
    board[x_init][y_init]->setText(QString::number(2));
}

void MainWindow::check()
{
    QString title("游戏结束");
    QString str("您的分数是:");
    str+=QString::number(score);
    bool flag=true;
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            if (board[i][j]->text().isEmpty())
            {
                flag=false;
                break;
            }
        }
    }
    if (flag)
    {
        QMessageBox::information(this,title,str,QMessageBox::Yes);
        newGame();
    }
}
