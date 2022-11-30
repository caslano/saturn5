// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_QVM_THROW_EXCEPTION

#	define BOOST_QVM_THROW_EXCEPTION ::boost::qvm::throw_exception

#	include <exception>

#	ifndef BOOST_QVM_NO_EXCEPTIONS
#   	if defined(__clang__) && !defined(__ibmxl__) // Clang C++ emulates GCC, so it has to appear early.
#       	if !__has_feature(cxx_exceptions)
#           	define BOOST_QVM_NO_EXCEPTIONS
#       	endif
#   	elif defined(__DMC__) // Digital Mars C++
#       	if !defined(_CPPUNWIND)
#           	define BOOST_QVM_NO_EXCEPTIONS
#       	endif
#   	elif defined(__GNUC__) && !defined(__ibmxl__) // GNU C++:
#       	if !defined(__EXCEPTIONS)
#           	define BOOST_QVM_NO_EXCEPTIONS
#       	endif
#   	elif defined(__KCC) // Kai C++
#       	if !defined(_EXCEPTIONS)
#           	define BOOST_QVM_NO_EXCEPTIONS
#       	endif
#   	elif defined(__CODEGEARC__) // CodeGear - must be checked for before Borland
#       	if !defined(_CPPUNWIND) && !defined(__EXCEPTIONS)
#           	define BOOST_QVM_NO_EXCEPTIONS
#       	endif
#   	elif defined(__BORLANDC__) // Borland
#       	if !defined(_CPPUNWIND) && !defined(__EXCEPTIONS)
#           	define BOOST_QVM_NO_EXCEPTIONS
#       	endif
#   	elif defined(__MWERKS__) // Metrowerks CodeWarrior
#       	if !__option(exceptions)
#           	define BOOST_QVM_NO_EXCEPTIONS
#       	endif
#   	elif defined(__IBMCPP__) && defined(__COMPILER_VER__) && defined(__MVS__) // IBM z/OS XL C/C++
#       	if !defined(_CPPUNWIND) && !defined(__EXCEPTIONS)
#           define BOOST_QVM_NO_EXCEPTIONS
#       	endif
#   	elif defined(__ibmxl__) // IBM XL C/C++ for Linux (Little Endian)
#       	if !__has_feature(cxx_exceptions)
#           	define BOOST_QVM_NO_EXCEPTIONS
#       	endif
#   	elif defined(_MSC_VER) // Microsoft Visual C++
			// Must remain the last #elif since some other vendors (Metrowerks, for
			// example) also #define _MSC_VER
#       	if !defined(_CPPUNWIND)
#           	define BOOST_QVM_NO_EXCEPTIONS
#       	endif
#   	endif
#	endif

////////////////////////////////////////

#	ifdef BOOST_NORETURN
#   	define BOOST_QVM_NORETURN BOOST_NORETURN
#	else
#   	if defined(_MSC_VER)
#       	define BOOST_QVM_NORETURN __declspec(noreturn)
#   	elif defined(__GNUC__)
#       	define BOOST_QVM_NORETURN __attribute__ ((__noreturn__))
#   	elif defined(__has_attribute) && defined(__SUNPRO_CC) && (__SUNPRO_CC > 0x5130)
#       	if __has_attribute(noreturn)
#           	define BOOST_QVM_NORETURN [[noreturn]]
#       	endif
#   	elif defined(__has_cpp_attribute)
#       	if __has_cpp_attribute(noreturn)
#           	define BOOST_QVM_NORETURN [[noreturn]]
#       	endif
#   	endif
#	endif

#	if !defined(BOOST_QVM_NORETURN)
#  		define BOOST_QVM_NORETURN
#	endif

////////////////////////////////////////

#	ifdef BOOST_QVM_NO_EXCEPTIONS

namespace boost
{
    BOOST_QVM_NORETURN void throw_exception( std::exception const & ); // user defined
}

namespace boost { namespace qvm {

    template <class T>
    BOOST_QVM_NORETURN void throw_exception( T const & e )
    {
        ::boost::throw_exception(e);
    }

} }

#	else

namespace boost { namespace qvm {

    template <class T>
    BOOST_QVM_NORETURN void throw_exception( T const & e )
    {
        throw e;
    }

} }

#	endif

#endif

/* throw_exception.hpp
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
*/