#include <arrow/api.h>
#include <arrow/python/pyarrow.h>
#include <iostream>
#include <vector>
#include <Python.h>


PyObject* pModule = nullptr;
PyObject* pFunc = nullptr;

void initialize_python() 
{
    Py_Initialize();
    #ifdef _WIN32
    const char* pythonPath = "C:\\Users\\ashsubr\\Repos\\Libraries\\python-dev\\myenv\\Lib\\site-packages";
    #else
    const char* pythonPath = "/Users/ashsubr/Code/Libraries/pyarrow-dev/lib/python3.12/site-packages";
    #endif

    PyObject* sysPath = PySys_GetObject("path");
    PyObject* path = PyUnicode_DecodeFSDefault(pythonPath);
    PyList_Append(sysPath, path);
    Py_DECREF(path);

    // initialize pyarrow
    if (arrow::py::import_pyarrow() < 0)
    {
        std::cerr << "error importing pyarrow\n";
    }

    PyRun_SimpleString("import sys\nimport os\nsys.path.insert(0,os.getcwd())\n");

    // Assume `py_table` is a PyObject* representing the Arrow Table
    pModule = PyImport_ImportModule("delta");

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


int main() {
   
    initialize_python();
    create_pytable();
    create_pytable();
    finalize_python();


    return 0; // Exit the program
}

