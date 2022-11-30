#if !defined(BOOST_PP_IS_ITERATING)

// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

# ifndef CALL_DWA2002411_HPP
#  define CALL_DWA2002411_HPP

# include <boost/python/detail/prefix.hpp>

#  include <boost/type.hpp>

#  include <boost/python/converter/arg_to_python.hpp>
#  include <boost/python/converter/return_from_python.hpp>
#  include <boost/python/detail/preprocessor.hpp>
#  include <boost/python/detail/void_return.hpp>

#  include <boost/preprocessor/comma_if.hpp>
#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/repeat.hpp>
#  include <boost/preprocessor/debug/line.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#  include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace boost { namespace python {

# define BOOST_PYTHON_FAST_ARG_TO_PYTHON_GET(z, n, _) \
    , converter::arg_to_python<A##n>(a##n).get()

#  define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/call.hpp>))
#  include BOOST_PP_ITERATE()

#  undef BOOST_PYTHON_FAST_ARG_TO_PYTHON_GET

}} // namespace boost::python

# endif // CALL_DWA2002411_HPP

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1
# if !(BOOST_WORKAROUND(__MWERKS__, > 0x3100)                      \
        && BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3201)))
#  line BOOST_PP_LINE(__LINE__, call.hpp)
# endif

# define N BOOST_PP_ITERATION()

template <
    class R
    BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)
    >
typename detail::returnable<R>::type
call(PyObject* callable
    BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, A, const& a)
    , boost::type<R>* = 0
    )
{
    PyObject* const result = 
        PyObject_CallFunction(
            callable
            , const_cast<char*>("(" BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_FIXED, "O") ")")
            BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_FAST_ARG_TO_PYTHON_GET, nil)
            );
    
    // This conversion *must not* be done in the same expression as
    // the call, because, in the special case where the result is a
    // reference a Python object which was created by converting a C++
    // argument for passing to PyObject_CallFunction, its reference
    // count will be 2 until the end of the full expression containing
    // the conversion, and that interferes with dangling
    // pointer/reference detection.
    converter::return_from_python<R> converter;
    return converter(result);
}

# undef N

#endif // BOOST_PP_ITERATION_DEPTH()
#endif

/* call.hpp
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
*/