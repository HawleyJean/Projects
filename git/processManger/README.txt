There are 3 files that add up to the program that manages processes from New, to Running, Rea
dy, Blocked and Exit states. Amongst these 3 files include :
   list.h =  an h file that lists methods useable by c classes.
   list.c =  a c program with multiple list functionalities and implementations
   process.c = c program with a main class that handles signals, and, using the list class, c
oordinates process structs that move from multiple states ; New, Ready, Running, Blocked and
Exit.

Designing a process manager under the 5 state model involved developing 3 seperate functions, eachfunction building upon an important element of process management. There is a signal fun
ction that amounts to a number of signal interrupt handling "void sig_handler". Depending on
the signal received, 
        SIGUSR1 allows prints all states of all processes, giving a concurrent status of wher
e the processes are located.
        SIGUSR2 cuts a process in the running state, and adding it to the blocked queue.
        SIGINT discontinues the processes and ejects the program.

The alarm_bells function allows for movement of processes to be made between states. At every
 SIGALARM, any new processes are added, one at a time, to the list of READY processes. All th
e while, the program checks if there are any RUNNING state processes, and if there are, then the currently RUNNING process' lifeTime decrements by 1, and the processedTime, initially 0, increases by 1. 
   This whileloop checks if the processedTime has equaled the running time, When it has it will remove the running state list's only node, which is the running process, and attatch it to the end of the ready list. 
   
  Regardless if the processed time variable equates to the running time, this while loop checks for the Lifetime of the process. If it reaches 0, then the running process is sent to the Exit state list. Every alarm signal, the exit state process removes one node in its list starting at its head. 

  Withen this signal handler, however, the moment the Running State List is empty, the head node of the READY state will be sent into the RUNNING state list. 

 In the signal Handler, if SIGUSR1 is received, stdout prints the output of a while loop that iterates through all lists, in NEW, READY, RUNING, BLOCKED and EXIT states and prints out all their processes. If SIGUSR2 is received, the current RUNNING state process is removed from the RUNNING list, and is added to the BLOCKED list. Every SIGALRM, a variable; blockcounter increments by 1. Once blockcounter reaches 5, the head node of the BLOCKED list is removed and added to the tail of the READY list.

 Any NEW processes are added to the READY list, from reading the command line in stdin of the main function. The user is prompt to enter the Process name, lifetime, and ready time.

