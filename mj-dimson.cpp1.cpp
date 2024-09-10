#include <iostream>
#include <direct.h>
#include <windows.h>
#include <string>
#include <vector>
#include <dirent.h>

using namespace std;
 
void displayMenu() {
    cout << "     MAIN MENU   \n";
    cout << "-----------------------\n";
    cout << "1. Display List of Files\n";
    cout << "2. Create New Directory\n";
    cout << "3. Change the Working Directory\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

void listAllFiles() {
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            cout << ent->d_name << endl;
        }
        closedir(dir);
    } else {
        perror("Error opening directory");
    }
}


void listFilesByExtension(const string& extension) {
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string fileName = ent->d_name;
            if (fileName.find(extension, fileName.length() - extension.length()) != string::npos) {
                cout << fileName << endl;
            }
        }
        closedir(dir);
    } else {
        perror("Error opening directory");
    }
}


void listFilesByPattern(const string& pattern) {
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string fileName = ent->d_name;
            if (fileName.find(pattern) != string::npos) {
                cout << fileName << endl;
            }
        }
        closedir(dir);
    } else {
        perror("Error opening directory");
    }
}


void listFiles() {
    cout << "\nList Files Menu:\n";
    cout << "1. List all files\n";
    cout << "2. List files by extension\n";
    cout << "3. List files by pattern\n";
    cout << "Choose an option: ";
    
    int choice;
    cin >> choice;
    string extension, pattern;

    switch (choice) {
        case 1:
            listAllFiles();
            break;
        case 2:
            cout << "Enter the file extension (e.g., .txt): ";
            cin >> extension;
            listFilesByExtension(extension);
            break;
        case 3:
            cout << "Enter the file pattern (e.g., moha): ";
            cin >> pattern;
            listFilesByPattern(pattern);
            break;
        default:
            cout << "Invalid option.\n";
            break;
    }
}


void createDirectory() {
    string dirName;
    cout << "Enter the name of the new directory: ";
    cin >> dirName;

    if (_mkdir(dirName.c_str()) == 0) {
        cout << "Directory created successfully.\n";
    } else {
        perror("Error creating directory");
    }
}


void changeDirectory() {
    cout << "\nChange Directory Menu:\n";
    cout << "1. Move one step back (to the parent directory)\n";
    cout << "2. Move to the root directory\n";
    cout << "3. Move to a specific directory\n";
    cout << "Choose an option: ";
    
    int choice;
    cin >> choice;
    string dirName;

    switch (choice) {
        case 1:
            if (_chdir("..") == 0) {
                cout << "Moved to parent directory.\n";
            } else {
                perror("Error changing directory");
            }
            break;
        case 2:
            if (_chdir("\\") == 0) {
                cout << "Moved to root directory.\n";
            } else {
                perror("Error changing directory");
            }
            break;
        case 3:
            cout << "Enter the name of the directory: ";
            cin >> dirName;
            if (_chdir(dirName.c_str()) == 0) {
                cout << "Moved to " << dirName << " directory.\n";
            } else {
                perror("Error changing directory");
            }
            break;
        default:
            cout << "Invalid option.\n";
            break;
    }
}

int main() {
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                listFiles();
                break;
            case 2:
                createDirectory();
                break;
            case 3:
                changeDirectory();
                break;
            case 4:
                cout << "Exiting the program...\n";
                return 0;
            default:
                cout << "Invalid option, please try again.\n";
        }
    }
    return 0;
}
