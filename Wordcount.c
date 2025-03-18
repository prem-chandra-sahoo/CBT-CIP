#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>  // For strlen()

#define MAX_LINE 100
#define MAX_LENGTH 1000

// Function to count the number of words in a line
int count_words(const char *str);

// Function to count the number of characters in a line
int count_characters(const char *str);

// Function to count words, lines, and characters in a file
void countFileStats(FILE *file, int *lineCount, int *wordCount, int *charCount);

int main()
{
    char lines[MAX_LINE][MAX_LENGTH];
    int num_lines = 0;

    // Prompt user for input
    printf("Enter your text (end with an empty line):\n");

    // Read lines of text until an empty line is encountered or maximum lines are reached
    while (num_lines < MAX_LINE && fgets(lines[num_lines], MAX_LENGTH, stdin) && lines[num_lines][0] != '\n')
    {
        // Remove the newline character at the end of the line if it exists
        size_t len = strlen(lines[num_lines]);
        if (len > 0 && lines[num_lines][len - 1] == '\n')
        {
            lines[num_lines][len - 1] = '\0'; // Remove the newline character
        }
        num_lines++;
    }

    int total_words = 0;
    int total_characters = 0;

    // Count the total number of words and characters
    for (int i = 0; i < num_lines; i++)
    {
        total_words += count_words(lines[i]);
        total_characters += count_characters(lines[i]);
    }
    // count words, lines, and characters in a file
    char filename[100];
    FILE *file;
    int lineCount = 0, wordCount = 0, charCount = 0;

    // Ask the user for the file name
    printf("Enter the name of the file to analyze (with extension, e.g., text.txt): ");
    scanf("%s", filename);

    // Open the file
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not open file %s. Please check the file path and try again.\n", filename);
        return 1; // Exit the program if file cannot be opened
    }

    // Call the function to count lines, words, and characters
    countFileStats(file, &lineCount, &wordCount, &charCount);

    // Close the file
    fclose(file);

    // Output the results
    printf("\nTotal number of lines: %d\n", num_lines);
    printf("Total number of words: %d\n", total_words);
    printf("Total number of characters: %d\n", total_characters);



    // Display the results to the user
    printf("\n--- File Analysis ---\n");
    printf("Lines: %d\n", lineCount);
    printf("Words: %d\n", wordCount);
    printf("Characters: %d\n", charCount);

    return 0;

}

// Function to count words in a string
int count_words(const char *str)
{
    int count = 0;
    int in_word = 0;

    // Traverse through each character of the string
    while (*str)
    {
        if (isspace(*str))  // If the character is whitespace, we are no longer in a word
        {
            in_word = 0;
        }
        else if (!in_word)  // If we are not already in a word, count this as the start of a word
        {
            count++;
            in_word = 1;  // We are inside a word now
        }
        str++;
    }
    return count;
}

// Function to count characters in a string
int count_characters(const char *str)
{
    int count = 0;
    // Traverse through each character of the string
    while (*str)
    {
        count++;  // Count the character
        str++;
    }
    return count;
}


// Function to count lines, words, and characters
void countFileStats(FILE *file, int *lineCount, int *wordCount, int *charCount) {
    char ch;
    int inWord = 0; // Flag to track if we are inside a word

    // Read the file character by character
    while ((ch = fgetc(file)) != EOF) {
        (*charCount)++; // Count each character

        // Count lines: Increment lineCount for every newline character
        if (ch == '\n') {
            (*lineCount)++;
        }

        // Count words: A word is a sequence of non-space characters
        if (isalpha(ch) || ch == '\'' || ch == '-') {
            if (!inWord) {  // We are starting a new word
                inWord = 1;
                (*wordCount)++;
            }
        } else {
            inWord = 0;  // We are no longer inside a word
        }
    }

    // Handle the case where the last line doesn't end with a newline
    if (ftell(file) > 0) {
        (*lineCount)++;
    }
}
