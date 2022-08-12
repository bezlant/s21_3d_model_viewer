# 3d Model Viewer

![Viewer Preview](assets/preview.gif)

### Table of Contents
* [Introduction](#introduction)
* [Goals](#goals)
* [Build & Dependencies](#build-and-dependencies)
* [Tests](#tests)

### Introduction

Implementation of the **model viewer** in C following the principles of structured programming. 

### Goals

- [ ] Obj parser
- [ ] Render a model (Vertices & Surfaces support)
- [ ] Translate the model by a given distance in relation to the X, Y, Z axes.
- [ ] Rotate the model by a given angle relative to its X, Y, Z axes.
- [ ] Scale the model by a given value.
- [ ] Gui with Imgui/GLFW
- [ ] Code is well documented
- [ ] Make all, install, uninstall, clean, dvi, dist, tests, gcov targets implemented
- [ ] Unit Tests 
- [ ] Add previews & tests to README

### Build and Dependencies

<u>You'll need to install g++, make, pkg-config, glfw and doxygen(if you need the documentation).</u><br>

```
$ git clone https://github.com/bezlant/s21_3d_model_viewer --recursive
$ cd s21_3d_model_viewer/src/
$ make 
$ make -f test.mk (for tests)
```

### Tests
* Unit tests are implemented using [Check](https://libcheck.github.io/check/) & coverage report with [LCOV](https://github.com/linux-test-project/lcov)

![Tests & Coverage](assets/tests.gif)
