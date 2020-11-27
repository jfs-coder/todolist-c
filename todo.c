// let's create a simple todo list app in c (porting from Python)

// check to see if there are args...

// if args is 0 then show "For Help: todo -help"

/* -HELP
 * if there is 1 arg and it matches '-help' then display this:
 *
 * Usage: 
 * todo -list (lists all elements)
 * todo -add 'something to do'
 * todo -rm 3 (removes element 3 from the list)
 */

/* -LIST
 * First we check if there is 1 arg and it matches '-list'
 * Then we check to see if the file exists, if not then print this error...
 * "No entries found. Add some things to do using <python3 todo.py -add 'something to do'>"
 * If it does exist, read the 'list' file and put each line in an array of strings
 * Then printf each line using a for loop. First line should be "[TODO LIST]\n"
 * Don't forget to display a number before the actual line "[1]: Buy more TP."
 * Don't forget to close the file once done.
 */

/* -ADD
 * Check to see if there is 2 args and the 1st one matches '-add' (the 2nd arg will be the element to add to list)
 * Open 'list' file with append mode, then write arg[1] (2nd arg) to the file.
 * Print out that you are adding it: "Adding Entry: -> " + arg[1]
 * Don't forget to close the file once done.
 */

/* -RM
 * Check to see if there are 2 args and the 1st one matches '-rm' (the 2nd arg will be element to remove from list)
 * First we need to read the file and store all the lines in an array
 * Then we echo what element we are removing: "Removing Entry #" + arg[1] + "->" + array[choice -1]
 * Then we 'write mode' to the file using a for loop but SKIPPING the arg[1] element (say 3rd one) 
 * by making a comparison with the current index. if index == choice, then skip writing, effectively
 * removing it from list and by extension the file. Remember to close the files.
 */
  
