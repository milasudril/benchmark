Benchmark
=========
This is a simple `LD_PRELOAD` trick that can be used to benchmark a program.

Compilation
-----------
Run `maike`, or compile `benchmark.cpp` as a shared library. Required linker
flags can be found at the beginning of that file. The wrapper script
`benchmark` can be used to launch the process that should be benchmark. The
shared library `benchmark.so` must be in the same directory as that script.

```bash
maike
sudo cp __targets/benchmark.so /usr/local/bin
sudo cp benchmark /usr/local/bin
sudo chmod o+x /usr/local/bin/benchmark
```

Usage
-----
Benchmarking is now simple:

```bash
benchmark *command*
```
The output is written to `stderr` and looks similar to this

    # Processing time in seconds for 8971

    Self (user / kernel):     0.024 / 0.015
    Children (user / kernel): 2.745 / 0.233
    Wallclock (total):        3.205

PID 8971 spent 24 ms in its own algorithms, 15 ms in kernel, while it took
2.745 seconds to run the algorithms inside the child processes, and they spent
0.233 seconds in kernel. The total execution time including waiting for I/O was
3.205 seconds.
