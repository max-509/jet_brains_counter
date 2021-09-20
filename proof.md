##### First, we prove that the two calls `inc (counter *c)` are linearizable. Since the FAA command is atomic, if an increment of one variable is made, there will be no data race, and, therefore, the sequence of commands can be represented in a single execution thread. 
##### Let's say we have `n` calls to the `inc(counter *c)` function and one call to the `get(counter *c)` function, and the initial state of the increment is `I`. Then the `get(counter *c)` function will return values from `I` to `(I + n)`, and after all calls, the increment value will be `(I + n)`. Then the program can be linearizable only by the following way: 
* `get`, `inc_1`, `inc_2`, ..., `inc_(n-1)`, `inc_n`; 
* `inc_1`, `inc_2`, ..., `inc_k`, `get`, `inc_(k+1)`, ..., `inc_n`;
* `inc_1`, `inc_2`, ..., `inc_(n-1)`, `inc_n`, `get`.
## Hence, the increment is linearizable.