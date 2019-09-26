# embedded_tools
Collection of useful tools for embedded development.

## Introduction

This repository is a container for a bunch of useful code
that I have written over the years for my own personal
embedded projects. I provide no guarantees for stability,
correctness, or even basic code style and consistency.

I have made this public in the hopes that other people may
find it useful (and also, public repos are free on GitHub).

Have fun!

## Overview

* [cmake](cmake) - Build files for CMake builds (used to build and run unit tests).
* [docs](docs) - Documentation and guides for the various classes in this project.
* [ext](ext) - External source files, used for reference and required for certain projects.
* [n64](n64) - Classes for interfacing with the N64 controller (and N64 console in the future) (**WIP**).
* [ps2](ps2) - Classes for interfacing with the PS2 DualShock controller (**WIP**). See [ps2.md](docs/ps2.md) in docs.
* [spi](spi) - Generalized SPI interface used in other projects.
* [tests](tests) - Unit tests for this projects.
* [adrian_helpers.hpp](adrian_helpers.hpp) - Includes definitions that are used across the project.
* [adrian_debounced_button.hpp](adrian_debounced_button.hpp) - Defines the DebouncedButton class, for stabilizing noisy buttons.
* [run_tests.sh](run_tests.sh) - Script for assisting in running unit tests. See [Running Tests](#running-tests) for details.

## Running Tests

Follow these steps to run the tests for this project:

1. If you haven't already, install [cmake](https://cmake.org/download/).
2. You will also need a C++ compiler installed.
3. The unit tests use the googletest framework. Follow the instructions on their [Github page](https://github.com/google/googletest/blob/master/googletest/README.md).
4. Once you have installed cmake and googletest, running the tests is easy. Follow these steps:

```
cd embedded_tools
mkdir build
cd build
cmake ..
cd ..
./run_tests.sh
```
