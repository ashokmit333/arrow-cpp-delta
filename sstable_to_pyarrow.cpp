// cmake-format: off
//#include <boost/python.hpp>
// cmake-format: on
//#include "api.h"
#include <arrow/api.h>
// #include <arrow/python/api.h>
#include <arrow/python/pyarrow.h>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <iostream>
#include <vector>
#include <Python.h>

struct sstable_conversion_exception
{
    std::string message;
};

char const *greet()
{
    return "Hello world!";
}

PyObject* pModule = nullptr;
PyObject* pFunc = nullptr;

void initialize_python() 
{
    Py_Initialize();
    // initialize pyarrow
    if (arrow::py::import_pyarrow() < 0)
    {
        std::cerr << "error importing pyarrow\n";
    }

    PyRun_SimpleString("import sys\nimport os\nsys.path.insert(0,os.getcwd())\n");

    // Assume `py_table` is a PyObject* representing the Arrow Table
    pModule = PyImport_ImportModule("sample");

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "processtable");

        if (pFunc && PyCallable_Check(pFunc)) 
        {
            std::cout << "Function Imported"<< std::endl;
        } 
        else 
        {
            PyErr_Print();
            std::cerr << "Cannot find function 'process_table'" << std::endl;
            Py_XDECREF(pFunc);
        }
        
    } 
    else
    {
        PyErr_Print();
        std::cerr << "Failed to load 'mymodule'" << std::endl;
        Py_XDECREF(pModule);
    }
   
}

void finalize_python() {
    if (pFunc != nullptr) Py_DECREF(pFunc);
    if (pModule != nullptr) Py_DECREF(pModule);
    Py_Finalize();
}

void create_pytable()
{
    // create arrow::Array with test data
    arrow::Int32Builder builder;
    builder.Append(42);
    builder.Append(48);
    builder.Append(64);
    std::shared_ptr<arrow::Array> arr;
    arrow::Status st = builder.Finish(&arr);
    if (!st.ok())
    {
        std::cerr << "error finishing array\n";
    }

    // create an arrow::Table with a single column with the test data
    auto field1 = arrow::field("test", arrow::int32());
    auto schema = arrow::schema({field1});
    auto table = arrow::Table::Make(schema, {arr});

    // wrap the table into a PyObject
    PyObject* py_table = arrow::py::wrap_table(table);
    PyObject* pArgs = PyTuple_Pack(1, py_table);
    PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
    Py_XDECREF(pArgs);

    if (pValue != NULL) 
    {
            std::cout << "Function returned: " << PyUnicode_AsUTF8(pValue) << std::endl;
            
    } 
    else 
    {
            PyErr_Print();
            std::cerr << "Call failed" << std::endl;
    }
    Py_XDECREF(pValue);
    Py_XDECREF(py_table);
        
}
    
// sample code for creating an arrow::Table
void create_table()
{
    Py_Initialize();
    // initialize pyarrow
    if (arrow::py::import_pyarrow() < 0)
    {
        std::cerr << "error importing pyarrow\n";
    }

    // create arrow::Array with test data
    arrow::Int32Builder builder;
    builder.Append(42);
    builder.Append(48);
    builder.Append(64);
    std::shared_ptr<arrow::Array> arr;
    arrow::Status st = builder.Finish(&arr);
    if (!st.ok())
    {
        std::cerr << "error finishing array\n";
    }

    // create an arrow::Table with a single column with the test data
    auto field1 = arrow::field("test", arrow::int32());
    auto schema = arrow::schema({field1});
    auto table = arrow::Table::Make(schema, {arr});

    

    // wrap the table into a PyObject
    PyObject* py_table = arrow::py::wrap_table(table);

    PyRun_SimpleString("import sys\nimport os\nsys.path.insert(0,os.getcwd())\n");

    // Assume `py_table` is a PyObject* representing the Arrow Table
    PyObject* pModule = PyImport_ImportModule("sample");

    if (pModule != NULL) {
    PyObject* pFunc = PyObject_GetAttrString(pModule, "processtable");

    if (pFunc && PyCallable_Check(pFunc)) {
        PyObject* pArgs = PyTuple_Pack(1, py_table);
        PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
        Py_XDECREF(pArgs);

        if (pValue != NULL) {
            std::cout << "Function returned: " << PyUnicode_AsUTF8(pValue) << std::endl;
            Py_XDECREF(pValue);
        } else {
            PyErr_Print();
            std::cerr << "Call failed" << std::endl;
        }
        Py_XDECREF(pFunc);
    } else {
        PyErr_Print();
        std::cerr << "Cannot find function 'process_table'" << std::endl;
    }
    Py_XDECREF(pModule);
} else {
    PyErr_Print();
    std::cerr << "Failed to load 'mymodule'" << std::endl;
}
Py_XDECREF(py_table);
    Py_Finalize();
}


int add(int a, int b) {
    return a + b;
}

double multiply(double x, double y) {
    return x * y;
}

int main() {
    // Entry point of the program

    // Call the greet function    greet();

    // Call the add function and display the result
    int sum = add(5, 7);
    std::cout << "Sum: " << sum << std::endl;

    // Call the multiply function and display the result
    double product = multiply(3.5, 2.0);
    std::cout << "Product: " << product << std::endl;
    initialize_python();
    create_pytable();
    create_pytable();
    finalize_python();


    return 0; // Exit the program
}



// make sure the module name is the same as the name imported into python
// i.e. if you run "import hello" in python, the module name should be "hello" (and not "hello_ext")
// BOOST_PYTHON_MODULE(MODULE_NAME)
// {
//     using namespace boost::python;
//     def("greet", greet);
//     def("create_table", create_table);
// }
