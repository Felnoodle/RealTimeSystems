# Week 4 Lab Readme

## Memory values table (bytes)
| Task allocated memory | Free heap before tasks | Free heap after task A | Free heap after task B |
|----------|------------------------|--------------------|--------------------|
|A = 4096, B = 4096| 359112 | 354384 | 349656 |
|A = 8192, B = 4096| 359112 | 350032 | 345432 |

# Explanations

## a. Did the free heap change when you increased the task stack size?

Yes. The larger the allocated stack for the tasks, the smaller the free heap is after creating the tasks. A 4096 byte size stack task reduced the heap size by 4728 or 4600 bytes and a 8192 byte size stack task reduced the heap size by 9080. Note that the reduced heap size is larger than the allocated stack size. This is because the task also has a Task Control Block (TCB) and possible allocator overhead in addition to the stack.

## b. What happened to the free heap?

It was allocated for the task's stack and TCB. It is no longer free to use by other tasks while the task exists.

## c. Why does a task need stack memory?

Each task needs a stack for function-call data and local variables. When the scheduler switches away from a task, its processor state is typically saved on its stack so it can resume later.

## d. Why does creating a FreeRTOS task use RAM?

Because a task needs a stack and a TCB. They are both memory blocks required by a task allocated from RAM.