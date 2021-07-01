# Philosophers

## MacOS - ![Build](https://github.com/dolovnyak/Philosophers/actions/workflows/c-cpp.yml/badge.svg?branch=master)

Three tasks that teach how to work with mutexes, semaphores and processes.
------------

Common rules:
----------
- A number of philosophers are sitting at a round table doing one of three things: eating, thinking or sleeping.
- While eating, they are not thinking or sleeping, while sleeping, they are not eating or thinking and of course, while thinking, they are not eating or sleeping.
- The philosophers sit at a circular table with a large bowl of spaghetti in the center.
- There are some forks on the table.
- As spaghetti is difficult to serve and eat with a single fork, it is assumed that a philosopher must eat with two forks, one for each hand.
- The philosophers must never be starving.
- Every philosopher needs to eat.
- Philosophers don’t speak with each other.
- Philosophers don’t know when another philosopher is about to die.
- Each time a philosopher has finished eating, he will drop his forks and start sleeping.
- When a philosopher is done sleeping, he will start thinking.
- The simulation stops when a philosopher dies.
- Each program should have the same options: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

philo_one rules:
----------
- One fork between each philosopher, therefore there will be a fork at the right and at the left of each philosopher.
- To avoid philosophers duplicating forks, you should protect the forks state with a `mutex` for each of them.
- Each philosopher should be a `thread`.

philo_two rules:
----------
- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by a `semaphore`.
- Each philosopher should be a `thread`.

philo_three rules:
----------
- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by a `semaphore`.
- Each philosopher should be a `process` and the main process should not be a philosopher.

Examples:
---------
```
 ./philo_one 4 410 200 200  # 4 - philosopehrs number, 410 - time to die, 200 - time to eat, 200 - time to sleep 
0ms 1 is thinking
0ms 1 has taken a fork
0ms 1 has taken a fork
0ms 1 is eating
0ms 3 is thinking
0ms 3 has taken a fork
0ms 3 has taken a fork
0ms 3 is eating
200ms 1 is sleeping
200ms 3 is sleeping
200ms 2 is thinking
200ms 2 has taken a fork
200ms 2 has taken a fork
200ms 2 is eating
200ms 4 is thinking
200ms 4 has taken a fork
200ms 4 has taken a fork
200ms 4 is eating
400ms 1 is thinking
400ms 3 is thinking
400ms 4 is sleeping
...... will live forever
```
```
 ./philo_one 4 390 200 200 
0ms 1 is thinking
0ms 3 is thinking
0ms 1 has taken a fork
0ms 3 has taken a fork
0ms 1 has taken a fork
0ms 3 has taken a fork
0ms 1 is eating
0ms 3 is eating
200ms 3 is sleeping
200ms 1 is sleeping
200ms 2 is thinking
200ms 2 has taken a fork
200ms 2 has taken a fork
200ms 2 is eating
200ms 4 is thinking
200ms 4 has taken a fork
200ms 4 has taken a fork
200ms 4 is eating
393ms 1 died
```
