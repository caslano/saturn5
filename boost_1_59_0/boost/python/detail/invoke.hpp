#if !defined(BOOST_PP_IS_ITERATING)

// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
# ifndef INVOKE_DWA20021122_HPP
#  define INVOKE_DWA20021122_HPP

#  include <boost/python/detail/prefix.hpp>
#  include <boost/python/detail/preprocessor.hpp>
#  include <boost/python/detail/none.hpp>

#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/facilities/intercept.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#  include <boost/preprocessor/repetition/enum_binary_params.hpp>
#  include <boost/python/to_python_value.hpp>

// This file declares a series of overloaded invoke(...)  functions,
// used to invoke wrapped C++ function (object)s from Python. Each one
// accepts:
//
//   - a tag which identifies the invocation syntax (e.g. member
//   functions must be invoked with a different syntax from regular
//   functions)
//
//   - a pointer to a result converter type, used solely as a way of
//   transmitting the type of the result converter to the function (or
//   an int, if the return type is void).
//
//   - the "function", which may be a function object, a function or
//   member function pointer, or a defaulted_virtual_fn.
//
//   - The arg_from_python converters for each of the arguments to be
//   passed to the function being invoked.

namespace boost { namespace python { namespace detail { 

// This "result converter" is really just used as a dispatch tag to
// invoke(...), selecting the appropriate implementation
typedef int void_result_to_python;

template <bool void_return, bool member>
struct invoke_tag_ {};

// A metafunction returning the appropriate tag type for invoking an
// object of type F with return type R.
template <class R, class F>
struct invoke_tag
  : invoke_tag_<
        is_same<R,void>::value
      , is_member_function_pointer<F>::value
    >
{
};

#  define BOOST_PP_ITERATION_PARAMS_1                                            \
        (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/invoke.hpp>))
#  include BOOST_PP_ITERATE()

}}} // namespace boost::python::detail

# endif // INVOKE_DWA20021122_HPP
#else 

# define N BOOST_PP_ITERATION()

template <class RC, class F BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class AC)>
inline PyObject* invoke(invoke_tag_<false,false>, RC const& rc, F& f BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(1, N, AC, & ac) )
{
    return rc(f( BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, ac, () BOOST_PP_INTERCEPT) ));
}
                 
template <class RC, class F BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class AC)>
inline PyObject* invoke(invoke_tag_<true,false>, RC const&, F& f BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(1, N, AC, & ac) )
{
    f( BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, ac, () BOOST_PP_INTERCEPT) );
    return none();
}

template <class RC, class F, class TC BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class AC)>
inline PyObject* invoke(invoke_tag_<false,true>, RC const& rc, F& f, TC& tc BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(1, N, AC, & ac) )
{
    return rc( (tc().*f)(BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, ac, () BOOST_PP_INTERCEPT)) );
}
                 
template <class RC, class F, class TC BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class AC)>
inline PyObject* invoke(invoke_tag_<true,true>, RC const&, F& f, TC& tc BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(1, N, AC, & ac) )
{
    (tc().*f)(BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, ac, () BOOST_PP_INTERCEPT));
    return none();
}

# undef N

#endif // BOOST_PP_IS_ITERATING 

/* invoke.hpp
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
*/