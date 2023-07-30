#include <iostream>
#include <fstream>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>
#include <chrono> // For measuring time

void copyMissingFiles(const std::string& parentFolderPath, const std::string& childFolderPath) {
    DIR* parentDir = opendir(parentFolderPath.c_str());
    DIR* childDir = opendir(childFolderPath.c_str());

    if (parentDir && childDir) {
        auto startTime = std::chrono::high_resolution_clock::now(); // Start the timer

        struct dirent* dirEntry;
        while ((dirEntry = readdir(parentDir)) != nullptr) {
            if (dirEntry->d_type == DT_REG) { // Check if it's a regular file
                std::string filename = dirEntry->d_name;
                std::string sourceFilePath = parentFolderPath + "/" + filename;
                std::string destFilePath = childFolderPath + "/" + filename;

                std::ifstream sourceFile(sourceFilePath, std::ios::binary);
                std::ofstream destFile(destFilePath, std::ios::binary);

                if (sourceFile && !destFile) {
                    destFile << sourceFile.rdbuf();
                }

                sourceFile.close();
                destFile.close();
            }
        }

        closedir(parentDir);
        closedir(childDir);

        auto endTime = std::chrono::high_resolution_clock::now(); // Stop the timer
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        std::cout << "Missing files copied successfully in " << duration << " milliseconds." << std::endl;
    } else {
        std::cout << "Failed to open folders." << std::endl;
    }
}

int main() {
    std::string parentFolderPath = "D:\\FileCopier\\parent"; // Replace with the actual parent folder path
    std::string childFolderPath = "D:\\FileCopier\\child";   // Replace with the actual child folder path

    copyMissingFiles(parentFolderPath, childFolderPath);

    return 0;
}
