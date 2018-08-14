# Building Anari

## Building Basics

CMake 3.1 or later is used to build Anari and Anari Tester. For your
convenience, we've included Makefiles to automate all common build scenarios on
Linux. Run `$ make` in the root of this repository for more information.

At this time, the Makefiles are only designed for Linux. If you are building
on another system, you can interact with CMake directly.

Currently, Anari is only designed to be built by GCC (5.3 or later) or
Clang (3.4 or later).

## Building and Linking Dependencies

Anari relies on CPGF, Eigen, and PawLIB. The default behavior of the build
system is to look for MousePaw Media's `libdeps/` and `pawlib/` repositories,
cloned parallel to this repository's main folder. Simply run `$ make ready` in
each of those repositories (optionally, you can run `$ make cpgf && make eigen`
in `libdeps/`) before building this one. (This is our default for company
development environments.)

You can specify custom paths for these libraries by creating a `.config` file
in the root of this repository. Make a copy of `build.config.txt` and save it
with the ending `.config`. See that file for more information.

## Ready-To-Use Build

If you just want to build Anari to use in your own project, the fastest way is
to run `$ make ready`. This will build Anari and place it in a folder called
`anari/`, then point your compiler and linker to `anari/include` and
`anari/lib` respectively. Our other repositories point to this by default.

## Building HTML Docs

If you want the HTML documentation for Anari, run `$ make docs`. Then, grab the
`docs/build/html` folder, or just open `docs/build/html/index.html` in your
favorite web browser.

## Building Tester

If you want to test out Anari directly, run `make tester`. Then, look for the
`anari-tester` executable in `anari-tester/bin/[Debug/Release]`. Alternatively,
you may use the symbolic link `tester` or `tester_debug` in the root of this
repository.

## IDE Support

Anari was written and built in CodeBlocks and VSCode. The CodeBlocks projects
(`*.cbp`) in this repository are pre-configured to build using the
Makefile/CMake build system. The configuration files in `.vscode/` are
pre-configured to provide the best IDE experience, and allow building and
debugging.

## Source Directories

- The `/docs` folder contains the Sphinx documentation for Anari.
- The `/anari-source` folder contains the source code for the Anari
  library.
- The `/anari-tester` folder contains the console application for testing
  the Anari library.
