# Operating Systems & Concurrency Coursework

This program implements three different scheduling algorithms: **First Come First Served (FCFS)**, **Round Robin (RR)**, and **Multi-Level Feedback Queue (MLFQ)**. It is written in C and provides a simple console-based user interface to interact with each scheduling algorithm.

## Features

- First Come First Served (FCFS): Processes are scheduled according to their arrival times.
- Round Robin (RR): Each process is assigned a fixed time in a cyclic way.
- Multi-Level Feedback Queue (MLFQ): Processes are assigned to different queues based on various criteria such as burst time and priority.


## Compilation and Execution

To compile and run the program, ensure that you have a C compiler installed (such as GCC). Compile the code using the following command:

```bash
  gcc -o scheduler main.c
```

Run the compiled program:

```bash
  ./scheduler
```

## Usage

Upon running the program, you will be prompted to choose a scheduling algorithm:

```bash
  What would you like to do?
  1. FCFS
  2. RR
  3. MLFQ
  4. Exit
```


Enter the number corresponding to your choice and follow the on-screen instructions to enter details like the number of processes, arrival times, burst times, and time quantum (for RR and MLFQ).

## Output

After inputting the necessary data, the program will display the scheduling results, which include:

- Process ID
- Arrival Time
- Burst Time
- Completion Time
- Waiting Time
- Turnaround Time
  

Additionally, the program calculates and displays the average waiting time, throughput, and average turnaround time for the processes based on the selected scheduling algorithm.


## Exiting the program

To exit the program, select option `4` at the main menu.

## Running the Code in an IDE (Alternative)

You can run this program in an Integrated Development Environment (IDE) such as _Visual Studio Code_, _Code::Blocks_, or _CLion_. Here's how you can do it:

**Steps:**

1. **Open the IDE**: Launch your preferred IDE and open a new project/workspace.

2. **Import the File**: Import the C file containing the source code into your project/workspace. This is typically done through the `File` menu in the IDE, where you can find options like `Import`, `Open`, or `Add Existing File`.

3. **Build the Project**: Use the build options provided by the IDE to compile the code. This option is usually found in the `Build` or `Run` menu of the IDE. Some IDEs automatically compile the code before running it.

4. **Run the Program**: Execute the compiled program using the `Run` option in your IDE. This should open a console or terminal window where you can interact with the program.

5. **Input Data**: Follow the on-screen prompts to input the required data for the scheduling algorithms.

6. **View Results**: After processing the input data, the program will display the scheduling results in the IDE's console or output window.
