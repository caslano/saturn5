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
        PyEval_CallFunction(
            callable
            , const_cast<char*>("(" BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_FIXED, "O") ")")
            BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_FAST_ARG_TO_PYTHON_GET, nil)
            );
    
    // This conversion *must not* be done in the same expression as
    // the call, because, in the special case where the result is a
    // reference a Python object which was created by converting a C++
    // argument for passing to PyEval_CallFunction, its reference
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