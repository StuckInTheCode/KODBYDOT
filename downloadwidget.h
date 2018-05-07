/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QFrame>
#include <QTime>
#include <QWebEngineDownloadItem>
#include "ui_downloadwidget.h"
#include <QFileInfo>
#include <QUrl>
//QT_BEGIN_NAMESPACE
//class QWebEngineDownloadItem;
//QT_END_NAMESPACE

class DownloadWidget final : public QFrame, Ui_DownloadWidget
{
    Q_OBJECT
public:
    DownloadWidget(QWebEngineDownloadItem *download, QWidget *parent = nullptr)
        :QFrame(parent)
       , m_download(download)
       , m_timeAdded(QTime::currentTime())
   {
       setupUi(this);
       m_dstName->setText(QFileInfo(m_download->path()).fileName());
       m_srcUrl->setText(m_download->url().toDisplayString());

       connect(m_cancelButton, &QPushButton::clicked,
               [this](bool) {
           if (m_download->state() == QWebEngineDownloadItem::DownloadInProgress)
               m_download->cancel();
           //else
           //    emit removeClicked(this);
       });

       connect(m_download, &QWebEngineDownloadItem::downloadProgress,
               this, &DownloadWidget::updateWidget);

       connect(m_download, &QWebEngineDownloadItem::stateChanged,
               this, &DownloadWidget::updateWidget);

       //updateWidget();
   }
    void updateWidget()
    {
        if(m_download->isFinished())
            this->close();
        //this->m_progressBar->
    }


private:

    QWebEngineDownloadItem *m_download;
    QTime m_timeAdded;
};

#endif // DOWNLOADWIDGET_H
