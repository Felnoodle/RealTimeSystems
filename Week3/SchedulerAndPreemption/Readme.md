# Week 3 Readme

| Scenario | Prediction before test | Actual observation | Did it match? Why? |
|----------|------------------------|--------------------|--------------------|
|Task B priority = 2| Task B message is in the middle of task A message | Task B message is in the middle of task A message | Yes. Task B has a higher priority, so when it is given notification to resume, it will immediately preempt task A. |
|Task B priority = 1| Task B message is after task A message | Task B message is after task A message | Yes. Since the tasks have the same priority, Task A will continue until it is Blocked before Task B becomes Running. With different scheduling configurations task B's message could also appear earlier. |
|Task B priority = 3| Task B message is in the middle of task A message | Task B message is in the middle of task A message | Yes. Functionally the same as situation 1. Task B has a higher priority. |

# Explanations

### What is the Running state?

It is the state that actively uses CPU resources and runs the code. With a single CPU core, only one task can be running at a time.

### What is the Ready state?

It is the state where it is ready to run, and waiting for the scheduler to move it to Running state. The highest priority Ready task is chosen by the scheduler as Running. If multiple Ready tasks share a priority, the chosen task depends on scheduler configuration and timing.

### What is the Blocked state?

It is the state where the task is waiting to become Ready through a notification or delay.

### Why is Task B initially Blocked?

Because Task B runs
```ulTaskNotifyTake(pdTRUE, portMAX_DELAY);```
it will be blocked until it receives a notification.

### What happens when Task A calls xTaskNotifyGive()?

Task B becomes Ready. If Task B has a higher priority, Task B will immediately preempt Task A.

### Why can Task B preempt Task A?

Because it has higher priority.

### What happens when Task B has the same priority as Task A?

Depends on the scheduler configuration and timing. It can yield to Task B if it reaches a time slice or continue running until it is Blocked, which it does when running into
```vTaskDelay(pdMS_TO_TICKS(1000));```
If time slicing is enabled, Task B could also run earlier, so exact serial output is not guaranteed.

### Why can Task A continue from where it stopped?

Because preempting doesn't interrupt the task's progress. The task's stack and program counter are preserved.