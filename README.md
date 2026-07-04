*This project has been created as part of the 42 curriculum by ykonka*.

# 42_Heilbronn - Philosophers Project

## Description

* The goal of this project is to simulate the dinning philosophers problem using concurrent programming techniques:
	- resource management
	- processes synchronization
	- avoiding race conditions & deadlocks
* To achieve above goals, we need two main mechanisms used in programming
	- threads [concurrency execution]
	- mutexes [used for resource management]

* Implementation done in `C` program

* For this, we were authorized to use the following functions:

	- `write`, `printf`
	- `malloc`, `free`
	- `memset`, `usleep`, `gettimeofday`
	- `pthread_create`, `pthread_detach`, ` pthread_join`
	- `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`


## Instructions

### Compilation

To get started with this project, follow these steps:
```clean-files
$ make fclean
```
```bash
$ make
```

### Execution

```bash
$ ./philo nr_philos time_to_die eat_duration sleep_duration minimum_meals
```

### Examples

Here’s an example of how to run the philosopher simulation in Bash Shell:

```bash
# philo 5 commands
$ ./philo 5 250 200 100 3
#  philo without optional argument[nr of minimum meals]
$ ./philo 5 250 200 100
#  philo endless run
$ ./philo 5 800 200 100
```

## Resources
- `AI usage`: AI is used for research, test case generation and code refactorization.

- [To get to know what is concurrency programming](https://en.wikipedia.org/wiki/Concurrency_(computer_science))
- `man [command]`: To understand what each of above functions do and how they are helpful in the philosophers implmentation.
