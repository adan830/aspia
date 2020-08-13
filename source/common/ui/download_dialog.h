//
// Aspia Project
// Copyright (C) 2020 Dmitry Chapyshev <dmitry@aspia.ru>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef COMMON__UI__DOWNLOAD_DIALOG_H
#define COMMON__UI__DOWNLOAD_DIALOG_H

#include "base/macros_magic.h"
#include "ui_download_dialog.h"

#include <QFile>
#include <QNetworkAccessManager>

namespace common {

class DownloadDialog : public QDialog
{
    Q_OBJECT

public:
    DownloadDialog(const QUrl& url, QFile& file, QWidget* parent = nullptr);
    ~DownloadDialog() = default;

private:
    Ui::DownloadDialog ui;

    QNetworkAccessManager network_manager_;
    QFile& file_;

    DISALLOW_COPY_AND_ASSIGN(DownloadDialog);
};

} // namespace common

#endif // COMMON__UI__DOWNLOAD_DIALOG_H