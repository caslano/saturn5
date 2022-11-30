#if !defined(BOOST_PP_IS_ITERATING)

// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

# ifndef RESULT_DWA2002521_HPP
#  define RESULT_DWA2002521_HPP

#  include <boost/type.hpp>

#  include <boost/python/detail/preprocessor.hpp>
#  include <boost/python/detail/type_traits.hpp>

#  include <boost/mpl/if.hpp>

#  include <boost/preprocessor/comma_if.hpp>
#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/debug/line.hpp>
#  include <boost/preprocessor/enum_params.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_params.hpp>

namespace boost { namespace python { namespace detail {

// Defines a family of overloaded function which, given x, a function
// pointer, member [function] pointer, or an AdaptableFunction object,
// returns a pointer to type<R>*, where R is the result type of
// invoking the result of bind(x).
//
// In order to work around bugs in deficient compilers, if x might be
// an AdaptableFunction object, you must pass OL as a second argument
// to get this to work portably.

#  define BOOST_PP_ITERATION_PARAMS_1                                                                   \
    (4, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/result.hpp>, BOOST_PYTHON_FUNCTION_POINTER))
#  include BOOST_PP_ITERATE()

#  define BOOST_PP_ITERATION_PARAMS_1                                                                     \
    (4, (0, BOOST_PYTHON_CV_COUNT - 1, <boost/python/detail/result.hpp>, BOOST_PYTHON_POINTER_TO_MEMBER))
#  include BOOST_PP_ITERATE()

template <class R, class T>
boost::type<R>* result(R (T::*), int = 0) { return 0; }

#  if (defined(__MWERKS__) && __MWERKS__ < 0x3000)
// This code actually works on all implementations, but why use it when we don't have to?
template <class T>
struct get_result_type
{
    typedef boost::type<typename T::result_type> type;
};

struct void_type
{
    typedef void type;
};

template <class T>
struct result_result
{
    typedef typename mpl::if_c<
        is_class<T>::value
        , get_result_type<T>
        , void_type
        >::type t1;

    typedef typename t1::type* type;
};

template <class X>
typename result_result<X>::type
result(X const&, short) { return 0; }

#  else // Simpler code for more-capable compilers
template <class X>
boost::type<typename X::result_type>*
result(X const&, short = 0) { return 0; }

#  endif

}}} // namespace boost::python::detail

# endif // RESULT_DWA2002521_HPP

/* --------------- function pointers --------------- */
// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == BOOST_PYTHON_FUNCTION_POINTER
# if !(BOOST_WORKAROUND(__MWERKS__, > 0x3100)                      \
        && BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3201)))
#  line BOOST_PP_LINE(__LINE__, result.hpp(function pointers))
# endif

# define N BOOST_PP_ITERATION()

template <class R BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)>
boost::type<R>* result(R (*)(BOOST_PP_ENUM_PARAMS_Z(1, N, A)), int = 0)
{
    return 0;
}

# undef N

/* --------------- pointers-to-members --------------- */
#elif BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == BOOST_PYTHON_POINTER_TO_MEMBER
// Outer over cv-qualifiers

# define BOOST_PP_ITERATION_PARAMS_2 (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/result.hpp>))
# include BOOST_PP_ITERATE()

#elif BOOST_PP_ITERATION_DEPTH() == 2
# if !(BOOST_WORKAROUND(__MWERKS__, > 0x3100)                      \
        && BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3201)))
#  line BOOST_PP_LINE(__LINE__, result.hpp(pointers-to-members))
# endif 
// Inner over arities

# define N BOOST_PP_ITERATION()
# define Q BOOST_PYTHON_CV_QUALIFIER(BOOST_PP_RELATIVE_ITERATION(1))

template <class R, class T BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)>
boost::type<R>* result(R (T::*)(BOOST_PP_ENUM_PARAMS_Z(1, N, A)) Q, int = 0)
{
    return 0;
}

# undef N
# undef Q

#endif // BOOST_PP_ITERATION_DEPTH()
#endif

/* result.hpp
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
*/