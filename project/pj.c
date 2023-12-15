#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#define MAX_BLOCKS 10
#define MAX_PARAMS 3
#define LOG_FILE "./restart.txt"
#define BLOCKS_FILE "./blocks.txt"
#define RESTART 3

typedef struct {
    char name[50];
    char params[MAX_PARAMS][50];

    int paramCount;
    int restartCount;
    time_t startTime;
    char reason[100];
} SoftwareBlock;

SoftwareBlock blocks[MAX_BLOCKS];
int blockCount = 0;

void readBlocksFromFile() {
    FILE* file = fopen(BLOCKS_FILE, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char line[200];
    while (fgets(line, sizeof(line), file) != NULL && blockCount < MAX_BLOCKS) {
        char* token = strtok(line, ";");
        strcpy(blocks[blockCount].name, token);

        token = strtok(NULL, ";");
        int paramIndex = 0;
        while (token != NULL) {
            strcpy(blocks[blockCount].params[paramIndex], token);
            paramIndex++;
            token = strtok(NULL, ";");
        }
        blocks[blockCount].paramCount = paramIndex;
        blockCount++;
    }

    fclose(file);
}

void initializeBlock(SoftwareBlock* block) {
    printf("Initializing block: %s\n", block->name);
    block->startTime = time(NULL);
    strcpy(block->reason, "Init");
}

void restartBlock(SoftwareBlock* block, const char* reason) {
    printf("Restarting block: %s\n", block->name);
    block->restartCount++;
    block->startTime = time(NULL);
    strcpy(block->reason, reason);

    FILE* file = fopen(LOG_FILE, "a");
    if (file == NULL) {
        printf("Error opening log file.\n");
        return;
    }

    // Remove newline character from ctime result
    char* timeStr = ctime(&block->startTime);
    timeStr[strlen(timeStr) - 1] = '\0';

    fprintf(file, "%-15s%-15d%-25s%s\n", block->name, block->restartCount, timeStr, block->reason);

    fclose(file);
}

void childSignalHandler(int signal) {
    pid_t childPid;
    int status;

    while ((childPid = waitpid(-1, &status, WNOHANG)) > 0) {
        int randomIndex = rand() % blockCount;
        SoftwareBlock* blockToRestart = &blocks[randomIndex];

        char restartReason[50];
        if (signal == SIGCHLD) {
            snprintf(restartReason, sizeof(restartReason), "Signal(SIGCHLD)");
        } else if (signal == SIGTERM) {
            snprintf(restartReason, sizeof(restartReason), "Signal(SIGTERM)");
        } else if (signal == SIGINT) {
            snprintf(restartReason, sizeof(restartReason), "Signal(SIGINT)");
        } else {
            snprintf(restartReason, sizeof(restartReason), "Signal(%d, Killed)", signal);
        }

        restartBlock(blockToRestart, restartReason);
    }
}

void spawnChildProcess() {
    pid_t pid = fork();
    if (pid < 0) {
        printf("Error forking process.\n");
        exit(1);
    } else if (pid == 0) {
        sleep(3);
        // Terminate the child process
	kill(getpid(), SIGINT);
	
	exit(0);
    } else {
        signal(SIGCHLD, childSignalHandler);
        signal(SIGTERM, childSignalHandler);
        signal(SIGINT, childSignalHandler);
    }
}

void printBlockStatus() {
    FILE* file = fopen(LOG_FILE, "a");
    if (file == NULL) {
        printf("Error opening log file.\n");
        return;
    }

    fprintf(file, "%-15s%-15s%-25s%s\n", "S/W Block Name", "Restart Count", "Start Time", "Reason");
    for (int i = 0; i < blockCount; i++) {
        SoftwareBlock* block = &blocks[i];
        char* timeStr = ctime(&block->startTime);
        timeStr[strlen(timeStr) - 1] = '\0';  // Remove newline character
        fprintf(file, "%-15s%-15d%-25s%s\n", block->name, block->restartCount, timeStr, block->reason);
    }

    fclose(file);

    printf("%-15s%-15s%-25s%s\n", "S/W Block Name", "Restart Count", "Start Time", "Reason");
    for (int i = 0; i < blockCount; i++) {
        SoftwareBlock* block = &blocks[i];
        char* timeStr = ctime(&block->startTime);
        timeStr[strlen(timeStr) - 1] = '\0';  // Remove newline character
        printf("%-15s%-15d%-25s%s\n", block->name, block->restartCount, timeStr, block->reason);
    }
}

int main() {
    srand(time(NULL));

    readBlocksFromFile();

    for (int i = 0; i < blockCount; i++) {
        initializeBlock(&blocks[i]);
    }

    while (1) {
        sleep(RESTART);
        spawnChildProcess();
        printBlockStatus();
    }

    return 0;
}
