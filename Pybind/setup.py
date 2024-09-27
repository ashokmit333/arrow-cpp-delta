from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        "cpp_module",  # Name of the Python module
        ["cpptopython.cpp"],  # C++ source file
        include_dirs=[pybind11.get_include()],  # pybind11 include directory
        language="c++",
        extra_compile_args=["-std=c++11"],
    )
]

setup(
    name="cpp_module",
    ext_modules=ext_modules
)


# CMD to build the module -- python setup.py build_ext --inplace

