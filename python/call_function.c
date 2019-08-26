// call_function.c - A sample of calling python functions from C code
// 
#include <Python.h>

int main(int argc, char *argv[])
{
	int i;
	PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue;

	if (argc < 3) 
	{
		printf("Usage: exe_name python_source function_name\n");
		return 1;
	}

	// Initialize the Python Interpreter
	Py_Initialize();

	// Build the name object
	pName = PyUnicode_DecodeFSDefault("py_function");

	// Load the module object
	pModule = PyImport_Import(pName);

	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);

	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, "multiply");

	if (PyCallable_Check(pFunc)) 
	{
		// Prepare the argument list for the call
		if( argc > 3 )
		{
    			pArgs = PyTuple_New(argc - 3);
    			for (i = 0; i < argc - 3; i++)
    			{
					pValue = PyLong_FromLong(atoi(argv[i + 3]));
        			if (!pValue)
        			{
						PyErr_Print();
             			return 1;
        			}
        			PyTuple_SetItem(pArgs, i, pValue);	
    			}
			
				pValue = PyObject_CallObject(pFunc, pArgs);

				if (pArgs != NULL)
				{
					Py_DECREF(pArgs);
				}
		} else
		{
				pValue = PyObject_CallObject(pFunc, NULL);
		}

		if (pValue != NULL) 
		{
			printf("Return of call : %d\n", PyLong_AsLong(pValue));
			Py_DECREF(pValue);
		}
		else 
		{
			PyErr_Print();
		}
	} else 
	{
		PyErr_Print();
	}

	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);

	// Finish the Python Interpreter
	Py_Finalize();

	return 0;
}