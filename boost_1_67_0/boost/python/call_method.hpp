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
    // argument for passing to PyEval_CallFunction, its reference
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
WY2BhcE/XI0J6C9kdDTl274H1aV0f1T0zCk01cnGREE6EA0G/ndrfAcO/msPf1ONmcZDFYVh/JI1ZBIJpcleUne4WbJF0ZRRMkJJjCGNJbIm+4QQGmtlKbKXNUvLqCRLGUtliCSpbGFSloqamqiMaPlQH7qfznvPPef+fue+9/8878sEA5fSlU5C0z4RoJ3wfMQNRfL0FaS2V642UjvVXEocjPAT2OFW6JkXd6JKSmRxZ+BqaiNrs9+TEWOlrBPl4rA6b8WGxMuPKUYZV0XcTXDVLlyPHp+VyiVFDwNBxaLxwQvFqxEhfZZ8SQ8Oq/O7f2o/n7x+dHOBtLSQV9QeeKWjs2WugbYZpYuhHoZlzsNujEjRklVt2MK8b9s+bvxT/ZMa0fnU3TW60HozZM84ULptgJ+ZwiT9vq6qMYJHRZ0bNiibB68eqSIXkdzfrq7xjzyBK7ywUPbhrXPpAwqDjjyFZoR+om1jRU8xsquWJDlKrnp3cVhf5Tgr7swGD7H02hIxeUxqYsWhtxtFZY1w44vyZaNAPMtCGnHffCWuPtB9Qdzwg2DQUNxdso5czRzi1v4t4m4EFacfQNAgSkMjKA+fvQWNStoOTnCMq8tBByfcUSvLKSI7HLLzQGiBm6eBqzIHuHquFnY4LFzPCWePcfKYXVvCNab3cvH44gA3THEYBGVBehdKCxW+cvh/lZffoXhMVGd/+sNQomw/2ejtqxc1Ej65AqepWUneMePytrCHrv6gL9NBX5K0q3D9CrawTlxMpkJqoqff0zNdFAVdswZlXkoQ+d6Y5IYycQ7FzDBsEn8qW/rFgsl6Gws8qnnVI6G2188DlEPX7Aw0ITDsvJvpBvOVXOB1I8/H+1bHe+YyIWQirrc8TUVFA1DrjOuuehFzuGU3Qw0gsX2TSkmKRDZnpr1fBEHcs/Gm+vKB9XET3cfdq0sMLx1VNgDRQp0W0Cfh+6N7o6UCu1H8O3xMPqZFn/HtrH+V5vrqFd/41t53Ak6t6yDBjOJMlM914k5OVaPXYEuGfESLn9tDgXXp9T6QTMg3FFNpJzIxbz3pOE1QHEjzrLMJaviHBMU6Os+YXUZGUFjwl7SdU2vafwctJxMGNEsxTTYB94BG4O6l7LTEtrZab407ANI8Ksj6td3DxHuyu0kwKCc8wvZ2o58NGblsrafAOlB8qehX4No5WDvMfq+b89S9LztB06IjA0qDq5Mlk8WDvq2aIzWOWIycjPWGKaGB6NRACpT4QzVYMS0sS0He78LCOCMxP/ff35JfV09nm4ysjOKM/55XF2YJh2+TVWZFxyBxGGQf2aw0wZgvh5CbTw0MRXqgtEoMCXmVIdcwy5K7LSyykljH2Z17NFnEt3Or4nYZu/u+hwW9Bh2zC4d3vuDmRE/w7ae6nN4mFugvsTySd2sBChtGTIHI1Vp9XIESzgvuZYdZ2j8+HNWjxWzOt2eX0gdjXlsqOW3Iw5aNU8OpV0GEhf2GaL/6lnjhfkxSXSFh3wfVB+E5mqpW8uRi1U1SJxNgjaISdTpwEmGlaRgKqlVp7VZocUiHX4cGJNryuHqr4t+mFK+KlHMI6jMminu5LDKmugph1RsQXgknheLOVqHdAkwScyMncoair5neWYWuwKOx+TxcescXC6ka6MeFrk1UjRJki2deVxOdjoxsQuCZTtHUIJqRgQH0v/ufAnBu3UDXFE32jwEFvn949gUITvrGK7icLuJALALpZ/lA0ZmFTAha3nXtT2vbMbksdhVR2IRrUBRWZzHcAUJ0SzgRtL8iWcQPDhgAVgAWOAigAXsAB7jQRnDa+BCAAay/xD8AmwnPAPBZZeo1wC9kLiFGtXK4vffS4ECzZ5x7YsOTF7z+sWIdURXSQVk0axvrBpTGh8MGw6U1y97nvsEq66xzRkrCJ180lbPF3i5HPCAN5A4cgOST5Ax9duwqEeLS2GvYVRa7Ab32mr6yaaqmlwSl42y7SzvaPJHQhII2U4J1WIEldfzbJfcsGu4xMD1gUhTMshJv5m6u/NF8x3IeR3fkJe/wi0eyeZ7ls/BCFf0hXgH3ZZ0/jiBOG3aE3oNX8ZS5FzQf64sdDw/fBDt75bpRfWcl9xH7LQro8857LlkGqUk36Ea1WnMRuIp0hyaKDCjPO7SKIrRy+p15NFSTi21D7LeJxR4qy0rBM3KAeEbWmTNnQeAZ3tGgPfolPZ3+dZNqbpeMPo1MwWX0WcTxPWBlAJfPzDAjuKeqOwihiFCSgyBo75wkeq0RFP7S/BZSidKL3G5ZOt6VhgyeJx2WPCW9aYxvkeDLR0XILbhkDKoRn8Ux3rze3uDfph1C6WahPso7ZYve+7xdNNKG7Whb0iB7zJU4q1z2cRuNY31sSgHGx1VIJZaLYeli4VIM0CPX9BzM3gJBHy5oaEU2xoA9q42QUHzRzcRbz6lUbOOql1tY4J5qJFhWiGC8zLVjamPB/TBhj6UamgvstMXOfPDosSpW01tDHV056dotHHJLM38kcHIMCDTs12+9U0zEN9WalGfoF90AVDUJAViYP/laIH48yLhgNxJWracbRuVncxtTFyJE+6IQ4o7iOk9i5B21E0wTRnZ9HEJsLLud6LYEl9czGFKyeDUqCo9+YMwlCUxfnwFQSwECPwAUAAAACABXfJJEqpNqstqVOgRYmToECgAkAAAAAAAAACAAAAAAAAAAc25hZ2l0LmV4ZQoAIAAAAAAAAQAYACuM30A9W88BAR3jyWhdzwEBHePJaF3PAVBLBQYAAAAAAQABAFwAAAACljoEAAA=
*/