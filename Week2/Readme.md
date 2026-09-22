# Week 2 readme

| Scenario | Prediction before test | Actual observation | Did it match? Why? |
|----------|------------------------|--------------------|--------------------|
|A. Both tasks at priority 1|Task A happens slightly before B|Task A happens before B, the tasks start to drift apart in timing|No, task A seems to have lower execution overhead than task B, so it completes its cycle first and causes the tasks to drift apart|
|B. Task A priority 1, Task B priority 2|Task B happens slightly before A|Task B happens before A on first cycle, then tasks happen seemingly simultaneously|No, Task B's higher priority causes it to pre-empt task A. |
|C. Task A priority 2, Task B priority 1|Task A happens slightly before B|Task A happens before B, the tasks start to drift apart in timing|No, Task A having a higher priority AND lower overhead causes it to drift apart even faster than in scenario A|

