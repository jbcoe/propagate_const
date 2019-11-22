#!/usr/bin/env python
# -*- coding: utf-8 -*-
from conans import ConanFile, CMake, tools

class PropagateconstConan(ConanFile):
    name = "propagate_const"
    version = "1.0.0"
    license = "MIT"
    url = "https://github.com/jbcoe/propagate_const"
    description = "A const-propagating member-pointer-wrapper for the C++ standard library"
    topics = ("conan", "propagate_const", "header-only", "std", "experimental")
<<<<<<< HEAD
    exports_sources = "CMakeLists.txt", "*.h", "*.cpp", "*.cmake", "*.cmake.in", "LICENSE.txt"
    generators = "cmake"

    _cmake = None
    @property
    def cmake(self):
        if self._cmake is None:
            self._cmake = CMake(self)
            self._cmake.definitions.update({
                "BUILD_TESTING": False
            })
            self._cmake.configure()
        return self._cmake


    def package(self):
        self.cmake.build()
        if self.options.build_testing:
            self.cmake.test()

    def package(self):
        self.cmake.install()
=======
    exports_sources = '*', "!build", "!install"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    def package(self):
        cmake = CMake(self)
        cmake.definitions["ENABLE_BUILDING_TESTS"] = "OFF"
        cmake.configure()
        cmake.install()

    def package_id(self):
        self.info.header_only()
>>>>>>> master
