# 3d Model Viewer

### Table of Contents
* [Introduction](#introduction)
* [Goals](#goals)
* [Build & Dependencies](#build-and-dependencies)
* [Tests](#tests)

### Introduction

Implementation of the **model viewer** in C following the principles of structured programming. 

### Goals

- [x] Obj parser
- [x] Render a model (Vertices & Faces support)
- [x] Translate the model by a given distance in relation to the X, Y, Z axes.
- [x] Rotate the model by a given angle relative to its X, Y, Z axes.
- [x] Scale the model by a given value.
- [x] Gui with Imgui/GLFW
- [x] Code is well documented
- [x] Make all, install, uninstall, clean, dvi, dist, tests, gcov targets implemented
- [x] Unit Tests 
- [x] Add previews 

### Build and Dependencies

<u>You'll need to install clang++, make, googletest, pkg-config, glfw and doxygen(if you need the documentation).</u><br>

```
$ git clone https://github.com/bezlant/s21_3d_model_viewer --recursive
$ cd s21_3d_model_viewer/src/
$ make 
$ make -f test.mk (for tests)
```

### Tests
* Unit tests are implemented using [googletest](https://github.com/google/googletest) & coverage report with [LCOV](https://github.com/linux-test-project/lcov)
