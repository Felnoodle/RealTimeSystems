# Week 3 Readme Lab 2

## Prediction table

| Scenario | Prediction before test | Actual observation | Did it match? Why? |
|----------|------------------------|--------------------|--------------------|
|LED task running normally|Can give input and LED blinks independently|As predicted|Yes. The tasks are independent and work concurrently|
|LED task suspended|Serial input functional, LED state "freezes"|As predicted|Yes. Since the LED function is suspended, the state of the LED will not change. Since the tasks are independent, changing the LED task to suspended has no effect on the Serial task.|
|LED task resumed|LED will finish its delay then resume blinking|LED instantly changes state and enters a new delay|No. Rather than returning to a blocked state and finishing the delay, the task immediately becomes Ready and executes the next line of code. Resuming a suspended task returns the task to a Ready state, not the state it was in before being suspended.|

## Task state investigation

## Situation 1 - Normal operation

### Serial task
Serial task is running when it checks for input. The serial task becomes blocked for 10ms after checking for input to spare needless CPU usage, but retain fast response. 

### LED task
The LED task is only running when the LED changes state between ON and OFF. During the
```vTaskDelay(pdMS_TO_TICKS(interval));```
function, the task is blocked. When the task moves from Blocked to Ready after the delay function finishes, the scheduler will move it to running, unless the Serial task is already running.

## Situation 2 - LED task is suspended

### Serial task
The serial task runs normally as in normal operation.

### LED task
The LED task is suspended until it receives a resume notification from the Serial task.

## Situation 3 - LED task is resumed

### Serial task
The serial task runs normally as in normal operation.

### LED task
Immediately after resuming, the LED task becomes Ready. Since the task was blocked by the delay function before being suspended, becoming Ready will execute the next line of the task, changing the LED between ON and OFF. Therefore if you set an extremely high delay for the LED blink (like 60000 ms), you can blink it faster "manually", by suspending it and resuming it. After changing the LED status, the task will continue to run normally and becomes Blocked by the delay function.

## Reflection

### Task handles
Task handles make it possible to change another task's state programmatically.

### Suspend
A suspended task doesn't consume any CPU resources and simply waits for a notification to resume it and return it to a Ready state. While suspended, it cannot be chosen by the scheduler to become Running.

### Resume
When the resume function is called, the suspended task becomes Ready if it was Suspended.

### Independent tasks
The Serial task is independent and uses its own stack. Suspending the LED task has no effect on the Serial task.

