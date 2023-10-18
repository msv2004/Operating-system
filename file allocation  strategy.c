#include <stdio.h>
#include <stdlib.h>

// Define a structure for a disk block
struct DiskBlock {
    int data;
    struct DiskBlock* next;
};

// Define a structure for a file
struct File {
    char filename[100];
    struct DiskBlock* firstBlock;
    struct DiskBlock* lastBlock;
};

// Function to create a new disk block
struct DiskBlock* createDiskBlock(int data) {
    struct DiskBlock* block = (struct DiskBlock*)malloc(sizeof(struct DiskBlock));
    block->data = data;
    block->next = NULL;
    return block;
}

// Function to create a new file
struct File* createFile(const char* filename) {
    struct File* file = (struct File*)malloc(sizeof(struct File));
    snprintf(file->filename, sizeof(file->filename), "%s", filename);
    file->firstBlock = NULL;
    file->lastBlock = NULL;
    return file;
}

// Function to add a block to a file
void addBlockToFile(struct File* file, int data) {
    struct DiskBlock* block = createDiskBlock(data);
    if (file->lastBlock == NULL) {
        file->firstBlock = block;
        file->lastBlock = block;
    } else {
        file->lastBlock->next = block;
        file->lastBlock = block;
    }
}

// Function to display the blocks of a file
void displayFile(struct File* file) {
    printf("File: %s\n", file->filename);
    struct DiskBlock* block = file->firstBlock;
    while (block != NULL) {
        printf("%d ", block->data);
        block = block->next;
    }
    printf("\n");
}

int main() {
    // Create some files and allocate blocks
    struct File* file1 = createFile("file1");
    addBlockToFile(file1, 1);
    addBlockToFile(file1, 2);
    addBlockToFile(file1, 3);

    struct File* file2 = createFile("file2");
    addBlockToFile(file2, 4);
    addBlockToFile(file2, 5);

    // Display the contents of the files
    displayFile(file1);
    displayFile(file2);

    // Clean up and free memory
    free(file1);
    free(file2);

    return 0;
}
