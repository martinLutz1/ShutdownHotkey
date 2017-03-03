#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"
#include <QMessageBox>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    if(!RegisterHotKey(HWND(winId()), 1, MOD_CONTROL, 33))
    {
        QMessageBox::warning(this, "Warnung", "Kann 'Bild hoch' nicht registrieren");
    }
    if(!RegisterHotKey(HWND(winId()), 0, MOD_CONTROL, 34))
    {
        QMessageBox::warning(this, "Warnung", "Kann 'Bild runter' nicht registrieren");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);

    MSG *msg = static_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY)
    {
        switch (msg->lParam)
        {
        case 2162690: // Ctrl + Page up
        {
            if (!shutdownInitiated)
            {
                shutdownInitiated = true;
                WinExec("shutdown -s -t 10 -c \"Herunterfahren in 10 Sekunden.\"", SW_HIDE);
            }
            break;
        }
        case 2228226: // Ctrl + Page down
        {
            if (shutdownInitiated)
            {
                shutdownInitiated = false;
                WinExec("shutdown -a", SW_HIDE);
            }
            break;
        }
        default:
            break;
        }
    }

    return QMainWindow::nativeEvent(eventType, message, result);
}
