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

#include "mainwindow.h"

//==============================================================================

#include "ui_mainwindow.h"

//==============================================================================

#include <QGuiApplication>
#include <QScreen>
#include <QSettings>
#include <QSystemTrayIcon>

//==============================================================================

ClickableLabel::ClickableLabel(QWidget *pParent)
    : QLabel(pParent)
{
    setCursor(Qt::PointingHandCursor);
}

//==============================================================================

void ClickableLabel::mousePressEvent(QMouseEvent *pEvent)
{
    Q_UNUSED(pEvent);

    emit clicked();
}

//==============================================================================

static const auto SettingsRadio    = QStringLiteral("Radio");
static const auto SettingsVolume   = QStringLiteral("Volume");
static const auto FranceInfoRadio  = QStringLiteral("https://direct.franceinfo.fr/live/franceinfo-midfi.mp3");
static const auto NostalgieRadio   = QStringLiteral("https://cdn.nrjaudio.fm/audio1/fr/30601/mp3_128.mp3");

//==============================================================================

MainWindow::MainWindow(QWidget *pParent) :
    QMainWindow(pParent),
    mGui(new Ui::MainWindow)
{
    mGui->setupUi(this);

    setWindowFlags(Qt::Popup);

    ClickableLabel *quitLabel = new ClickableLabel(this);
    QFont quitLabelFont = quitLabel->font();

    quitLabelFont.setPointSize(mGui->iRadioLabel->font().pointSize());

    quitLabel->setPixmap(QPixmap(":/Close").scaled(16, 16, Qt::KeepAspectRatio));
    quitLabel->setFont(quitLabelFont);
    quitLabel->setStyleSheet("ClickableLabel {"
                             "    padding: 4px 4px 4px 0px;"
                             "    background-color: rgb(0, 85, 127);"
                             "    color: white;"
                             "}");

    mGui->topLayout->addWidget(quitLabel);

    connect(quitLabel, &ClickableLabel::clicked,
            qApp, &QApplication::quit);

    mTrayIcon.setIcon(QIcon(":/iRadio"));
    mTrayIcon.setToolTip("iRadio");

    connect(&mTrayIcon, &QSystemTrayIcon::activated,
            this, &MainWindow::trayIconActivated);

    mTrayIcon.show();

    QSettings settings;

    mGui->volumeSlider->setValue(settings.value(SettingsVolume, 13).toInt());

    playRadio(settings.value(SettingsRadio, FranceInfoRadio).toString());
}

//==============================================================================

MainWindow::~MainWindow()
{
    delete mGui;
}

//==============================================================================

void MainWindow::playRadio(const QString &pRadio)
{
    QSettings().setValue(SettingsRadio, pRadio);

    mMediaPlayer.setMedia(QUrl(pRadio));
    mMediaPlayer.play();
}

//==============================================================================

void MainWindow::on_franceinfoButton_clicked()
{
    playRadio(FranceInfoRadio);
}

//==============================================================================

void MainWindow::on_nostalgieButton_clicked()
{
    playRadio(NostalgieRadio);
}

//==============================================================================

void MainWindow::on_volumeSlider_valueChanged(int pValue)
{
    QSettings().setValue(SettingsVolume, pValue);

    mMediaPlayer.setVolume(qRound(100.0*QAudio::convertVolume(0.01*pValue,
                                                              QAudio::LogarithmicVolumeScale,
                                                              QAudio::LinearVolumeScale)));
}

//==============================================================================

void MainWindow::trayIconActivated()
{
    // Show ourselves at our cursor's position, correcting it if needed

    show();
    activateWindow();
    raise();

    QPoint pos = QCursor::pos();
    QRect availableGeometry = QGuiApplication::primaryScreen()->availableGeometry();

    move(qMax(0, qMin(pos.x()-(width() >> 1), availableGeometry.width()-width())),
         qMin(pos.y(), availableGeometry.height()-height()));
}

//==============================================================================
// End of file
//==============================================================================
