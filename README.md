<a id = "anchor_5"></a>
# 🧪 STL Concurrency Lab

### Content list
1. [About the program](#anchor_1)
2. [What technologies were used](#anchor_2)
3. [Program execution example](#anchor_3)
4. [Results](#anchor_4)
---

<a id = "anchor_1"></a>
### About the program
- __Part 1:__
Parallel processing of an array (increasing each member by a constant) using the std::async asynchronous call mechanism. To do this, we split the array into M equal parts, processing each in a separate thread.
>The size of the array, the number of parts M and the launch policy are set by the user from the keyboard.

- __Part 2:__

The following scheme has been implemented:
![scheme](https://user-images.githubusercontent.com/105476685/177993634-877824b3-5b5c-4a44-a273-b891a8d522ec.png)

The system consists of N generators and one processor. Generators generate random numbers and pass them to the processor, which prints them to the console. Each of the entities (generator/processor) is executed in a separate thread.
>The number of generators and the startup policy is set by the user from the keyboard.

<a id = "anchor_2"></a>
### What technologies were used
- Parallelism with the STL

<a id = "anchor_3"></a>
### Program execution example

![image_1](https://user-images.githubusercontent.com/105476685/177993636-0693b376-a8b6-432d-9abf-279aedd973e7.png)
![image_2](https://user-images.githubusercontent.com/105476685/177993630-a1f8f2e4-c162-4136-bab7-6ca06b2033b7.png)

<a id = "anchor_4"></a>
### Results

__Array length = 3000__
|M|Time async|Time deferred|
|---|---|---|
|1|0.121|0.112|
|2|0.131|0.171|
|3|0.104|0.117|
|4|0.083|0.148|
|8|0.069|0.213|
|16|0.057|0.143|

[↑ UP ↑](#anchor_5)
