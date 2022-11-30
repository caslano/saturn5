#if !defined(BOOST_PP_IS_ITERATING)

// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

# ifndef TARGET_DWA2002521_HPP
#  define TARGET_DWA2002521_HPP

#  include <boost/python/detail/preprocessor.hpp>

#  include <boost/type.hpp>

#  include <boost/preprocessor/comma_if.hpp>
#  include <boost/preprocessor/if.hpp>
#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/debug/line.hpp>
#  include <boost/preprocessor/enum_params.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_params.hpp>

namespace boost { namespace python { namespace detail {

#  define BOOST_PP_ITERATION_PARAMS_1                                                                   \
    (4, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/target.hpp>, BOOST_PYTHON_FUNCTION_POINTER))
#  include BOOST_PP_ITERATE()

#  define BOOST_PP_ITERATION_PARAMS_1                                                                    \
    (4, (0, BOOST_PYTHON_CV_COUNT - 1, <boost/python/detail/target.hpp>, BOOST_PYTHON_POINTER_TO_MEMBER))
#  include BOOST_PP_ITERATE()

template <class R, class T>
T& (* target(R (T::*)) )() { return 0; }

}}} // namespace boost::python::detail

# endif // TARGET_DWA2002521_HPP

/* --------------- function pointers --------------- */
// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == BOOST_PYTHON_FUNCTION_POINTER
# if !(BOOST_WORKAROUND(__MWERKS__, > 0x3100)                      \
        && BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3201)))
#  line BOOST_PP_LINE(__LINE__, target.hpp(function_pointers))
# endif 

# define N BOOST_PP_ITERATION()

template <class R BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)>
BOOST_PP_IF(N, A0, void)(* target(R (*)(BOOST_PP_ENUM_PARAMS_Z(1, N, A))) )()
{
    return 0;
}

# undef N

/* --------------- pointers-to-members --------------- */
#elif BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == BOOST_PYTHON_POINTER_TO_MEMBER
// Outer over cv-qualifiers

# define BOOST_PP_ITERATION_PARAMS_2 (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/target.hpp>))
# include BOOST_PP_ITERATE()

#elif BOOST_PP_ITERATION_DEPTH() == 2
# if !(BOOST_WORKAROUND(__MWERKS__, > 0x3100)                      \
        && BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3201)))
#  line BOOST_PP_LINE(__LINE__, target.hpp(pointers-to-members))
# endif 
// Inner over arities

# define N BOOST_PP_ITERATION()
# define Q BOOST_PYTHON_CV_QUALIFIER(BOOST_PP_RELATIVE_ITERATION(1))

template <class R, class T BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)>
T& (* target(R (T::*)(BOOST_PP_ENUM_PARAMS_Z(1, N, A)) Q) )()
{
    return 0;
}

# undef N
# undef Q

#endif // BOOST_PP_ITERATION_DEPTH()
#endif

/* target.hpp
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
*/