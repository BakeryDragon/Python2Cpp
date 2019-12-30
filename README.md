# Manual on using pybind11

## Steven Zhang 10/20/2019

### Introduction

There are different ways to implement pybind11. I choose to use existing example project provided by Dean Moldovan which can be found on the GitHub https://github.com/pybind/cmake_example

### File description

The package consists of four folders and one file: ".idea", ".vs", "venv" are the folders related to the main.py file. "cmake_example" folder contains the cpp files in "Library" folder to be called and the binding file main.cpp is in the "src" folder.

### Implementation

For a new C++ file and header file, we have to build the binding code for them to be called by python manually. Further improvement includes building the binding code automatically using LLVM/clang http://cppbinder.readthedocs.io/en/latest/about.html However in this solution, we shall learn how to do this manually

All the binding code are kept in the main.cpp. First we open main.cpp. The first two lines are 

```c++
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
```

The first line calls the pybind11, and must be included in every binding cases. The second line is optional. If you use vector in the C++ file, it needs to be added. For further information regarding which type of information can be used under different pybind11 headers, see https://pybind11.readthedocs.io/en/master/advanced/cast/overview.html at Type conversions/Overview

```C++
PYBIND11_MODULE(python_example, m) {
	m.def("add", &add);
	m.def("square", &square);
	m.def("BS", &BS);

	py::class_<BlackScholesGenerator>(m, "BlackScholesGenerator")
		.def(py::init<double, double, double, double, double>())
		.def("operator", &BlackScholesGenerator::operator());
	
	py::class_<EquityPriceGenerator>(m, "EquityPriceGenerator")
		.def(py::init<double, unsigned, double, double, double>())
		.def("operator", &EquityPriceGenerator::operator());

	py::enum_<OptionType>(m, "OptionType")
		.value("CALL", OptionType::CALL)
		.value("PUT", OptionType::PUT)
		.export_values();

	py::class_<MCEuroOptPricer>(m, "MCEuroOptPricer")
		.def(py::init<double, double, double, double, double, OptionType, int, int, bool, int, double>())
		.def("operator", &MCEuroOptPricer::operator())
		.def("time", &MCEuroOptPricer::time);

	m.def("innerproduct", &innerproduct, R"pbdoc(
		calculate the inner product of two vectors
	)pbdoc"); 
}
```

There are three types of binding code under the PYBIND11_MODULE: binding code for functions which start with m.def , binding code for C++ Classes which start with py::class and binding code for enumeration type py::enum. For more advanced C++ objects, see https://pybind11.readthedocs.io/en/master/advanced/classes.html or https://pybind11.readthedocs.io/en/master/advanced/functions.html

m.def has two argument, "add" indicates the function name you want to use when calling C++ function in python, this can be changed to anything else e.g. "myadd". But for simplicity, we use the same name as the function is declared in the C++. &add indicates which function in C++ you would like to bind. 

py::class has the similar syntax as m.def. \<BlackScholesGenerator>  indicates what C++ classes you want to use in python. Each class must come with a constructor, which the binding code is py::init\<arguments type>(). For functors in the C++ class, the binding code is similar to the C++ function

m serves as a handle for the pybind11, all binding codes add new binding features to m.

### Different IDE for python

Since the interface file main.cpp do not need to be compiled until we need to call C++ function/class from python, this chapter is only about IDE for python
 
#### PyCharm

This program is originally complied in PyCharm. Just click open the python file main.py under the Python2Cpp folder. Go to "Run"(Alt+Shift+F10) and press Enter. The program will first install the binding code and then run the test code.
### Spyder in Anaconda

Open the main.py in Spyder. Run the file(F5).

### Visual Studio

I tested on Visual Studio 2019, but anything after Visual Studio 2015 should work as well.

For Visual Studio, instead of directly open the python file main.py, you have to open the local folder Python2Cpp. After opening the folder, you should be able to see the main.py in Solution Explorer. Click open it and run it.
