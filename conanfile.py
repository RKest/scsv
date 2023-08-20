from conans import ConanFile, CMake


class SCSVConan(ConanFile):
    name = "SCSV"
    version = "0.1.0"
    license = "See LICENCE.txt at the root of the project"
    author = "Max Ind"
    url = "https://github.com/RKest/scsv"
    description = "CSV to structs converter"
    topics = ("csv")
    settings = "os", "compiler", "build_type", "arch"
    options = {"without_tests": [True, False]}
    default_options = {"without_tests": True, "boost:without_test": True}
    generators = "cmake"
    exports_sources = "include/*", "CMakeLists.txt", "cmake/*", "LICENCE.txt"
    requires = "boost/1.76.0", "magic_enum/0.8.0", "mio/cci.20230303", "nanobench/4.3.11", "gtest/1.12.1"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.hpp", dst="include/scsv", src="include/scsv")

    def package_info(self):
        self.cpp_info.libs = ["scsv"]
