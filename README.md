# IATest

## Description

A tiny single-header test framework for C++

## Usage Example

```cpp
#include <stdint.h>
#include <iatest.hpp>

namespace mathlib
{
    uint64_t multiply_by_2(uint64_t value) { return (value << 1); }
    uint64_t divide_by_2(uint64_t value) { return (value >> 1); }
}

IA_TEST_MAIN()
{
    IA_TEST_START_METHOD_SET(MathLib);
    
    IA_TEST_METHOD_EQ(mathlib::multiply_by_2(90), 180);
    IA_TEST_METHOD_EQ(mathlib::multiply_by_2(3), 6);
    IA_TEST_METHOD_EQ(mathlib::divide_by_2(7), 3);

    IA_TEST_END_METHOD_SET(MathLib);
}

int main()
{
    IA_TEST_RUN();

    return 0;
}
```

This should produce the following output.

![example_01_result](https://i-a-s.lk/res/images/git/iatest/example_01_result.png)


If you were to change this line from
```cpp
IA_TEST_METHOD_EQ(mathlib::multiply_by_2(3), 6);
```
to
```cpp
IA_TEST_METHOD_EQ(mathlib::multiply_by_2(3), 8);
```
it should produce the following output instead.

![example_02_result](https://i-a-s.lk/res/images/git/iatest/example_02_result.png)

## Documentation

The documentation will soon be made available on this repository.

## Building

No building is necessary, including the iatest.hpp in your project will be all.

## Contributing

Please refer to the following guides:

1) [Contribution Guide](https://i-a-s.lk/docs/contributing/contribution_guide/)
2) [Style Guide](https://i-a-s.lk/docs/contributing/style_guide/)

## Roadmap

The roadmap for IATest can be found [here](https://i-a-s.lk/roadmaps/iatest/)

## License

IATest is licensed under the [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0)