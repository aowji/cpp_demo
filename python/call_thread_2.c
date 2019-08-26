// A sample of python embedding (calling python classes from within C++ code)
//
#ifdef WIN32
#include <Windows.h>
#else
#define Sleep(x) sleep(x/1000)
#endif
#include <Python.h>


int main(int argc, char *argv[])
{
    PyObject *pName, *pModule, *pDict, *pClass, *pInstance;
    int i;


    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault("py_thread");
    if (pName == NULL)
    {
        PyErr_Print();
		fprintf(stderr, "Failed to create name object \"%s\"\n", "py_thread");
        return 1;
    }
    
    pModule = PyImport_Import(pName);
    if (pModule == NULL) 
    {
        PyErr_Print();
		fprintf(stderr, "Failed to create module object \"%s\"\n", "py_thread");
        return 1;
    }

    pDict = PyModule_GetDict(pModule);
    /* pDict is a borrowed reference */

    //////////////////////////////////////////////////////////////////////////
    // Call python classes
    //////////////////////////////////////////////////////////////////////////
   
    // Build callable class name 
    pClass = PyDict_GetItemString(pDict, "MyThread");
    if (pClass == NULL || !PyCallable_Check(pClass))
    {
        PyErr_Print();
        fprintf(stderr, "The class \"%s\" is not callable\n", "MyThread");
        return 1;
    }

    // Create instance
    pInstance = PyObject_CallObject(pClass, NULL); 
    if (pInstance == NULL)
    {
        PyErr_Print();
        fprintf(stderr, "Failed to create the class instance \"%s\"\n", "MyThread");
        return 1;
    }

    PyObject_CallMethod(pInstance, "start", NULL);
	PyThreadState* _save;
	_save = PyEval_SaveThread();
	
    i = 0;
    while(i<10)
    {
		printf("Printed from C thread...\n");

		// PyEval_RestoreThread(_save);
		// !!!Important!!! C thread will not release CPU to Python thread without the following call.
 		// PyObject_CallMethod(pInstance, "join", "(f)", 0.001);
		// PyObject* rlt = PyObject_CallMethod(pInstance, "is_alive", NULL);
		// if (PyObject_IsTrue(rlt)) {
		// 
		// }
		// _save = PyEval_SaveThread();

		Sleep(1000);
		i++;
    }

	PyEval_RestoreThread(_save);

    printf("C thread join and wait for Python thread to complete...\n");
    PyObject_CallMethod(pInstance, "join", NULL);		
    
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    Py_Finalize();
    
    printf("Program completed gracefully.\n");

    return 0;
}
