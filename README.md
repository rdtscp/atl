# atl

![C/C++ CI](https://github.com/rdtscp/atl/workflows/C/C++%20CI/badge.svg)
[![codecov](https://codecov.io/gh/rdtscp/atl/branch/master/graph/badge.svg)](https://codecov.io/gh/rdtscp/atl)
![License](https://img.shields.io/badge/License-MIT-brightgreen.svg)

Alexander's Template Library - Reimplement basic functionality of some the STL to assist in bootstrapping a c-compiler.

## tools/lldbatl.py

Add `command script import /path/to/your/cloned/atl/tools/lldbatl.py` to get cleaner LLDB debugging experience.

Currently supports:

-   `atl::shared_ptr`
-   `atl::string`
-   `atl::vector`
