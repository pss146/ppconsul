from conans import ConanFile, CMake, tools

class ppConsul(ConanFile):
    name = "ppconsul"
    version = "0.1"
    license = "Boost Software License v1.0"
    author = "Perepelitsyn Stanislav <stas.perepel@gmail.com>"
    url = "https://github.com/pss146/ppconsul"
    description = "C++ client for Consul"
    topics = ("consul", "ppconsul")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    #exports_sources = ["../CMakeLists.txt", "../ext/*", "../include/*", "../src/*"]
    #exports_sources = ["*", "!.*"]
    exports_sources = ["*"]

    def configure(self):
        # We can control the options of our dependencies based on current options
        # self.options["libcurl"].shared = self.options.shared
        self.options["libcurl"].shared = True

    def requirements(self):
        self.requires.add('boost/1.70.0@conan/stable')
        self.requires.add('libcurl/7.64.1@bincrafters/stable')
        self.requires.add('Catch2/2.9.2@catchorg/stable')

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions['BUILD_TESTS'] = 'OFF'
        cmake.definitions['BUILD_SHARED_LIBS'] = 'ON' if self.options.shared else 'OFF'
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        #self.cpp_info.libs = tools.collect_libs(self)
        self.cpp_info.libs = ['ppconsul', 'json11']

