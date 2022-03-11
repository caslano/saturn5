
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