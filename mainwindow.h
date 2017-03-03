#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
    bool shutdownInitiated = false;
};

#endif // MAINWINDOW_H
