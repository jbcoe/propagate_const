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
