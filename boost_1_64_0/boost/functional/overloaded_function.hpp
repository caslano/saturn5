
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/functional/overloaded_function

#ifndef DOXYGEN // Doxygen documentation only.

#if !BOOST_PP_IS_ITERATING
#   ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_HPP_
#       define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_HPP_

#       include <boost/functional/overloaded_function/detail/base.hpp>
#       include <boost/functional/overloaded_function/detail/function_type.hpp>
#       include <boost/functional/overloaded_function/config.hpp>
#       include <boost/typeof/typeof.hpp>
#       include <boost/preprocessor/iteration/iterate.hpp>
#       include <boost/preprocessor/repetition/enum.hpp>
#       include <boost/preprocessor/repetition/repeat.hpp>
#       include <boost/preprocessor/control/expr_iif.hpp>
#       include <boost/preprocessor/control/expr_if.hpp>
#       include <boost/preprocessor/comparison/greater.hpp>
#       include <boost/preprocessor/comparison/less.hpp>
#       include <boost/preprocessor/cat.hpp>
#       include <boost/preprocessor/arithmetic/add.hpp>
#       include <boost/preprocessor/arithmetic/sub.hpp>
#       include <boost/preprocessor/tuple/eat.hpp>
#       include <boost/preprocessor/logical/and.hpp>
#       include <boost/preprocessor/logical/not.hpp>
#       include <boost/preprocessor/facilities/expand.hpp>

#define BOOST_FUNCTIONAL_f_type(z, n, unused) \
    BOOST_PP_CAT(F, n)

#define BOOST_FUNCTIONAL_f_arg(z, n, unused) \
    BOOST_PP_CAT(f, n)

#define BOOST_FUNCTIONAL_f_tparam(z, n, unused) \
    typename BOOST_FUNCTIONAL_f_type(z, n, ~) \

#define BOOST_FUNCTIONAL_f_tparam_dflt(z, n, is_tspec) \
    BOOST_FUNCTIONAL_f_tparam(z, n, ~) \
    /* overload requires at least 2 functors so F0 and F1 not optional */ \
    BOOST_PP_EXPR_IIF(BOOST_PP_AND(BOOST_PP_NOT(is_tspec), \
            BOOST_PP_GREATER(n, 1)), \
        = void \
    )

#define BOOST_FUNCTIONAL_f_arg_decl(z, n, unused) \
    BOOST_FUNCTIONAL_f_type(z, n, ~) /* no qualifier to deduce tparam */ \
    BOOST_FUNCTIONAL_f_arg(z, n, ~)

#define BOOST_FUNCTIONAL_g_type(z, n, unused) \
    BOOST_PP_CAT(G, n)

#define BOOST_FUNCTIONAL_g_arg(z, n, unused) \
    BOOST_PP_CAT(g, n)

#define BOOST_FUNCTIONAL_g_tparam(z, n, unused) \
    typename BOOST_FUNCTIONAL_g_type(z, n, ~)

#define BOOST_FUNCTIONAL_g_arg_decl(z, n, unused) \
    BOOST_FUNCTIONAL_g_type(z, n, ~) /* no qualifier to deduce tparam */ \
    BOOST_FUNCTIONAL_g_arg(z, n, ~)

#define BOOST_FUNCTIONAL_base(z, n, unused) \
    ::boost::overloaded_function_detail::base< \
        BOOST_FUNCTIONAL_f_type(z, n, ~) \
    >

#define BOOST_FUNCTIONAL_inherit(z, n, unused) \
    public BOOST_FUNCTIONAL_base(z, n, ~)

#define BOOST_FUNCTIONAL_base_init(z, n, unused) \
    BOOST_FUNCTIONAL_base(z, n, ~)(BOOST_FUNCTIONAL_g_arg(z, n, ~))

#define BOOST_FUNCTIONAL_using_operator_call(z, n, unused) \
    using BOOST_FUNCTIONAL_base(z, n, ~)::operator();

#define BOOST_FUNCTIONAL_function_type(z, n, unused) \
    typename ::boost::overloaded_function_detail::function_type< \
        BOOST_FUNCTIONAL_f_type(z, n, ~) \
    >::type

#       define BOOST_PP_ITERATION_PARAMS_1 \
            /* at least 2 func to overload so start from 2 to MAX */ \
            /* (cannot iterate [0, MAX-2) because error on Sun) */ \
            (3, (2, BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX, \
            "boost/functional/overloaded_function.hpp"))
#       include BOOST_PP_ITERATE() // Iterate over function arity.

#undef BOOST_FUNCTIONAL_f_type
#undef BOOST_FUNCTIONAL_f_arg
#undef BOOST_FUNCTIONAL_f_tparam
#undef BOOST_FUNCTIONAL_f_arg_decl
#undef BOOST_FUNCTIONAL_f_tparam_dflt
#undef BOOST_FUNCTIONAL_g_type
#undef BOOST_FUNCTIONAL_g_arg
#undef BOOST_FUNCTIONAL_g_tparam
#undef BOOST_FUNCTIONAL_g_arg_decl
#undef BOOST_FUNCTIONAL_base
#undef BOOST_FUNCTIONAL_inherit
#undef BOOST_FUNCTIONAL_base_init
#undef BOOST_FUNCTIONAL_using_operator_call
#undef BOOST_FUNCTIONAL_function_type

#   endif // #include guard

#elif BOOST_PP_ITERATION_DEPTH() == 1
#   define BOOST_FUNCTIONAL_overloads \
        /* iterate as OVERLOADS, OVERLOADS-1, OVERLOADS-2, ... */ \
        /* (add 2 because iteration started from 2 to MAX) */ \
        BOOST_PP_ADD(2, BOOST_PP_SUB( \
                BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX, \
                BOOST_PP_FRAME_ITERATION(1)))
#   define BOOST_FUNCTIONAL_is_tspec \
        /* if template specialization */ \
        BOOST_PP_LESS(BOOST_FUNCTIONAL_overloads, \
                BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX)

// For type-of emulation: This must be included at this pp iteration level.
#   include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

namespace boost {

template<
    BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_f_tparam_dflt,
            BOOST_FUNCTIONAL_is_tspec)
>
class overloaded_function
    // Template specialization.
    BOOST_PP_EXPR_IIF(BOOST_PP_EXPAND(BOOST_FUNCTIONAL_is_tspec), <)
    BOOST_PP_IIF(BOOST_FUNCTIONAL_is_tspec,
        BOOST_PP_ENUM
    ,
        BOOST_PP_TUPLE_EAT(3)
    )(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_f_type, ~)
    BOOST_PP_EXPR_IIF(BOOST_PP_EXPAND(BOOST_FUNCTIONAL_is_tspec), >)
    // Bases (overloads >= 2 so always at least 2 bases).
    : BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads,
            BOOST_FUNCTIONAL_inherit, ~)
{
public:
    template<
        BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_g_tparam, ~)
    > /* implicit */ inline overloaded_function(
            BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads,
                    BOOST_FUNCTIONAL_g_arg_decl, ~))
            // Overloads >= 2 so always at least 2 bases to initialize.
            : BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads,
                    BOOST_FUNCTIONAL_base_init, ~)
    {}

    BOOST_PP_REPEAT(BOOST_FUNCTIONAL_overloads, 
            BOOST_FUNCTIONAL_using_operator_call, ~)
};

template<
    BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_f_tparam, ~)
>
overloaded_function<
    BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_function_type, ~)
> make_overloaded_function(
    BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_f_arg_decl, ~)
) {
    return overloaded_function<
        BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads,
                BOOST_FUNCTIONAL_function_type, ~)
    >(BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_f_arg, ~));
}

} // namespace

// For type-of emulation: Register overloaded function type (for _AUTO, etc).
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::overloaded_function,
    BOOST_FUNCTIONAL_overloads)

#   undef BOOST_FUNCTIONAL_overloads
#   undef BOOST_FUNCTIONAL_is_tspec
#endif // iteration

// DOCUMENTATION //

#else // DOXYGEN

/** @file
@brief Overload distinct function pointers, function references, and
monomorphic function objects into a single function object.
*/

namespace boost {

/**
@brief Function object to overload functions with distinct signatures.

This function object aggregates together calls to functions of all the
specified function types <c>F1</c>, <c>F2</c>, etc which must have distinct
function signatures from one another.

@Params
@Param{F<em>i</em>,
Each function type must be specified using the following syntax (which is
Boost.Function's preferred syntax):
@code
    result_type (argument1_type\, argumgnet2_type\, ...)
@endcode
}
@EndParams

In some cases, the @RefFunc{make_overloaded_function} function template can be
useful to construct an overloaded function object without explicitly
specifying the function types.

At least two distinct function types must be specified (because there is
nothing to overload between one or zero functions).
The maximum number of functions to overload is given by the
@RefMacro{BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX}
configuration macro.
The maximum number of function parameters for each of the specified function
types is given by the
@RefMacro{BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_ARITY_MAX}
configuration macro.

@See @RefSect{tutorial, Tutorial} section, @RefFunc{make_overloaded_function},
@RefMacro{BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX},
@RefMacro{BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_ARITY_MAX},
Boost.Function.
*/
template<typename F1, typename F2, ...>
class overloaded_function {
public:
    /**
    @brief Construct the overloaded function object.

    Any function pointer, function reference, and monomorphic function object
    that can be converted to a <c>boost::function</c> function object can be
    specified as parameter.

    @Note Unfortunately, it is not possible to support polymorphic function
    objects (as explained <a
    href="http://lists.boost.org/Archives/boost/2012/03/191744.php">here</a>).
    */
    overloaded_function(const boost::function<F1>&,
            const boost::function<F2>&, ...);

    /**
    @brief Call operator matching the signature of the function type specified
    as 1st template parameter.

    This will in turn invoke the call operator of the 1st function passed to
    the constructor.
    */
    typename boost::function_traits<F1>::result_type operator()(
            typename boost::function_traits<F1>::arg1_type,
            typename boost::function_traits<F1>::arg2_type,
            ...) const;

    /**
    @brief Call operator matching the signature of the function type specified
    as 2nd template parameter.

    This will in turn invoke the call operator of the 2nd function passed to
    the constructor.

    @Note Similar call operators are present for all specified function types
    <c>F1</c>, <c>F2</c>, etc (even if not exhaustively listed by this
    documentation).
    */
    typename boost::function_traits<F2>::result_type operator()(
            typename boost::function_traits<F2>::arg1_type,
            typename boost::function_traits<F2>::arg2_type,
            ...) const;
};

/**
@brief Make an overloaded function object without explicitly specifying the
function types.

This function template creates and returns an @RefClass{overloaded_function}
object that overloads all the specified functions <c>f1</c>, <c>f2</c>, etc.

The function types are internally determined from the template parameter types
so they do not need to be explicitly specified.
Therefore, this function template usually has a more concise syntax when
compared with @RefClass{overloaded_function}.
This is especially useful when the explicit type of the returned
@RefClass{overloaded_function} object does not need to be known (e.g., when
used with Boost.Typeof's <c>BOOST_AUTO</c>, C++11 <c>auto</c>, or when the
overloaded function object is handled using a function template parameter, see
the @RefSect{tutorial, Tutorial} section).

The maximum number of functions to overload is given by the
@RefMacro{BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX}
configuration macro.

@Note In this documentation, <c>__function_type__</c> is a placeholder for a
symbol that is specific to the implementation of this library.

@See @RefSect{tutorial, Tutorial} section, @RefClass{overloaded_function},
@RefMacro{BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX}.
*/
template<typename F1, typename F2, ...>
overloaded_function<
    __function_type__<F1>, __function_type__<F2>, ...
> make_overloaded_function(F1 f1, F2 f2, ...);

} // namespace

#endif // DOXYGEN


/* overloaded_function.hpp
We8uex+mkRHi5d/Y2Ylnmty9U1vnTOQWEri6wC4v1bAclWq4w1l36dE8SeuxGZyvieLVidTzcs3MkY8+fPy1bru4du7D7pI6XefMryQjGsShR2OViApWAqMujvUduxObev/Y8cr75iS9E+OvjXjULrHkFFaOBgzvRHBZpv3i4RRQ/1pSm+/7M6XHCcu91ZJGJ5b2cKz79PoBi03asVIZuifwA0+p4nxHq6YVAq4fPan7sG7LWTjUPzVyRnUvK7MsoLWCsT7HvCFVV0iNzNJYsubHuy2c1F5UBfO7btuHSZNesnWXip5ebR4qm6qPMnv63F+boSUh3YEf7wrPldCmu46N7ZQNsm9WZUnsLoaRBRp/W6RQn/EV8PGt76/zVccnfLZ7s6tbMfsXOg3qy3V3Cv0oG/V+EUw0/k2jtxN+KcWhgGVfioL9J5G/nj5jqPxs9uGb0EH1tHXuoEe6r5iUSx09qL5eD0i6X7N8/4ZT1oBUTgGh/IY8gYvhDlHj5ZlTrjFqDdY6sdKzy+y/rBLk/jjCbVI+4Ybvcnv/8etgj9i2IbcAN393/KiYwp8pW0qqI/am0UeDnn8PvC8Q1DJJfi6g/O0TpeLSuPyLgss8hWqJSYWp7kd0vsayMKmwheaJBj35ynv/a48O95L3owipbuayce/66fRSi0kj09nG5yw/L45/emwi/SK546iCm4FE4hzyv/e594yu4v6XRbutZLacmryC+ydUScJlH9UnMIcP0ZPW+qTFUX0Qq8RdLEr4Wd9waeH1qSiNo2Lmu17tVqHcFF/88ZRP9OImDW1++nw7+T3DzYrgZWV0vGHsDk786uyv4lWHe3AvJeK2dtgfKNvvVF+kk3e9xe25bhCQFlFj+kmG6dM6YcHH2Bc+JyqiZI455ToF5PzmTuzhyfsnWtL1edTWb13MnKsXEeommtnlDZMJGNkr1bQpV9N/d/9oPjMp86+0D47Zk+7vhfHgto+3X7X+1cCGXeXD8ImmSMkzB/xd3U/0ln8OXu+csNSnio9UuqJMnlNeWR0QbSBv2xMm+tjkQm4rWtC8fldO+WrIIalq534Gy3Pemz538c9rz6vhBLoyfmNS111PINlrv1yq/ilSkSSU1gFpS05mVPdOVVL7EWYIi+kmWN5n6b8UTTEs7PXTSVitPd+wKdStKOt3X4rs9bjbFen+DH27nYInE4bLNJcZxTcL5vsy5GRNn7A0LJDhwPcrqbG9qWehZUjrZPc8c2dDy7LpXc5Xqw3iAe1vrrFafgqcLL51+WvFx5pjvmIGh7Yvya1QNNs7mChf0DJResetyxg+yydGUxrOUTvGQjH4pJAzSN5qUiLw6X35IybqcQI8t0rOBbIcZ/ySFmXPJ8TEZ45uCiaHTlVfD9cjoO9brtpKXpSRPm4g9LLp8tnA8wrLI3hNwukMmj2zgaIiSyyEJc+HZ8uZl71qsxMznLuHvNSu6EYWmMsSagR/Ooq/g/Pk8TErp5hKFzEmY1md95B9TrRfXJFgbsZsvjZyhYnD2PckT8ebDDUpJNvKwtZILni4Z19NNLP+C+JnpPI6yXHquMqSpcYHimuPcHcPjOn4jc2JTh0cUJJ/IKUnZcWDr2LF0/Q7MLo883P92Ss87mlf46U33aYyI8ThSSlvOefinEZwQR/xQu9uEF79fEmCyzEDBfX6TM37aKVds5fb+LxmN5KvzLXxPu3Xd5HC5+N8JNVNWdx7xsTKjxMcVXd6+/roz1/UR/OH3aMW/JkSdBUs1caQlnBrtBCL9dO3jKSZhI04IloRlXGDS77NFi1Zue36hnOOC4MxjrGpAmwKqfcVYsQf2tdlqv1G9jh+YLzsvCpr15tAFnw=
*/