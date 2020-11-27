// let's create a simple todo list app in c (porting from Python)
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	// check to see if there are args...
	// if args is 1 then show "For Help: todo -help"
	if (argc == 1) {
		printf("\nFor Help: todo -help\n\n");
	}

	/* -HELP
	 * if there 2 args and 2nd one matches '-help' then display this:
	 *
	 * Usage:
	 * todo -list (lists all elements)
	 * todo -add 'something to do'
	 * todo -rm 3 (removes 3rd element from the list)
	 */

	if ( (argc == 2) && (!strcmp("-help", argv[1])) ) {
		printf("\nUsage:\n");
		printf("todo -list (lists all elements)\n");
		printf("todo -add 'something to do'\n");
		printf("todo -rm 3 (removes 3rd element from the list)\n\n");
	}

	/* -LIST
	 * First we check if there are 2 args and the 2nd one matches '-list'
	 * Then we check to see if the file exists, if not then print this message...
	 * "No entries found. Add some things to do using <todo -add 'something to do'>"
	 * If it does exist, read the 'list' file and put each line in an array of strings
	 * Then printf each line using a for loop. First line should be "[TODO LIST]\n"
	 * Don't forget to display a number before the actual line "[1]: Buy more TP."
	 * Don't forget to close the file once done.
	 */

	if ( (argc == 2) && (!strcmp("-list", argv[1])) ) {
		// check to see if the 'list' file exists and if so read and display entries, else print msg
		FILE *todoFile;
		if( (todoFile = fopen("list", "r"))) {
			printf("[TODO LIST]\n\n");
			char line[256];
			int counter = 1;
			while (fgets(line, sizeof(line), todoFile)) {
				printf("[%d]: %s\n", counter, line);
				counter++;
			}
			fclose(todoFile);
		}
		else {
			printf("\nNo entries found. Add some things to do using <todo -add 'something to do'>\n\n"); 
		}
	
	}

	/* -ADD
	 * Check to see if there is 3 args and the 2nd one matches '-add' (the 3rd arg will be the element to add to list)
	 * Open 'list' file with append mode, then write arg[3] (3rd arg) to the file.
	 * Print out that you are adding it: "Adding Entry: -> " + arg[3]
	 * Don't forget to close the file once done.
	 */

	/* -RM
	 * Check to see if there are 3 args and the 2nd one matches '-rm' (the 2nd arg will be element to remove from list)
	 * First we need to read the file and store all the lines in an array
	 * Then we echo what element we are removing: "Removing Entry #" + arg[1] + "->" + array[choice -1]
	 * Then we 'write mode' to the file using a for loop but SKIPPING the arg[1] element (say 3rd one) 
	 * by making a comparison with the current index. if index == choice, then skip writing, effectively
	 * removing it from list and by extension the file. Remember to close the files.
	 */

	return 0;
}
