#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define CREDENTIALS_FILE "~/.shipcap"
#define MAX_PATH_LENGTH 256
#define REMOTE_BUCKET "/home/grad1/"

int readCredentials(char* username, char* password) {
    FILE* file = fopen(CREDENTIALS_FILE, "r");
    if (file == NULL) {
        return -1; // Error opening file
    }

    // Read username and password (assuming they are stored one per line)
    if (fgets(username, MAX_PATH_LENGTH, file) == NULL) {
        fclose(file);
        return -1; // Error reading username
    }
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    if (fgets(password, MAX_PATH_LENGTH, file) == NULL) {
        fclose(file);
        return -1; // Error reading password
    }
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    fclose(file);
    return 0;
}

void createDirectoryIfNotExists(const char* dirPath) {
    struct stat st;
    if (stat(dirPath, &st) == -1) {
        // Directory does not exist, create it
        mkdir(dirPath, 0755);
    }
}

int main(int argc, char *argv[]) {
    int verbose = 0; // Initialize verbose flag to false

    if (argc == 4 && strcmp(argv[1], "--verbose") == 0) {
        verbose = 1; // Set verbose flag to true
        argc--; // Decrement argc to skip the verbose argument
        argv++;
    }

    if (argc != 3 && argc != 2) {
        fprintf(stderr, "Usage: %s [--verbose] [push <filename> | pull <destination_dir>]\n", argv[0]);
        return 1;
    }

    char username[MAX_PATH_LENGTH];
    char password[MAX_PATH_LENGTH];
    char remote_path[MAX_PATH_LENGTH];
    strcat(remote_path, username);
    strcat(remote_path, "/bucket");

    // Read credentials from ~/.shipcap
    if (readCredentials(username, password) != 0) {
        fprintf(stderr, "Error reading credentials from ~/.shipcap\n");
        return 1;
    }

    if (strcmp(argv[1], "push") == 0 && argc == 3) {
        // Construct an SCP command to copy a local file to the remote bucket
        char scpCommand[MAX_PATH_LENGTH * 2];
        snprintf(scpCommand, sizeof(scpCommand), "scp -v %s %s@csa1.bu.edu:%s", argv[2], username, remote_path);

        if (verbose) {
            printf("Executing command: %s\n", scpCommand);
        }

        // Use system() to execute the SCP command
        if (system(scpCommand) != 0) {
            fprintf(stderr, "Error copying file\n");
            return 1;
        }
    } else if (strcmp(argv[1], "pull") == 0 && argc == 3) {
        // Create the destination directory if it doesn't exist
        createDirectoryIfNotExists(argv[2]);

        // Construct an SCP command to copy files from the remote bucket to the local directory
        char scpCommand[MAX_PATH_LENGTH * 2];
        snprintf(scpCommand, sizeof(scpCommand), "scp -v -r %s@csa1.bu.edu:%s/* %s", username, remote_path, argv[2]);

        if (verbose) {
            printf("Executing command: %s\n", scpCommand);
        }

        // Use system() to execute the SCP command
        if (system(scpCommand) != 0) {
            fprintf(stderr, "Error copying files\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s [--verbose] [push <filename> | pull <destination_dir>]\n", argv[0]);
        return 1;
    }

    return 0;
}
