#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
// add all the cpp files that is needed
#include "..\Library\Functions.cpp"
#include "..\Library\BlackScholesGenerator.cpp"
#include "..\Library\EquityPriceGenerator.cpp"
#include "..\Library\MCEuroOptPricer.cpp"

namespace py = pybind11;

PYBIND11_MODULE(cmake_example, m) {
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
