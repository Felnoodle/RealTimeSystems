# Week 2 readme

| Scenario | Prediction before test | Actual observation | Did it match? Why? |
|----------|------------------------|--------------------|--------------------|
|A. Both tasks at priority 1|Task A happens slightly before B|Task A happens before B, the tasks start to drift apart in timing|No, task A seems to have lower execution overhead than task B, so it completes its cycle first and causes the tasks to drift apart|
|B. Task A priority 1, Task B priority 2|Task B happens slightly before A|Task B happens before A on first cycle, then tasks happen seemingly simultaneously|No, Task B's higher priority causes it to pre-empt task A. |
|C. Task A priority 2, Task B priority 1|Task A happens slightly before B|Task A happens before B, the tasks start to drift apart in timing|No, Task A having a higher priority AND lower overhead causes it to drift apart even faster than in scenario A|

# Temporary starvation experiment

If Task A includes the Serial.println line, Task B will still run during UART transmission. If however Task A is just a While(1) infinite loop, The LED will not blink, since Task B will never change state from Ready to Running, since Task A will be running all the time.

# Explanations

### When a task is running

In this demo a task is running when it is initiating a UART transmission or changing the state of the LED.

### Why vTaskDelay() moves the task to the Blocked state. 

It is necessary for the delay function to block the task, because if it put the task into the ready state instead, a higher priority task would become running instantly.

### What happens when the delay expires and the task becomes Ready. 

If no higher priority task is Ready or Running, the task will become Running.

### How the scheduler selects a Ready task. 

The highest priority Ready task will be selected as Running. If 2 Ready tasks have the same priority, they are spliced.

### How priority affected, or did not visibly affect, your normal periodic tests. 

If the LED task had higher priority, the tasks seemingly were in sync with each other. If they had the same priority or the message task had higher priority, the timing started to drift apart.

### Why removing the delay from the higher-priority task can prevent the lower-priority task from running on the same core.

Because the higher priority task never becomes blocked, it will remain Running forever and the lower priority task will remain Ready forever.