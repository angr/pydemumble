#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <llvm/Demangle/Demangle.h>
#include <swift/Demangling/Demangle.h>
#include <string>

#define __PYDEMUMBLE_VERSION__ "0.0.1"

namespace pydemumble
{
	std::string demangle(std::string& func_name)
	{
		size_t nUsed = func_name.length();
		char* result = NULL;
		if (func_name.length() > 1 && (result = llvm::itaniumDemangle(func_name)) != NULL) {
			return std::string(result);
		}
		if ((result = llvm::rustDemangle(func_name)) != NULL) {
			return std::string(result);
		}
		if ((result = llvm::microsoftDemangle(func_name, &nUsed, NULL)) != NULL) {
			return std::string(result);
		}
		if (swift::Demangle::isSwiftSymbol(func_name)) {
			swift::Demangle::DemangleOptions opt;
			opt.SynthesizeSugarOnTypes = true;
			std::string swiftResult = swift::Demangle::demangleSymbolAsString(func_name, opt);
			if (swiftResult != func_name) {
				return swiftResult;
			}
		}
		return "";
	}

	std::string version()
	{
		return std::string(__PYDEMUMBLE_VERSION__);
	}

	NB_MODULE(pydemumble, m) {
		m.def("demangle", &demangle);
		m.attr("__version__") = version();
	}
}

