# SCSV
### CSV to static data types parser

### Motivational example
```c++
#include <scsv/parse_file.hpp>

struct Person
{
    std::string name;
    int age;
    std::string address;
};

int main()
{
    std::vector<Person> people = scsv::parse_file("people.csv");
    ...
}
```

### Usage
Requires c++20.\
scsv is header only, however it depends on: 
- boost::pfr 
- boost::lexical_cast 
- mio 
- magic_enum 

Therefor the easiest way to use this library, is via conan, by requiring the following conanfile.txt:
```
[requires]
scsv/0.1.0
```
and running
```bash
conan create . --build=missing
```
Then all is left is to link against the library, to include its headers.\
For example in cmake:
```cmake
target_link_libraries(your_target PRIVATE|PUBLIC|INTERFACE scsv)
```