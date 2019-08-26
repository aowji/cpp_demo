// A sample of python embedding (calling python classes from within C++ code)
//
// To run:
// 1) setenv PYTHONPATH ${PYTHONPATH}:./
// 2) call_class py_source Multiply multiply 
// 3) call_class py_source Multiply multiply 9 8 
//

#include <Python.h>

int main(int argc, char *argv[])
{
    PyObject *pName, *pModule, *pDict, *pClass, *pInstance, *pValue;
    int i, arg[8];

    Py_Initialize();
	char cName[] = "py_class";
    pName = PyUnicode_DecodeFSDefault(cName);
    pModule = PyImport_Import(pName);
	if (pModule == NULL) {
		PyErr_Print();
		Py_DECREF(pName);
		Py_Finalize();
		return -1;
	}
	pDict = PyModule_GetDict(pModule);
   
    // Build the name of a callable class 
    pClass = PyDict_GetItemString(pDict, "Multiply");

    // Create an instance of the class
    if (PyCallable_Check(pClass))
    {
		pInstance = PyObject_CallObject(pClass, NULL); 
    }

	// Call a method of the class with two parameters
	pValue = PyObject_CallMethod(pInstance, "multiply2", "(ii)", 2, 2);
	if (pValue != NULL)
	{
		printf("Return of call : %d\n", PyLong_AsLong(pValue));
		Py_DECREF(pValue);
	}
	else
	{
		PyErr_Print();
	}

	// Call a method of the class with no parameters
	pValue = PyObject_CallMethod(pInstance, "multiply", NULL);
	if (pValue != NULL)
	{
		printf("Return of call : %d\n", PyLong_AsLong(pValue));
		Py_DECREF(pValue);
	}
	else
	{
		PyErr_Print();
	}
    
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    Py_Finalize();
    
    return 0;
}
