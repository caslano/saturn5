
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
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
*/