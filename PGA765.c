#include <stdio.h>
#include <stdlib.h>

// Node structures for different scheduling algorithms

// Node structure for Round Robin and Multi-Level Feedback Queue
struct Node
{
    int processNum;      // Process number
    int arrivalTime;     // Arrival time of the process
    int burstTime;       // Burst time of the process
    int remainingTime;   // Remaining time for execution
    struct Node* next;   // Pointer to the next node
};

// Node structure for storing results of scheduling
struct Node2
{
    int processNum;       // Process number
    int arrivalTime;      // Arrival time of the process
    int burstTime;        // Burst time of the process
    int completionTime;   // Completion time of the process
    int waitingTime;      // Waiting time of the process
    int turnaroundTime;   // Turnaround time of the process
    struct Node2* next;   // Pointer to the next node
};

// Node structure for First Come First Served (FCFS) scheduling
struct NodeFCFS
{
    int processNum;       // Process number
    int arrivalTime;      // Arrival time of the process
    int burstTime;        // Burst time of the process
    int waitingTime;      // Waiting time of the process
    int completionTime;   // Completion time of the process
    int turnaroundTime;   // Turnaround time of the process
    struct NodeFCFS* next; // Pointer to the next node
};

// Function to create a new Node (for Round Robin and Multi-Level Feedback Queue)
struct Node* createNode(int arrivalT, int burstT, int procNum)
{
    // Allocate memory and initialize values
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->processNum = procNum;
    newNode->arrivalTime = arrivalT;
    newNode->burstTime = burstT;
    newNode->remainingTime = burstT; // Initialize remaining time as burst time
    newNode->next = NULL;
    return newNode;
}

// Function to create a new Node2 (for storing results)
struct Node2* createNode2(int arrivalT, int burstT, int procNum, int completionT)
{
    // Allocate memory and initialize values including calculated times
    struct Node2* newNode2 = (struct Node2*)malloc(sizeof(struct Node2));
    newNode2->processNum = procNum;
    newNode2->arrivalTime = arrivalT;
    newNode2->burstTime = burstT;
    newNode2->completionTime = completionT;
    newNode2->turnaroundTime = completionT - arrivalT;
    newNode2->waitingTime = completionT - arrivalT - burstT;
    newNode2->next = NULL;
    return newNode2;
}

// Function to calculate average waiting time for a list of Node2
float calculateAverageWaitingTime(struct Node2* head)
{
    // Iterate through the list and calculate the average
    struct Node2* currentNode = head;
    int sum = 0;
    int count = 0;
    float waitingTimeAverage = 0.0;

    while (currentNode != NULL)
    {
        count++;
        sum += currentNode->waitingTime;
        currentNode = currentNode->next;
    }

    waitingTimeAverage = (float)sum / count;
    return waitingTimeAverage;
}

// Function to calculate average turnaround time for a list of Node2
float calculateAverageTurnaroundTime(struct Node2* head)
{
    // Iterate through the list and calculate the average
    struct Node2* currentNode = head;
    int sum = 0;
    int count = 0;
    float averageTurnaroundTime = 0.0;

    while (currentNode != NULL)
    {
        count++;
        sum += currentNode->turnaroundTime;
        currentNode = currentNode->next;
    }

    averageTurnaroundTime = (float)sum / count;
    return averageTurnaroundTime;
}

// Function to calculate throughput for a list of Node2
float calculateThroughput(struct Node2* head, int NumOfProcesses)
{
    // Calculate the total time and divide the number of processes by it
    float throughput;
    struct Node2* currentNode;
    int minAT = head->arrivalTime, maxCT = head->completionTime, totalTime;

    currentNode = head;

    while (currentNode != NULL)
    {
        if (currentNode->arrivalTime < minAT)
        {
            minAT = currentNode->arrivalTime;
        }
        if (currentNode->completionTime > maxCT)
        {
            maxCT = currentNode->completionTime;
        }

        currentNode = currentNode->next;
    }

    totalTime = maxCT - minAT;

    throughput = (float)NumOfProcesses / totalTime;

    return throughput;
}

// Function to sort Nodes based on arrival time (bubble sort)
struct Node* bubbleSort(struct Node* head)
{
    // Perform bubble sort on the linked list
    int isSwapped;
    struct Node* temp;
    do
    {
        isSwapped = 0;
        struct Node* tail2 = head;
        struct Node* previousNode = NULL;

        while (tail2->next != NULL)
        {
            struct Node* nextNode = tail2->next;

            if (tail2->arrivalTime > nextNode->arrivalTime)
            {
                if (previousNode != NULL)
                {
                    previousNode->next = nextNode;
                }
                else
                {
                    head = nextNode;
                }

                tail2->next = nextNode->next;
                nextNode->next = tail2;

                temp = tail2;
                tail2 = nextNode;
                nextNode = temp;

                isSwapped = 1;
            }
            previousNode = tail2;
            tail2 = tail2->next;
        }
    } while (isSwapped);

    return head;
}

// Function to add a Node to the end of a queue
struct Node* enqueue(struct Node* tail, struct Node* Node)
{
    // Add Node to the end of the queue and return the new tail
    tail->next = Node;
    tail = tail->next;
    return tail;
}

// Function to remove a Node from the front of a queue
struct Node* dequeue(struct Node** head)
{
    // Remove the head Node from the queue and return it
    struct Node* node;
    struct Node* temp;

    node = *head;
    temp = *head;
    temp = temp->next;
    *head = temp;
    node->next = NULL;
    return node;
}

// Function to process nodes for Multi-Level Feedback Queue scheduling
struct Node2* Processing(struct Node* head, struct Node2* head2)
{
    struct Node* RRhead = createNode(head->arrivalTime, head->burstTime, head->processNum);
    struct Node* RRtail = RRhead;
    struct Node* temp;
    struct Node* FCFShead = NULL;
    struct Node* FCFStail = NULL;
    struct Node2* tail2;
    struct Node* RRCheck;
    struct Node* FCFSCheck;
    int currentT = 0;
    int quantum;

    temp = head->next;
    RRCheck = RRhead;

    // Execute processes until the RR queue is empty
    while (RRhead != NULL)
    {
        if (RRhead->remainingTime == 0)
        {
            // Process completed, calculate and store results
            currentT = currentT + RRhead->burstTime;
            tail2 = createNode2(RRhead->arrivalTime, RRhead->burstTime, RRhead->processNum, currentT);
            head2 = tail2;

            if (RRhead->next != NULL)
            {
                RRhead = RRhead->next;
                free(RRCheck);
                RRCheck = RRhead;
            }
            else
            {
                RRhead = NULL;
                free(RRCheck);
            }
        }
        else if (RRhead->remainingTime > 0 && RRhead->remainingTime <= quantum)
        {
            // Process quantum expires, calculate and store results
            currentT = currentT + RRhead->remainingTime;
            RRhead->remainingTime = 0;
            tail2 = createNode2(RRhead->arrivalTime, RRhead->burstTime, RRhead->processNum, currentT);
            head2 = tail2;

            if (RRhead->next != NULL)
            {
                RRhead = RRhead->next;
                free(RRCheck);
                RRCheck = RRhead;
            }
            else
            {
                RRhead = NULL;
                free(RRCheck);
            }
        }
        else
        {
            // Process still needs more time, adjust remaining time
            currentT = currentT + quantum;
            RRhead->remainingTime = RRhead->remainingTime - quantum;

            // Enqueue processes that have arrived while executing
            while (temp != NULL)
            {
                if (temp->arrivalTime <= currentT)
                {
                    RRtail = enqueue(RRtail, createNode(temp->arrivalTime, temp->burstTime, temp->processNum));
                    temp = temp->next;
                }
                else
                {
                    break;
                }
            }

            RRtail->next = NULL;

            // Copy remaining processes to FCFS queue
            FCFSCheck = FCFShead;
            while (FCFSCheck != NULL)
            {
                FCFStail = enqueue(FCFStail, createNode(FCFSCheck->arrivalTime, FCFSCheck->burstTime, FCFSCheck->processNum));
                FCFSCheck = FCFSCheck->next;
            }

            FCFShead = RRhead;
            FCFStail = RRtail;

            RRhead = FCFShead->next;
            FCFShead->next = NULL;

            temp = FCFShead;

            if (FCFSCheck != NULL)
            {
                FCFShead = FCFShead->next;
                free(temp);
            }
        }
    }

    return head2;
}

int main()
{
    struct Node* head = NULL;
    struct Node* tail = NULL;
    struct Node2* head2 = NULL;
    struct Node2* tail2 = NULL;
    int num, choice, procNum, arrivalTime, burstTime;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &num);

    // Input processes
    for (int i = 0; i < num; i++)
    {
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrivalTime, &burstTime);
        tail = enqueue(tail, createNode(arrivalTime, burstTime, i + 1));
        if (head == NULL)
        {
            head = tail;
        }
    }

    // Sort processes by arrival time using bubble sort
    head = bubbleSort(head);

    // Choose scheduling algorithm
    printf("Select scheduling algorithm:\n");
    printf("1. Round Robin\n");
    printf("2. Multi-Level Feedback Queue\n");
    printf("3. First Come First Served (FCFS)\n");
    printf("Enter your choice (1/2/3): ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("Enter time quantum for Round Robin: ");
        scanf("%d", &quantum);
        while (head != NULL)
        {
            head2 = Processing(head, head2);
        }
        break;

    case 2:
        while (head != NULL)
        {
            head2 = Processing(head, head2);
        }
        break;

    case 3:
        printf("The FCFS scheduling result is as follows:\n");
        while (head != NULL)
        {
            if (head2 == NULL)
            {
                head2 = createNode2(head->arrivalTime, head->burstTime, head->processNum, head->arrivalTime + head->burstTime);
                head = head->next;
            }
            else
            {
                tail2 = createNode2(head->arrivalTime, head->burstTime, head->processNum, head2->completionTime + head->arrivalTime);
                head2 = tail2;
                head = head->next;
            }
        }
        break;

    default:
        printf("Invalid choice!\n");
        exit(1);
    }

    // Print scheduling results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    struct Node2* tempNode2 = head2;
    while (tempNode2 != NULL)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", tempNode2->processNum, tempNode2->arrivalTime, tempNode2->burstTime, tempNode2->completionTime, tempNode2->waitingTime, tempNode2->turnaroundTime);
        tempNode2 = tempNode2->next;
    }

    // Calculate and print average waiting time, average turnaround time, and throughput
    printf("\nAverage Waiting Time: %.2f\n", calculateAverageWaitingTime(head2));
    printf("Average Turnaround Time: %.2f\n", calculateAverageTurnaroundTime(head2));
    printf("Throughput: %.2f processes per unit time\n", calculateThroughput(head2, num));

    return 0;
}
