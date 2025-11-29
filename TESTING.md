<!-- Assisted by GitHub Copilot, adapted by Abdul Mziya, 2025-11-28
	Reason: added concise test run instructions for local development -->

GoogleTest / CTest instructions

This project uses GoogleTest (fetched during CMake configure) and integrates with CTest.

From the repository root you can configure, build, and run the tests with:

```bash
# create a fresh build directory and configure
cmake -S . -B build

# build the project (this also builds GoogleTest)
cmake --build build --config Debug -- -j 4

# run tests with CTest (shows failure output)
ctest --test-dir build --output-on-failure
```

If you prefer the CLion-generated directory, replace `build` with `cmake-build-debug` in the commands above.

If you see failures, run the test executable directly for more details, for example:

```bash
./build/my_test
```

If you want, I can add more sample unit tests or configure coverage reporting.
