cmake_minimum_required(VERSION 3.15...3.27)
project(pydemumble)

if (CMAKE_VERSION VERSION_LESS 3.18)
  set(DEV_MODULE Development)
else()
  set(DEV_MODULE Development.Module)
endif()

if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-exceptions -fno-rtti")
endif()

if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:inline")
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)  # The LLVM build sets this.

	# statically link against msvcrt
	string(TOUPPER "${CMAKE_BUILD_TYPE}" build)
	set(flag_var "CMAKE_CXX_FLAGS_${build}")
	if(${flag_var} MATCHES "/MD")
		string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
	endif()
endif()

find_package (Python COMPONENTS Interpreter Development REQUIRED)

if (NOT Python_Development_FOUND)
	message(FATAL_ERROR "Python3 include directory not found!")
endif()

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include_directories(
	demumble/third_party/llvm/include
	demumble/third_party/swift/include
)

add_definitions(
  -DLLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING=1
  -DSWIFT_SUPPORT_OLD_MANGLING=1
  -DSWIFT_STDLIB_HAS_TYPE_PRINTING=1
)

# finding nanobind
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/nanobind)

nanobind_add_module(
	pydemumble
	pydemumble.cpp
	demumble/third_party/llvm/lib/Demangle/DLangDemangle.cpp
	demumble/third_party/llvm/lib/Demangle/ItaniumDemangle.cpp
	demumble/third_party/llvm/lib/Demangle/MicrosoftDemangle.cpp
	demumble/third_party/llvm/lib/Demangle/MicrosoftDemangleNodes.cpp
	demumble/third_party/llvm/lib/Demangle/RustDemangle.cpp
	demumble/third_party/swift/lib/Demangling/Context.cpp
	demumble/third_party/swift/lib/Demangling/CrashReporter.cpp
	demumble/third_party/swift/lib/Demangling/Demangler.cpp
	demumble/third_party/swift/lib/Demangling/Errors.cpp
	demumble/third_party/swift/lib/Demangling/ManglingUtils.cpp
	demumble/third_party/swift/lib/Demangling/NodeDumper.cpp
	demumble/third_party/swift/lib/Demangling/NodePrinter.cpp
	demumble/third_party/swift/lib/Demangling/OldDemangler.cpp
	demumble/third_party/swift/lib/Demangling/OldRemangler.cpp
	demumble/third_party/swift/lib/Demangling/Punycode.cpp
	demumble/third_party/swift/lib/Demangling/Remangler.cpp
)