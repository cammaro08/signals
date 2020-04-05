#include <Python.h>
//#include <Python/Python.h>
#include <stdlib.h>


// function definitions
void initPython(char*, char*);
void closePython(void);
long  callFunc(char*);

// globals
PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *presult;



long callFunc(char* value) {
   if (PyCallable_Check(pFunc))
   {   
       pValue=Py_BuildValue("(z)",(char*)value);
       PyErr_Print();
       presult=PyObject_CallObject(pFunc,pValue);
       PyErr_Print();
   } else
   {   
       PyErr_Print();
   }
   
   return PyLong_AsLong(presult);
}

void initPython(char* moduleName, char* function) {

   // Set PYTHONPATH TO working directory
   setenv("PYTHONPATH",".",1);

   // Initialize the Python Interpreter
   Py_Initialize();

   // Build the name object
   pName = PyUnicode_FromString(moduleName);

   // Load the module object
   pModule = PyImport_Import(pName);


   // pDict is a borrowed reference
   pDict = PyModule_GetDict(pModule);


   // pFunc is also a borrowed reference
   pFunc = PyDict_GetItemString(pDict, function);

}

void closePython() {

   Py_DECREF(pValue);

   // Clean up
   Py_DECREF(pModule);
   Py_DECREF(pName);

   // Finish the Python Interpreter
   Py_Finalize();

}
