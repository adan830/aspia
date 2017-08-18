//
// PROJECT:         Aspia Remote Desktop
// FILE:            ui/file_manager_panel.cc
// LICENSE:         Mozilla Public License Version 2.0
// PROGRAMMERS:     Dmitry Chapyshev (dmitry@aspia.ru)
//

#include "ui/file_manager_panel.h"
#include "ui/file_manager.h"
#include "ui/file_manager_helpers.h"
#include "ui/status_code.h"
#include "base/logging.h"

#include <uxtheme.h>

namespace aspia {

static_assert(FileListWindow::kInvalidObjectIndex == DriveListWindow::kInvalidObjectIndex,
              "Values must be equal");

FileManagerPanel::FileManagerPanel(Type type,
                                   std::shared_ptr<FileRequestSenderProxy> sender,
                                   Delegate* delegate)
    : toolbar_(type == Type::LOCAL ?
          FileToolBar::Type::LOCAL : FileToolBar::Type::REMOTE),
      type_(type),
      sender_(sender),
      delegate_(delegate)
{
    // Nothing
}

FilePath FileManagerPanel::GetCurrentPath() const
{
    return drive_list_.CurrentPath();
}

void FileManagerPanel::Refresh()
{
    sender_->SendFileListRequest(This(), GetCurrentPath());
}

LPARAM FileManagerPanel::OnCreate(UINT message, WPARAM wparam, LPARAM lparam, BOOL& handled)
{
    HFONT default_font = AtlGetStockFont(DEFAULT_GUI_FONT);

    CString panel_name;

    if (type_ == Type::LOCAL)
        panel_name.LoadStringW(IDS_FT_LOCAL_COMPUTER);
    else
        panel_name.LoadStringW(IDS_FT_REMOTE_COMPUTER);

    CRect title_rect(0, 0, 200, 20);

    title_.Create(*this, title_rect, panel_name,
                  WS_CHILD | WS_VISIBLE | SS_OWNERDRAW);
    title_.SetFont(default_font);

    drive_list_.CreateDriveList(*this, kDriveListControl);
    toolbar_.CreateFileToolBar(*this);
    file_list_.CreateFileList(*this, kFileListControl);

    CRect status_rect(0, 0, 200, 20);
    status_.Create(*this, status_rect, nullptr,
                   WS_CHILD | WS_VISIBLE | SS_OWNERDRAW);
    status_.SetFont(default_font);

    sender_->SendDriveListRequest(This());
    return 0;
}

LRESULT FileManagerPanel::OnDestroy(UINT message, WPARAM wparam, LPARAM lparam, BOOL& handled)
{
    drive_list_.DestroyWindow();
    file_list_.DestroyWindow();
    toolbar_.DestroyWindow();
    title_.DestroyWindow();
    status_.DestroyWindow();
    return 0;
}

LRESULT FileManagerPanel::OnSize(UINT message, WPARAM wparam, LPARAM lparam, BOOL& handled)
{
    HDWP dwp = BeginDeferWindowPos(5);

    if (!dwp)
        return 0;

    CSize size(lparam);

    toolbar_.AutoSize();

    CRect drive_rect;
    drive_list_.GetWindowRect(drive_rect);

    CRect toolbar_rect;
    toolbar_.GetWindowRect(toolbar_rect);

    CRect title_rect;
    title_.GetWindowRect(title_rect);

    CRect status_rect;
    status_.GetWindowRect(status_rect);

    title_.DeferWindowPos(dwp, nullptr,
                          0, 0,
                          size.cx, title_rect.Height(),
                          SWP_NOACTIVATE | SWP_NOZORDER);

    drive_list_.DeferWindowPos(dwp, nullptr,
                               0, title_rect.Height(),
                               size.cx, drive_rect.Height(),
                               SWP_NOACTIVATE | SWP_NOZORDER);

    toolbar_.DeferWindowPos(dwp, nullptr,
                            0, title_rect.Height() + drive_rect.Height(),
                            size.cx, toolbar_rect.Height(),
                            SWP_NOACTIVATE | SWP_NOZORDER);

    int list_y = title_rect.Height() + toolbar_rect.Height() + drive_rect.Height();
    int list_height = size.cy - list_y - status_rect.Height();

    file_list_.DeferWindowPos(dwp, nullptr,
                              0, list_y,
                              size.cx, list_height,
                              SWP_NOACTIVATE | SWP_NOZORDER);

    status_.DeferWindowPos(dwp, nullptr,
                           0, list_y + list_height,
                           size.cx, status_rect.Height(),
                           SWP_NOACTIVATE | SWP_NOZORDER);

    EndDeferWindowPos(dwp);

    return 0;
}

LRESULT FileManagerPanel::OnDrawItem(UINT message, WPARAM wparam, LPARAM lparam, BOOL& handled)
{
    LPDRAWITEMSTRUCT dis = reinterpret_cast<LPDRAWITEMSTRUCT>(lparam);

    if (dis->hwndItem != title_ && dis->hwndItem != status_)
        return 0;

    int saved_dc = SaveDC(dis->hDC);
    if (!saved_dc)
        return 0;

    // Transparent background.
    SetBkMode(dis->hDC, TRANSPARENT);

    HBRUSH background_brush = GetSysColorBrush(COLOR_WINDOW);
    FillRect(dis->hDC, &dis->rcItem, background_brush);

    WCHAR label[256] = { 0 };
    ::GetWindowTextW(dis->hwndItem, label, _countof(label));

    if (label[0])
    {
        SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));
        DrawTextW(dis->hDC, label, wcslen(label), &dis->rcItem, DT_VCENTER | DT_SINGLELINE);
    }

    RestoreDC(dis->hDC, saved_dc);

    return 0;
}

LRESULT FileManagerPanel::OnDriveChange(WORD code, WORD ctrl_id, HWND ctrl, BOOL& handled)
{
    int object_index = drive_list_.SelectedObject();

    if (object_index == DriveListWindow::kInvalidObjectIndex)
        return 0;

    MoveToDrive(object_index);
    return 0;
}

LRESULT FileManagerPanel::OnListDoubleClock(int ctrl_id, LPNMHDR hdr, BOOL& handled)
{
    int object_index = file_list_.GetObjectUnderMousePointer();

    if (object_index == FileListWindow::kInvalidObjectIndex)
        return 0;

    if (!file_list_.HasFileList())
    {
        MoveToDrive(object_index);
        return 0;
    }

    if (!file_list_.IsValidObjectIndex(object_index))
        return 0;

    if (file_list_.IsDirectoryObject(object_index))
    {
        FilePath path(drive_list_.CurrentPath());
        path.append(file_list_.ObjectName(object_index));
        sender_->SendFileListRequest(This(), path);
    }

    return 0;
}

LRESULT FileManagerPanel::OnFolderUp(WORD code, WORD ctrl_id, HWND ctrl, BOOL& handled)
{
    FilePath path = drive_list_.CurrentPath();

    if (!path.has_parent_path() || path.parent_path() == path.root_name())
    {
        MoveToDrive(DriveListWindow::kComputerObjectIndex);
    }
    else
    {
        sender_->SendFileListRequest(This(), path.parent_path());
    }

    return 0;
}

LRESULT FileManagerPanel::OnFolderAdd(WORD code, WORD ctrl_id, HWND ctrl, BOOL& handled)
{
    file_list_.AddDirectory();
    return 0;
}

LRESULT FileManagerPanel::OnRefresh(WORD code, WORD ctrl_id, HWND ctrl, BOOL& handled)
{
    sender_->SendDriveListRequest(This());
    return 0;
}

LRESULT FileManagerPanel::OnRemove(WORD code, WORD ctrl_id, HWND ctrl, BOOL& handled)
{
    if (!file_list_.HasFileList())
        return 0;

    UINT selected_count = file_list_.GetSelectedCount();
    if (!selected_count)
        return 0;

    CString title;
    title.LoadStringW(IDS_CONFIRMATION);

    CString message;
    message.Format(IDS_FT_DELETE_CONFORM, selected_count);

    if (MessageBoxW(message, title, MB_YESNO | MB_ICONQUESTION) != IDYES)
        return 0;

    for (FileListWindow::Iterator iter(file_list_, FileListWindow::Iterator::SELECTED);
         !iter.IsAtEnd();
         iter.Advance())
    {
        FilePath path = drive_list_.CurrentPath();
        FilePath name = std::experimental::filesystem::u8path(iter.Object().name());

        path.append(name);

        sender_->SendRemoveRequest(This(), path);
    }

    return 0;
}

void FileManagerPanel::MoveToDrive(int object_index)
{
    if (object_index == DriveListWindow::kComputerObjectIndex)
    {
        toolbar_.EnableButton(ID_FOLDER_ADD, FALSE);
        toolbar_.EnableButton(ID_FOLDER_UP, FALSE);
        toolbar_.EnableButton(ID_DELETE, FALSE);
        toolbar_.EnableButton(ID_SEND, FALSE);
        toolbar_.EnableButton(ID_HOME, FALSE);

        file_list_.Read(drive_list_.DriveList());
        drive_list_.SetCurrentPath(FilePath());
    }
    else
    {
        sender_->SendFileListRequest(This(), drive_list_.ObjectPath(object_index));
    }
}

LRESULT FileManagerPanel::OnListEndLabelEdit(int ctrl_id, LPNMHDR hdr, BOOL& handled)
{
    LPNMLVDISPINFOW disp_info = reinterpret_cast<LPNMLVDISPINFOW>(hdr);

    if (!file_list_.HasFileList())
        return 0;

    int object_index = disp_info->item.lParam;

    // New folder.
    if (object_index == FileListWindow::kNewFolderObjectIndex)
    {
        CEdit edit(file_list_.GetEditControl());

        WCHAR buffer[MAX_PATH] = { 0 };
        edit.GetWindowTextW(buffer, _countof(buffer));

        FilePath path = drive_list_.CurrentPath();
        path.append(buffer);

        sender_->SendCreateDirectoryRequest(This(), path);
    }
    else // Rename exists item.
    {
        DCHECK(file_list_.IsValidObjectIndex(object_index));

        // User canceled rename.
        if (!disp_info->item.pszText)
            return 0;

        FilePath old_name = drive_list_.CurrentPath();
        old_name.append(file_list_.ObjectName(object_index));

        FilePath new_name = drive_list_.CurrentPath();
        new_name.append(disp_info->item.pszText);

        sender_->SendRenameRequest(This(), old_name, new_name);
    }

    return 0;
}

LRESULT FileManagerPanel::OnListItemChanged(int ctrl_id, LPNMHDR hdr, BOOL& handled)
{
    UINT count = file_list_.GetSelectedCount();

    if (file_list_.HasFileList())
    {
        bool enable = (count != 0);

        toolbar_.EnableButton(ID_DELETE, enable);
        toolbar_.EnableButton(ID_SEND, enable);
    }

    CString status;
    status.Format(IDS_FT_SELECTED_OBJECT_COUNT, count);
    status_.SetWindowTextW(status);

    return 0;
}

LRESULT FileManagerPanel::OnSend(WORD code, WORD ctrl_id, HWND ctrl, BOOL& handled)
{
    FilePath source_path = drive_list_.CurrentPath();

    // If the path is empty, the panel displays a list of drives.
    if (source_path.empty())
        return 0;

    FileTransfer::FileList file_list;

    // Create a list of files and directories to copy.
    for (FileListWindow::Iterator iter(file_list_, FileListWindow::Iterator::SELECTED);
         !iter.IsAtEnd();
         iter.Advance())
    {
        file_list.emplace_back(iter.Object());
    }

    // If the list is empty (there are no selected items).
    if (file_list.empty())
        return 0;

    // Sending files. After the method is completed, the operation must be completed.
    delegate_->SendFiles(type_, drive_list_.CurrentPath(), file_list);

    return 0;
}

LRESULT FileManagerPanel::OnDriveEndEdit(int ctrl_id, LPNMHDR hdr, BOOL& handled)
{
    PNMCBEENDEDITW end_edit = reinterpret_cast<PNMCBEENDEDITW>(hdr);

    if (end_edit->fChanged && end_edit->iWhy == CBENF_RETURN && end_edit->szText[0])
    {
        sender_->SendFileListRequest(This(), FilePath(end_edit->szText));
    }

    return 0;
}

LRESULT FileManagerPanel::OnHome(WORD code, WORD ctrl_id, HWND ctrl, BOOL& handled)
{
    MoveToDrive(DriveListWindow::kComputerObjectIndex);
    return 0;
}

void FileManagerPanel::OnDriveListReply(std::shared_ptr<proto::DriveList> drive_list,
                                        proto::RequestStatus status)
{
    if (status != proto::REQUEST_STATUS_SUCCESS)
    {
        CString status_string = RequestStatusCodeToString(status);

        CString message;
        message.Format(IDS_FT_OP_BROWSE_DRIVES_ERROR, status_string.GetBuffer(0));
        MessageBoxW(message, nullptr, MB_ICONWARNING | MB_OK);
    }
    else
    {
        drive_list_.Read(std::move(drive_list));

        if (file_list_.HasFileList())
        {
            Refresh();
        }
        else
        {
            MoveToDrive(DriveListWindow::kComputerObjectIndex);
        }
    }
}

void FileManagerPanel::OnFileListReply(const FilePath& path,
                                       std::shared_ptr<proto::FileList> file_list,
                                       proto::RequestStatus status)
{
    if (status != proto::REQUEST_STATUS_SUCCESS)
    {
        CString status_string = RequestStatusCodeToString(status);

        CString message;
        message.Format(IDS_FT_BROWSE_FOLDERS_ERROR, path.c_str(), status_string.GetBuffer(0));
        MessageBoxW(message, nullptr, MB_ICONWARNING | MB_OK);
    }
    else
    {
        toolbar_.EnableButton(ID_FOLDER_ADD, TRUE);
        toolbar_.EnableButton(ID_FOLDER_UP, TRUE);
        toolbar_.EnableButton(ID_HOME, TRUE);

        file_list_.Read(std::move(file_list));
        drive_list_.SetCurrentPath(path);
    }
}

void FileManagerPanel::OnDirectorySizeReply(const FilePath& path,
                                            uint64_t size,
                                            proto::RequestStatus status)
{
    // TODO
}

void FileManagerPanel::OnCreateDirectoryReply(const FilePath& path, proto::RequestStatus status)
{
    if (status != proto::RequestStatus::REQUEST_STATUS_SUCCESS)
    {
        CString status_string = RequestStatusCodeToString(status);

        CString message;
        message.Format(IDS_FT_OP_CREATE_FOLDER_ERROR, path.c_str(), status_string);
        MessageBoxW(message, nullptr, MB_ICONWARNING | MB_OK);
    }
    else
    {
        Refresh();
    }
}

void FileManagerPanel::OnRemoveReply(const FilePath& path, proto::RequestStatus status)
{
    if (status != proto::RequestStatus::REQUEST_STATUS_SUCCESS)
    {
        CString status_string = RequestStatusCodeToString(status);

        CString message;
        message.Format(IDS_FT_OP_REMOVE_ERROR, path.c_str(), status_string);
        MessageBoxW(message, nullptr, MB_ICONWARNING | MB_OK);
    }
    else
    {
        Refresh();
    }
}

void FileManagerPanel::OnRenameReply(const FilePath& old_name,
                                     const FilePath& new_name,
                                     proto::RequestStatus status)
{
    if (status != proto::RequestStatus::REQUEST_STATUS_SUCCESS)
    {
        CString status_string = RequestStatusCodeToString(status);

        CString message;
        message.Format(IDS_FT_OP_RENAME_ERROR, old_name.c_str(), new_name.c_str(), status_string);
        MessageBoxW(message, nullptr, MB_ICONWARNING | MB_OK);
    }
    else
    {
        Refresh();
    }
}

void FileManagerPanel::OnFileUploadReply(const FilePath& file_path, proto::RequestStatus status)
{
    DLOG(FATAL) << "Unexpected reply: file upload request";
}

void FileManagerPanel::OnFileDownloadReply(const FilePath& file_path, proto::RequestStatus status)
{
    DLOG(FATAL) << "Unexpected reply: download request";
}

void FileManagerPanel::OnFilePacketSended(uint32_t flags, proto::RequestStatus status)
{
    DLOG(FATAL) << "Unexpected reply: file packet sended";
}

void FileManagerPanel::OnFilePacketReceived(std::shared_ptr<proto::FilePacket> file_packet,
                                            proto::RequestStatus status)
{
    DLOG(FATAL) << "Unexpected reply: file packet received";
}

} // namespace aspia
