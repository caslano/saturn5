#if !defined(BOOST_PP_IS_ITERATING)

// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
# ifndef CALL_METHOD_DWA2002411_HPP
#  define CALL_METHOD_DWA2002411_HPP

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

# define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/call_method.hpp>))
# include BOOST_PP_ITERATE()

# undef BOOST_PYTHON_FAST_ARG_TO_PYTHON_GET

}} // namespace boost::python

# endif // CALL_METHOD_DWA2002411_HPP

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1
# if !(BOOST_WORKAROUND(__MWERKS__, > 0x3100)                      \
        && BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3201)))
#  line BOOST_PP_LINE(__LINE__, call_method.hpp)
# endif 

# define N BOOST_PP_ITERATION()

template <
    class R
    BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)
    >
typename detail::returnable<R>::type
call_method(PyObject* self, char const* name
    BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, A, const& a)
    , boost::type<R>* = 0
    )
{
    PyObject* const result = 
        PyEval_CallMethod(
            self
            , const_cast<char*>(name)
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
#endif // BOOST_PP_IS_ITERATING

/* call_method.hpp
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
*/