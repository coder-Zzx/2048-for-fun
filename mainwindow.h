#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ctime>
#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QPoint>
#include <QPushButton>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:

private:
    Ui::MainWindow *ui;
    void initGame();
    void up();
    void down();
    void left();
    void right();
    void defBoard();
    void check();
    void newGame();
    int generateRandom(int n);
    QLabel *board[4][4];
    int t=1;
    int score=0;
};
#endif // MAINWINDOW_H
