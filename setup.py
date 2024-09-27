from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        "my_module",  # Name of the Python module
        ["cpptopython.cpp"],  # C++ source file
        include_dirs=[pybind11.get_include()],  # pybind11 include directory
        language="c++",
        extra_compile_args=["-std=c++11"],
    )
]

setup(
    name="my_module",
    ext_modules=ext_modules
)
