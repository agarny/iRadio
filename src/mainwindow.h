/*******************************************************************************

Copyright Alan Garny

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*******************************************************************************/

//==============================================================================
// Main window
//==============================================================================

#pragma once

//==============================================================================

#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QSystemTrayIcon>

//==============================================================================

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *pParent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *pEvent);

signals:
    void clicked();
};

//==============================================================================

namespace Ui {
    class MainWindow;
}

//==============================================================================

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *pParent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *mGui;

    QSystemTrayIcon mTrayIcon;

    QMediaPlayer mMediaPlayer;

    void playRadio(const QString &pRadio);

private slots:
    void trayIconActivated();

    void on_franceinfoButton_clicked();
    void on_nostalgieButton_clicked();

    void on_volumeSlider_valueChanged(int pValue);
};

//==============================================================================
// End of file
//==============================================================================
