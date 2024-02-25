# TrainUsacoCpp

My solutions to the problems at https://usaco.training/ written in C++.


## Compilation

To compile and run a program, start from the root of the project and compile with
```sh
cd chapter/section/problem_full_name/
g++ -std=c++14 -Wall <prog>.cpp
./a.out
```

## Directory Structure

```sh
.
├── .clang-format				- Configuration for [clang-format](https://clang.llvm.org/docs/ClangFormat.html), a C++ formatter
├── .clang-tidy					- Configuration for [clang-tidy](https://clang.llvm.org/extra/clang-tidy/), a C++ linter
├── .gitignore					- Git configuration on which local files to ignore when committing, such as generated binaries
├── .pre-commit-config.yaml		- Configuration for [pre-commit](https://pre-commit.com/)
├── LICENSE						- Git repository license
├── README.md					- This file
├── chapter1					- Problems are divided by chapters and sections
│   ├── section2
│   │   ├── README.md
│   │   ├── broken_necklace
│   │   │   ├── beads.cpp		- C++ solution file
│   │   │   └── beads.in		- input file
│   │   ├── friday_the_thirteenth
│   │   │   ├── friday.cpp
│   │   │   └── friday.in
│   │   └── your_ride_is_here
│   │       ├── ride.cpp
│   │       └── ride.in
│   └── section3
│       ├── README.md
│       └── milking_cows
│           ├── milk2.cpp
│           └── milk2.in
├── lint.sh						- Wrapper script for clang-tidy
├── poetry.lock					- Specific versions of Python dependencies generated by Poetry
└── pyproject.toml				- Python project configuration and depenencies
```
