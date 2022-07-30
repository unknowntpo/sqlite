# sqlite
db_tutorial code followed the step in https://cstack.github.io/db_tutorial/

## Build the target

Set up project directory

```
$ project_dir=$(pwd)
```

```
$ mkdir -p ${project_dir}/build
$ cd build
$ cmake ..
```

And inside `${project_dir}/build`, run

```
$ make
```

## Run the tests
Note: you need to build the target first.
```
$ cd ${project_dir}/build
$ ctest
```

You will see something like:

```
Test project /Users/unknowntpo/repo/unknowntpo/sqlite/build
    Start 1: db_test
1/1 Test #1: db_test ..........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```
