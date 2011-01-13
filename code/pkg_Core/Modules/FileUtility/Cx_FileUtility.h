// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _X3_UTILITY_FILEUTILITY_H
#define _X3_UTILITY_FILEUTILITY_H

#include <Ix_FileUtility.h>
#include <Ix_FileVersion.h>

class Cx_FileUtility
    : public Ix_FileUtility
    , public Ix_FileVersion
{
public:
    Cx_FileUtility();
    virtual ~Cx_FileUtility() {}

public:
    // From Ix_FileUtility
    virtual bool IsPathFileExists(const wchar_t* pszFileName, bool bWrite = false);
    virtual bool IsPath(const wchar_t* pszFileName, bool bCheckExists = false);
    virtual bool CreateDirectory(const wchar_t* pszFileName, bool bIsPath);
    virtual bool VerifyFileCanWrite(const wchar_t* pszFileName);
    virtual bool DeletePathFile(const wchar_t* pszFileName, bool bRecycle = false);
    virtual bool MovePathFile(const wchar_t* pszOldFile, const wchar_t* pszNewFile);
    virtual bool RenamePathFile(const wchar_t* pszOldFile, const wchar_t* pszNewFile);
    virtual bool CopyPathFile(const wchar_t* pszOldFile, const wchar_t* pszNewFile);
    virtual void SetMsgBoxOwnerWnd(HWND hWnd);
    virtual HWND GetMsgBoxOwnerWnd();
    virtual std::wstring RelToAbs(const wchar_t* pszRel, bool bRelIsFile, 
        const wchar_t* pszBase = NULL, bool bBaseIsFile = true);
    virtual std::wstring AbsToRel(const wchar_t* pszAbs, bool bAbsIsFile, 
        const wchar_t* pszBase = NULL, bool bBaseIsFile = true);
    virtual std::wstring ChangeFileNameSuffix(const wchar_t* pszFileName, const wchar_t* pszSuffix);
    virtual std::wstring GetFileTitle(const wchar_t* pszFileName);
    virtual std::wstring GetFileName(const wchar_t* pszFileName);
    virtual std::wstring GetExtension(const wchar_t* pszFileName);
    virtual std::wstring GetPathOfFile(const wchar_t* pszFileName);
    virtual std::wstring MakeFileName(const std::wstring& wstrPath, 
        const std::wstring& wstrFileTitle, const std::wstring& wstrExtName);
    virtual std::wstring CreateFileName(const std::wstring& wstrPath, 
        const std::wstring& wstrPrefix, const std::wstring& wstrExtName, 
        bool bReturnRel = true);
    virtual std::wstring GetModifyTime(const std::wstring& wstrFileName);
    virtual ULONG GetFileSize(const std::wstring& wstrFileName);
    virtual int CompareFileName(const wchar_t* pszFileName1, const wchar_t* pszFileName2, 
        long* pSamePartCount = NULL);

    // From Ix_FileVersion
    virtual bool GetFileVersion(std::wstring& version, const std::wstring& filename);
    virtual bool GetFileVersion(WORD& ver1, WORD& ver2, 
        WORD& ver3, WORD& ver4, const std::wstring& filename);
    virtual bool GetFileDescription(std::wstring& description, const std::wstring& filename);

private:
    bool TwoFileOperation(const wchar_t* pszOldFile, const wchar_t* pszNewFile, UINT wFunc);

private:
    HWND    m_hMsgBoxOwnerWnd;
};

#endif // _X3_UTILITY_FILEUTILITY_H