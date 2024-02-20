#define _CRT_SECURE_NO_WARNINGS  //suppress warning in Visual Studio (for example: fopen)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_CONTENT_LENGTH 1024
#define MAX_FILES_IN_DIR 10

typedef struct {
    char name[MAX_NAME_LENGTH];
} File;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int num_files;
    File files[MAX_FILES_IN_DIR];
} Directory;

//create a new file
void createFile(Directory* currentDir, const char* filename) {
    if (currentDir->num_files < MAX_FILES_IN_DIR) {
        FILE* file = fopen(filename, "w");
        fclose(file);

        File newFile;
        strcpy(newFile.name, filename);
        currentDir->files[currentDir->num_files++] = newFile;
        printf("File %s created successfully.\n", filename);
    }
    else {
        printf("Directory is full. Cannot create more files.\n");
    }
}

//delete a file
void deleteFile(Directory* currentDir, const char* filename) {
    int i;
    for (i = 0; i < currentDir->num_files; i++) {
        if (strcmp(currentDir->files[i].name, filename) == 0) {
            remove(filename);
            //shift files to fill the gap
            for (int j = i; j < currentDir->num_files - 1; j++) {
                currentDir->files[j] = currentDir->files[j + 1];
            }
            currentDir->num_files--;
            printf("File %s deleted successfully.\n", filename);
            return;
        }
    }
    printf("File %s not found.\n", filename);
}

//list the files in the current directory
void listFiles(Directory* currentDir) {
    printf("Files in %s directory:\n", currentDir->name);
    for (int i = 0; i < currentDir->num_files; i++) {
        printf("%s\n", currentDir->files[i].name);
    }
}

//read the content of a file
void readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        char buffer[MAX_CONTENT_LENGTH];
        while (fgets(buffer, MAX_CONTENT_LENGTH, file) != NULL) {
            printf("%s", buffer);
        }
        fclose(file);
    }
    else {
        printf("File %s not found.\n", filename);
    }
}

//write content to a file
void writeFile(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%s", content);
        fclose(file);
        printf("Content written to %s successfully.\n", filename);
    }
    else {
        printf("Could not open file %s for writing.\n", filename);
    }
}

int main() {
    Directory rootDir;
    strcpy(rootDir.name, "root");
    rootDir.num_files = 0;
    Directory* currentDir = &rootDir;

    char command[20];
    char arg1[MAX_NAME_LENGTH];
    char arg2[MAX_CONTENT_LENGTH];

    while (1) {
        printf("\nEnter command: ");
        scanf("%s", command);

        if (strcmp(command, "create_file") == 0) {
            scanf("%s", arg1);
            createFile(currentDir, arg1);
        }

        else if (strcmp(command, "delete_file") == 0) {
            scanf("%s", arg1);
            deleteFile(currentDir, arg1);
        }

        else if (strcmp(command, "list_files") == 0) {
            listFiles(currentDir);
        }

        else if (strcmp(command, "read_file") == 0) {
            scanf("%s", arg1);
            readFile(arg1);
        }

        else if (strcmp(command, "write_file") == 0) {
            scanf("%s", arg1);
            scanf(" %[^\n]s", arg2); //read the content with spaces
            writeFile(arg1, arg2);
        }

        else if (strcmp(command, "exit") == 0) {
            break;
        }

        else {
            printf("Invalid command. Try again.\n");
        }
    }
    return 0;
}
