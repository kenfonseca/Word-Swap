#include "word-swapper.h"

// Function to zero buffers
void zero(uint8_t *buffer, uint16_t count){
    uint8_t *p;
    uint16_t i;

    for(i=0, p = buffer; i<count; i++, p++){
        *p = 0;
    }
}

// Function to construct the name of the file to write to
int create_wsFile(uint8_t *file, uint8_t *fileCpy){
    // Buffers to hold parts of the file name
    uint8_t fileName[256];
    uint8_t fileExt[256];
    zero(fileName, sizeof(fileName)-1);
    zero(fileExt, sizeof(fileExt)-1);

    // Copy over the file name and extension
    strncpy((char *)fileName, (char *)file, sizeof(fileName));
    uint8_t Ext = 0, tmp = 0;
    // Search through the original file name
    for(uint8_t i = 0, j = 0; i<strlen((char *)fileName); i++){
        // Find the dot
        if(fileName[i] == '.'){
            Ext = 1;
            tmp = i;
        }
        // Single the extension into a buffer
        if(Ext == 1){
            if(fileName[i]){
                fileExt[j] = fileName[i];
            }
            j++;
        }
    }
    if(Ext == 0){
        // If there is no extension, this is not a file that can be read/written
        printf("No extension found for file\n");
        return 1;
    } else {
        // Single out the name of the file (no extension)
        fileName[tmp] = 0;

        // Assemble the name of the file to copy to with the extension
        strcat((char *)fileCpy, (char *)fileName);
        strcat((char *)fileCpy, "WS");
        strcat((char *)fileCpy, (char *)fileExt);
    }
    return 0;
}

// Function to find and replace a word in a string, and return the amount of times the word was found
int word_replacer(uint8_t *string, uint8_t *word1, uint8_t *word2){
    uint16_t word1Count = 0;
    for(uint8_t i = 0, j = 0; i<strlen((char *)string); i++){
        // Find the word
        if(string[i] == word1[j]){
            j++;
            // Ensure the word is found
            if(j == strlen((char *)word1)){
                // Construct the new line to replace the old one
                uint8_t beginBuf[256], endBuf[256], wFileBuf[256];
                zero(beginBuf, sizeof(beginBuf));
                zero(endBuf, sizeof(endBuf));
                zero(wFileBuf, sizeof(wFileBuf));

                strncpy((char *)beginBuf, (char *)string, i-strlen((char *)word1)+1);
                strncpy((char *)endBuf, (char *)string+strlen((char *)beginBuf)+strlen((char *)word1), sizeof(endBuf)-1);

                zero(string, sizeof(string));
                strcat((char *)string, (char *)beginBuf);
                strcat((char *)string, (char *)word2);
                strcat((char *)string, (char *)endBuf);

                word1Count++;
            }
        } else {
            j = 0;
        }
    }
    return word1Count;
}

// Function to start the program
int ws_program(int argc, char *argv[]){
    uint8_t file[256], getWord[256], setWord[256];
    uint16_t i;

    zero(file, sizeof(file));
    zero(getWord, sizeof(getWord));
    zero(setWord, sizeof(setWord));

    // Check if user entered arguments
    if(argc > 1){
        for(i=0; i<argc; i++){
            if(i == 1){
                strncpy((char *)file, argv[i], 255);
            }
            if(i == 2){
                strncpy((char *)getWord, argv[i], 255);
            }
            if(i == 3){
                strncpy((char *)setWord, argv[i], 255);
            }
        }
    } else {
        printf("Error: no arguments\n");
        return 1;
    }

    // Confirm the correct arguments
    if(!(*file)){
        printf("Error: Must enter a file\n");
        return 1;
    }
    // Make sure the file can be opened
    FILE *fp0;
    fp0 = fopen((char *)file, "r");
    if(fp0 == NULL){
        printf("Error: File pointer for \"%s\" is NULL\nMust be a valid file entry\n", file);
        fclose(fp0);
        return 1;
    }
    printf("File \"%s\" opened for reading...\n", file);
    
    if(!(*getWord)){
        printf("Error: must enter a word to swap\n");
        return 1;
    }
    if(!(*setWord)){
        printf("Error: must enter the replacement word\n");
        return 1;
    }

    // Create the file to write to
    uint8_t fileCpy[256];
    zero(fileCpy, sizeof(fileCpy));
    if(create_wsFile(file, fileCpy) == 1){
        printf("Error: Could not create ws file\n");
        fclose(fp0);
        return 1;
    }
    printf("File \"%s\" created...\n", fileCpy);

    // Open the copied file for writing
    FILE *fp1;
    if(!(*fileCpy)){
        printf("No file \"%s\" to open\n", fileCpy);
        fclose(fp0);
        return 1;
    }
    fp1 = fopen((char *)fileCpy, "w");
    if(fp1 == NULL){
        printf("File pointer for \"%s\" is NULL\n", fileCpy);
        fclose(fp0);
        fclose(fp1);
        return 1;
    }
    printf("File \"%s\" opened for writing...\n", fileCpy);

    // buffer to pass in as an fopen arg
    uint8_t fileBuffer[256];
    zero(fileBuffer, 255);

    // Keep track of how many times the word was found
    uint16_t foundCount = 0;
    // Keep track of the current line
    // uint8_t lineNum = 0;
    // Read from the file pointer
    while((fgets((char *)fileBuffer, sizeof(fileBuffer), fp0) != NULL)){
        // lineNum++;
        uint8_t lineBuf[256];
        zero(lineBuf, sizeof(lineBuf));
        // Copy over line to a buffer that can be manipulated
        strncpy((char *)lineBuf, (char *)fileBuffer, sizeof(lineBuf));
        // Find out if there if the word to replace is in the line and replace it
        foundCount = foundCount + word_replacer(lineBuf, getWord, setWord);
        // Write the new line to the new file
        fprintf(fp1, "%s", (char *)lineBuf);
    }
    if(foundCount > 0){
        printf("\"%s\" was found %d times.\n", getWord, foundCount);
        printf("The word \"%s\" was replaced by the word \"%s\" and written to \"%s\"\n", getWord, setWord, fileCpy);
    } else {
        printf("\"%s\" was not found.\n", getWord);
    }

    fclose(fp0);
    fclose(fp1);

    return 0;
}

int main(int argc, char *argv[]){
    if(ws_program(argc, argv) == 1){
        return 1;
    }

    return 0;
}