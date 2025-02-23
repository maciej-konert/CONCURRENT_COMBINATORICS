# Concurrent Combinatorics Calculator

This project was developed as part of the Concurrent Programming class, implementing both non-recursive and parallel approaches to combinatorics calculations.

## Project Overview

The project consists of two main implementations:

1. **Non-recursive Implementation**: A memory-efficient solution using a custom stack and shared pointer implementation, achieving performance close to the reference recursive version (approximately 10% slower).

2. **Parallel Implementation**: A multi-threaded version using the pthreads library, demonstrating excellent scalability with up to 14x speedup using 16 threads on large inputs.

## Task Description

The full task description is available in two versions:
- `concurrent_combinatorics_task_en.pdf` (English version - machine translated)
- `concurrent_combinatorics_task_pl.pdf` (Polish version - original)

## Implementation Details

### Non-recursive Version
- Located in `mk459179/nonrecursive/main.c`
- Uses custom stack implementation
- Implements C++-like shared_ptr for memory management
- Guarantees no memory leaks
- Performance comparable to reference recursive implementation

### Parallel Version
- Located in `mk459179/parallel/`
- Files: `main.c`, `shared_ptr.h`, `stack.h`
- Uses pthreads library
- Supports arbitrary number of threads
- Implements synchronization using mutexes and monitors
- Optimized for minimal thread waiting
- Scalability analysis available in `mk459179/report.pdf`

## Building and Running

1. Extract the project files:
```bash
unzip mk459179.zip
```

2. Configure the build:
```bash
cmake -S mk459179/ -B build/ -DCMAKE_BUILD_TYPE=Release
```

3. Build the project:
```bash
cd build/
make
```

4. Run the programs:

Non-recursive version:
```bash
echo -n -e '1 3 1 0\n1\n\n' | ./nonrecursive/nonrecursive
```

Parallel version:
```bash
echo -n -e '1 3 1 0\n1\n\n' | ./parallel/parallel
```

## Example Inputs

1. Small example:
```bash
echo -n -e '8 10 0 1 1\n1\n\n' | ./parallel/parallel
```

2. Medium example:
```bash
echo -n -e '16 34 0 1 1\n1\n\n' | ./parallel/parallel
```

3. Large example (may take up to 1 minute):
```bash
echo -n -e '16 50 0 1 1\n1\n\n' | ./parallel/parallel
```

## Project Evaluation

The project received 9.1/10 points after comprehensive testing. Detailed test results are available at [test results](https://mimuw.edu.pl/~mwrochna/upload/pw2425hw2/mk459179_243a4339.html). The minor point deduction was related to scalability performance on specific test cases. This was primarily due to the heuristic condition used for task distribution among threads - a condition that determines when a thread should give up its tasks to other threads. The somewhat random nature of this heuristic led to occasional suboptimal performance on certain test cases, though the overall scalability remained strong across most scenarios.
