# atl

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c049afa944ab4c0abd906029f7473bb7)](https://app.codacy.com/app/rdtscp/atl?utm_source=github.com&utm_medium=referral&utm_content=rdtscp/atl&utm_campaign=Badge_Grade_Dashboard)
![C/C++ CI](https://github.com/rdtscp/atl/workflows/C/C++%20CI/badge.svg)
![License](https://img.shields.io/badge/License-MIT-brightgreen.svg)

Alexander's Template Library - Reimplement basic functionality of some the STL to assist in bootstrapping a c-compiler.

## tools/lldbatl.py

Add `command script import /path/to/your/cloned/atl/tools/lldbatl.py` to get cleaner LLDB debugging experience.

Currently supports:

-   `atl::shared_ptr`
-   `atl::string`
-   `atl::vector`
