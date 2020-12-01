// let's create a simple todo list app in c (porting from Python)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* VERSION = "0.3";
const char* LIST_PATH = "list";

int noSwitchIsPresent(int argumentCount) {
	// checks to see if there are arguments
	// 1 arg doesn't count because it is the app name.
	return  (argumentCount == 1);
}

int helpSwitchIsPresent(int argumentCount, char* argumentString) {
	// if there are two arguments and the second argument is equal to "-help" then return 1 (true)
	return (argumentCount == 2) && (!strcmp("-help", argumentString));
}

int listSwitchIsPresent(int argumentCount, char* argumentString) {
	// if there are three arguments and the second argument is equal to "-list" then return 1 (true)
	return (argumentCount == 2) && (!strcmp("-list", argumentString));
}

int addSwitchIsPresent(int argumentCount, char* argumentString) {
	// if there are three arguments and the second argument is equal to "-add" then return 1 (true)
	return (argumentCount == 3) && (!strcmp("-add", argumentString));
}

int rmSwitchIsPresent(int argumentCount, char* argumentString) {
	// if there are three arguments and the second argument is equal to "-rm" then return 1 (true)
	return (argumentCount == 3) && (!strcmp("-rm", argumentString));
}

void displayHelp() {
	printf("\n[TODO LIST HELP - Version %s]\n\n", VERSION);
	printf("Usage:\n");
	printf("todo -help (displays help)\n");
	printf("todo -list (lists all elements)\n");
	printf("todo -add 'something to do'\n");
	printf("todo -rm 3 (removes 3rd element from the list)\n\n");
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
		printf("\nNo elements found. Add some things to do using <todo -add 'something to do'>\n\n"); 
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

void rmElement(char* argumentString) {
	int elementToRemove = atoi(argumentString); // convert arg string (choice of element to remove) to integer
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



int main(int argc, char **argv) {

	if (noSwitchIsPresent(argc)) {
		displayHelp();
	}

	if (helpSwitchIsPresent(argc, argv[1])) {
		displayHelp();
	}

	if (listSwitchIsPresent(argc, argv[1])) {
		displayList();
	}

	if (addSwitchIsPresent(argc, argv[1])) {
		addElement(argv[2]);
		displayList();
	}

	if (rmSwitchIsPresent(argc, argv[1])) {
		rmElement(argv[2]);
		displayList();
	}

	return 0;
}
