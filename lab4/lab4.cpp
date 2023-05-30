#include <iostream>
#include <filesystem>
#include <string>
#include <Windows.h>

namespace fs = std::filesystem;

void PrintFileAttributes(const fs::directory_entry& file) {
    std::wstring filePath = file.path().wstring();
    DWORD attributes = GetFileAttributesW(filePath.c_str());
    if (attributes != INVALID_FILE_ATTRIBUTES) {
        std::cout << "Атрибути: " << std::endl;
        if (attributes & FILE_ATTRIBUTE_ARCHIVE) {
            std::cout << "Архівний " << std::endl;
        }
        else std::cout << "Не архівний " << std::endl;
        if (attributes & FILE_ATTRIBUTE_HIDDEN) {
            std::cout << "Прихований " << std::endl;
        }
        else std::cout << "Не прихований " << std::endl;
        if (attributes & FILE_ATTRIBUTE_READONLY) {
            std::cout << "Тільки для читання " << std::endl;
        }
        else std::cout << "Не тільки для читання " << std::endl;
    }
    else {
        std::cout << "Не вдалося отримати атрибути файлу." << std::endl;
    }
}

void CountFilesInDirectory(const std::string& directoryPath, const std::string& extension = "") {
    int totalFiles = 0;

    for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
        if (fs::is_directory(entry)) {

            std::string subdirectoryName = entry.path().filename().string();

            int subdirectoryFileCount = 0;
            for (const auto& subentry : fs::directory_iterator(entry)) {
                if (fs::is_regular_file(subentry)) {
                    if (extension.empty() || subentry.path().extension() == extension) {
                        ++subdirectoryFileCount;
                        ++totalFiles;

                        std::cout << "Ім'я файлу: " << subentry.path().filename().string() << std::endl;

                        PrintFileAttributes(subentry);
                    }
                }
            }

            std::cout << "Підкаталог: " << subdirectoryName << std::endl;
            std::cout << "Кількість файлів у підкаталозі: " << subdirectoryFileCount << std::endl;
            std::cout << std::endl;
        }
    }

    std::cout << "Загальна кількість файлів у підкаталогах: " << totalFiles << std::endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string directoryPath;
    std::cout << "Введіть шлях до директорії: ";
    std::getline(std::cin, directoryPath);

    std::string extension;
    std::cout << "Введіть розширення файлів (або натисніть Enter, щоб не обмежувати за розширенням): ";
    std::getline(std::cin, extension);

    std::cout << std::endl;
    CountFilesInDirectory(directoryPath, extension);

    return 0;
}