// let's create a simple todo list app in c (porting from Python)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* VERSION = "0.5";
// const char* LIST_PATH = "/home/ec2-user/bin/.list";
const char* LIST_PATH = "list";

int checkWhichSwitchIsPresent(int argumentCount, int argumentNumber, char* argumentString, char* argSwitch) {
	return  (argumentCount == argumentNumber && (!strcmp(argumentString, argSwitch)));
}

void displayHelp() {
	printf("\n[TODO LIST HELP - Version %s]\n\n", VERSION);
	printf("Usage:\n");
	printf("todo help (displays help)\n");
	printf("todo list (lists all elements)\n");
	printf("todo add 'something to do'\n");
	printf("todo rm 3 (removes 3rd element from the list)\n");
	printf("todo swap 3 'new replacement text' (swaps an entry for a new string text)\n\n");
}

void displayList() {
	// check to see if the '.list' file exists and if so read and display elements, else print msg
	FILE *todoFile;
	if( (todoFile = fopen(LIST_PATH, "r"))) {
		printf("\n[TODO LIST - Version %s]\n\n", VERSION);
		char line[256];
		int counter = 1;
		while (fgets(line, sizeof(line), todoFile)) {
			printf("[%d]: %s\n", counter, line);
			counter++;
		}
		fclose(todoFile);
	}
	else {
		printf("\nNo elements found. Add some things to do using <todo add 'something to do'>\n\n"); 
	}
}

void addElement(char* argumentString) {
	// Open file "list" and append/write to it the entry provided
	FILE *todoFile;
	todoFile = fopen(LIST_PATH, "a");
	printf("\nAdding Entry: -> %s\n", argumentString);
	fputs(argumentString, todoFile);
	// here we have to add a NEWLINE manually because fputs doesn't do it automatically on our string.
	fputs("\n", todoFile);
	fclose(todoFile);
}

void rmElement(char* argumentNumber) {
	int elementToRemove = atoi(argumentNumber); // convert arg string (choice of element to remove) to integer
	FILE *todoFile;
	if ((todoFile = fopen(LIST_PATH, "r"))) {
		char line[50][256];
		int counter = 0; // used to iterate lines
		int lineCounter = 0; // used to find out how many lines we are dealing with
		while (fgets(line[counter], sizeof(line[counter]), todoFile)) {
			counter++;
			lineCounter++;
		}
		fclose(todoFile);

		// write to the file, but skipping the one entry being removed.
		todoFile = fopen(LIST_PATH, "w");
		int i;
		for (i = 0; i < lineCounter; i++) {
			if(i+1 == elementToRemove) {
				printf("\nRemoving Entry #%d -> %s", i+1, line[i]);
				continue; // skip adding it to the file, effectively removing it.
			}
			fputs(line[i], todoFile);
		}
		fclose(todoFile);
	}
}

void swapElement(char* argumentNumber, char* argumentString) {
	int elementToSwap = atoi(argumentNumber);
	FILE *todoFile;
	if ((todoFile = fopen(LIST_PATH, "r"))) {
		char line[50][256];
		int counter = 0; // used to iterate lines
		int lineCounter = 0; // used to find out how many lines we are dealing with
		while (fgets(line[counter], sizeof(line[counter]), todoFile)) {
			counter++;
			lineCounter++;
		}
		fclose(todoFile);

		// write to the file, but swapping the one entry being replaced.
		todoFile = fopen(LIST_PATH, "w");
		int i;
		for (i = 0; i < lineCounter; i++) {
			if(i+1 == elementToSwap) {
				printf("\nSwaping Entry #%d -> %s", i+1, line[i]);
			        printf("With Entry -> %s\n", argumentString);
				fputs(argumentString, todoFile); // here we write the replacement string and then continue to skip the real line
				fputs("\n", todoFile); // here we add a newline because fputs doesn't do it on its own. important for file format.
				continue; // skip adding it to the file, effectively swaping entry.
			}
			fputs(line[i], todoFile);
		}
		fclose(todoFile);
	}
}

int main(int argc, char **argv) {
	// if there are less than 2 arguments, then that means no switches present.
	if (argc == 1) {
		displayHelp();
	}

	if (checkWhichSwitchIsPresent(argc, 2, argv[1], "help")) {
		displayHelp();
	}

	if (checkWhichSwitchIsPresent(argc, 2, argv[1], "list")) {
		displayList();
	}

	if (checkWhichSwitchIsPresent(argc, 3, argv[1], "add")) {
		addElement(argv[2]);
		displayList();
	}

	if (checkWhichSwitchIsPresent(argc, 3, argv[1], "rm")) {
		rmElement(argv[2]);
		displayList();
	}

	if (checkWhichSwitchIsPresent(argc, 4, argv[1], "swap")) {
		swapElement(argv[2], argv[3]);
		displayList();
	}

	if (checkWhichSwitchIsPresent(argc, 2, argv[1], "secret")) {
		printf("\nDo you know the way?\n\n");
	}

	return 0;
}
