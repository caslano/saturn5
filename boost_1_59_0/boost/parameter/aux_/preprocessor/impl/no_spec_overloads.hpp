// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_NO_SPEC_OVERLOADS_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_NO_SPEC_OVERLOADS_HPP

#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>

// Defines the no-spec implementation function header.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_HEAD(name, is_const)           \
    template <typename ResultType, typename Args>                            \
    BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(name) ResultType                  \
        BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_NAME(                          \
            name, is_const                                                   \
        )(ResultType(*)(), Args const& args)
/**/

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#include <boost/parameter/aux_/preprocessor/impl/parenthesized_return_type.hpp>

// Expands to the result metafunction for the specified no-spec function.
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_HEAD(result, name, is_const)        \
    template <typename TaggedArg0, typename ...TaggedArgs>                   \
    using BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(name, is_const)       \
    = typename BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(result);
/**/
#else
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_HEAD(result, name, is_const)        \
    template <typename TaggedArg0, typename ...TaggedArgs>                   \
    struct BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(name, is_const)      \
      : BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(result)                    \
    {                                                                        \
    };
/**/
#endif  // BOOST_PARAMETER_CAN_USE_MP11

#include <boost/parameter/compose.hpp>
#include <boost/parameter/are_tagged_arguments.hpp>
#include <boost/parameter/aux_/preprocessor/impl/parenthesized_type.hpp>
#include <boost/core/enable_if.hpp>

// Exapnds to a variadic constructor that is enabled if and only if all its
// arguments are tagged arguments.  The enclosing class must inherit from the
// specified base class, which in turn must implement a constructor that takes
// in the argument pack that this one passes on.
#define BOOST_PARAMETER_NO_SPEC_CONSTRUCTOR(class_, base)                    \
    template <                                                               \
        typename TaggedArg0                                                  \
      , typename ...TaggedArgs                                               \
      , typename = typename ::boost::enable_if<                              \
            ::boost::parameter                                               \
            ::are_tagged_arguments<TaggedArg0,TaggedArgs...>                 \
        >::type                                                              \
    > inline explicit                                                        \
    class_(TaggedArg0 const& arg0, TaggedArgs const&... args)                \
      : BOOST_PARAMETER_PARENTHESIZED_TYPE(base)(                            \
            ::boost::parameter::compose(arg0, args...)                       \
        )                                                                    \
    {                                                                        \
    }
/**/

// Exapnds to a variadic constructor that is enabled if and only if all its
// arguments are tagged arguments.  The specified function must be able to
// take in the argument pack that this constructor passes on.
#define BOOST_PARAMETER_NO_SPEC_NO_BASE_CONSTRUCTOR(class_, func)            \
    template <                                                               \
        typename TaggedArg0                                                  \
      , typename ...TaggedArgs                                               \
      , typename = typename ::boost::enable_if<                              \
            ::boost::parameter                                               \
            ::are_tagged_arguments<TaggedArg0,TaggedArgs...>                 \
        >::type                                                              \
    > inline explicit                                                        \
    class_(TaggedArg0 const& arg0, TaggedArgs const&... args)                \
    {                                                                        \
        func(::boost::parameter::compose(arg0, args...));                    \
    }
/**/

#include <boost/parameter/aux_/preprocessor/nullptr.hpp>
#include <boost/preprocessor/control/expr_if.hpp>

// Exapnds to a variadic function that is enabled if and only if
// all its arguments are tagged arguments.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD(name, impl, is_m, c)       \
    template <typename TaggedArg0, typename ...TaggedArgs>                   \
    BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(impl)                             \
    inline typename ::boost::lazy_enable_if<                                 \
        ::boost::parameter                                                   \
        ::are_tagged_arguments<TaggedArg0,TaggedArgs...>                     \
      , BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(                        \
            impl, c                                                          \
        )<TaggedArg0,TaggedArgs...>                                          \
    >::type BOOST_PARAMETER_MEMBER_FUNCTION_NAME(name)                       \
    (TaggedArg0 const& arg0, TaggedArgs const&... args)                      \
    BOOST_PP_EXPR_IF(c, const)                                               \
    {                                                                        \
        return BOOST_PP_EXPR_IF(is_m, this->)                                \
        BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_NAME(impl, c)(                 \
            static_cast<                                                     \
                typename BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(       \
                    impl, c                                                  \
                )<TaggedArg0,TaggedArgs...>::type(*)()                       \
            >(BOOST_PARAMETER_AUX_PP_NULLPTR)                                \
          , ::boost::parameter::compose(arg0, args...)                       \
        );                                                                   \
    }
/**/

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/preprocessor/impl/parenthesized_return_type.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

// Expands to the result metafunction for the specified no-spec function.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_HEAD(result, name, is_const)        \
    template <                                                               \
        BOOST_PP_ENUM_BINARY_PARAMS(                                         \
            BOOST_PARAMETER_COMPOSE_MAX_ARITY                                \
          , typename TaggedArg                                               \
          , = ::boost::parameter::void_ BOOST_PP_INTERCEPT                   \
        )                                                                    \
    >                                                                        \
    struct BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(name, is_const)      \
      : BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(result)                    \
    {                                                                        \
    };
/**/

#include <boost/parameter/compose.hpp>
#include <boost/parameter/aux_/preprocessor/impl/parenthesized_type.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#if defined(BOOST_NO_SFINAE)

// Exapnds to a tagged-argument constructor overload that passes the argument
// pack to the base class delegate constructor.
#define BOOST_PARAMETER_NO_SPEC_CONSTRUCTOR_OVERLOAD_Z(z, n, data)           \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename TaggedArg)>              \
    BOOST_PP_EXPR_IF(BOOST_PP_EQUAL(n, 1), explicit) inline                  \
    BOOST_PP_TUPLE_ELEM(2, 0, data)(                                         \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, TaggedArg, const& arg)           \
    ) : BOOST_PARAMETER_PARENTHESIZED_TYPE(BOOST_PP_TUPLE_ELEM(2, 1, data))( \
            ::boost::parameter::compose(BOOST_PP_ENUM_PARAMS_Z(z, n, arg))   \
        )                                                                    \
    {                                                                        \
    }
/**/

// Exapnds to a tagged-argument constructor overload that passes the argument
// pack to the delegate function.
#define BOOST_PARAMETER_NO_SPEC_NO_BASE_CONSTRUCTOR_OVERLOAD_Z(z, n, data)   \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename TaggedArg)>              \
    BOOST_PP_EXPR_IF(BOOST_PP_EQUAL(n, 1), explicit) inline                  \
    BOOST_PP_TUPLE_ELEM(2, 0, data)(                                         \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, TaggedArg, const& a)             \
    )                                                                        \
    {                                                                        \
        BOOST_PP_TUPLE_ELEM(2, 1, data)(                                     \
            ::boost::parameter::compose(BOOST_PP_ENUM_PARAMS_Z(z, n, a))     \
        );                                                                   \
    }
/**/

#include <boost/parameter/aux_/preprocessor/nullptr.hpp>

// Exapnds to a tagged-argument function overload.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD_Z(z, n, data)              \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename TaggedArg)>              \
    BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(BOOST_PP_TUPLE_ELEM(4, 1, data))  \
    inline typename BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(            \
        BOOST_PP_TUPLE_ELEM(4, 1, data)                                      \
      , BOOST_PP_TUPLE_ELEM(4, 3, data)                                      \
    )<BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)>::type                         \
        BOOST_PARAMETER_MEMBER_FUNCTION_NAME(                                \
            BOOST_PP_TUPLE_ELEM(4, 0, data)                                  \
        )(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, TaggedArg, const& arg))        \
        BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(4, 3, data), const)             \
    {                                                                        \
        return BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(4, 2, data), this->)     \
        BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_NAME(                          \
            BOOST_PP_TUPLE_ELEM(4, 1, data)                                  \
          , BOOST_PP_TUPLE_ELEM(4, 3, data)                                  \
        )(                                                                   \
            static_cast<                                                     \
                typename BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(       \
                    BOOST_PP_TUPLE_ELEM(4, 1, data)                          \
                  , BOOST_PP_TUPLE_ELEM(4, 3, data)                          \
                )<BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)>::type(*)()        \
            >(BOOST_PARAMETER_AUX_PP_NULLPTR)                                \
          , ::boost::parameter::compose(BOOST_PP_ENUM_PARAMS_Z(z, n, arg))   \
        );                                                                   \
    }
/**/

#else   // !defined(BOOST_NO_SFINAE)

#include <boost/parameter/are_tagged_arguments.hpp>
#include <boost/parameter/aux_/preprocessor/nullptr.hpp>
#include <boost/core/enable_if.hpp>

// Exapnds to a tagged-argument constructor overload that passes the argument
// pack to the base class delegate constructor.  This constructor is enabled
// if and only if all its arguments are tagged arguments.
#define BOOST_PARAMETER_NO_SPEC_CONSTRUCTOR_OVERLOAD_Z(z, n, data)           \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename TaggedArg)>              \
    BOOST_PP_EXPR_IF(BOOST_PP_EQUAL(n, 1), explicit) inline                  \
    BOOST_PP_TUPLE_ELEM(2, 0, data)(                                         \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, TaggedArg, const& arg)           \
      , typename ::boost::enable_if<                                         \
            ::boost::parameter::are_tagged_arguments<                        \
                BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)                      \
            >                                                                \
        >::type* = BOOST_PARAMETER_AUX_PP_NULLPTR                            \
    ) : BOOST_PARAMETER_PARENTHESIZED_TYPE(BOOST_PP_TUPLE_ELEM(2, 1, data))( \
            ::boost::parameter::compose(BOOST_PP_ENUM_PARAMS_Z(z, n, arg))   \
        )                                                                    \
    {                                                                        \
    }
/**/

// Exapnds to a tagged-argument constructor overload that passes the argument
// pack to the delegate function.  This constructor is enabled if and only if
// all its arguments are tagged arguments.
#define BOOST_PARAMETER_NO_SPEC_NO_BASE_CONSTRUCTOR_OVERLOAD_Z(z, n, data)   \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename TaggedArg)>              \
    BOOST_PP_EXPR_IF(BOOST_PP_EQUAL(n, 1), explicit) inline                  \
    BOOST_PP_TUPLE_ELEM(2, 0, data)(                                         \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, TaggedArg, const& a)             \
      , typename ::boost::enable_if<                                         \
            ::boost::parameter::are_tagged_arguments<                        \
                BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)                      \
            >                                                                \
        >::type* = BOOST_PARAMETER_AUX_PP_NULLPTR                            \
    )                                                                        \
    {                                                                        \
        BOOST_PP_TUPLE_ELEM(2, 1, data)(                                     \
            ::boost::parameter::compose(BOOST_PP_ENUM_PARAMS_Z(z, n, a))     \
        );                                                                   \
    }
/**/

// Exapnds to a function overload that is enabled if and only if
// all its arguments are tagged arguments.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD_Z(z, n, data)              \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename TaggedArg)>              \
    BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(BOOST_PP_TUPLE_ELEM(4, 1, data))  \
    inline typename ::boost::lazy_enable_if<                                 \
        ::boost::parameter                                                   \
        ::are_tagged_arguments<BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)>      \
      , BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(                        \
            BOOST_PP_TUPLE_ELEM(4, 1, data)                                  \
          , BOOST_PP_TUPLE_ELEM(4, 3, data)                                  \
        )<BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)>                           \
    >::type BOOST_PARAMETER_MEMBER_FUNCTION_NAME(                            \
        BOOST_PP_TUPLE_ELEM(4, 0, data)                                      \
    )(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, TaggedArg, const& arg))            \
    BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(4, 3, data), const)                 \
    {                                                                        \
        return BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(4, 2, data), this->)     \
        BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_NAME(                          \
            BOOST_PP_TUPLE_ELEM(4, 1, data)                                  \
          , BOOST_PP_TUPLE_ELEM(4, 3, data)                                  \
        )(                                                                   \
            static_cast<                                                     \
                typename BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(       \
                    BOOST_PP_TUPLE_ELEM(4, 1, data)                          \
                  , BOOST_PP_TUPLE_ELEM(4, 3, data)                          \
                )<BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)>::type(*)()        \
            >(BOOST_PARAMETER_AUX_PP_NULLPTR)                                \
          , ::boost::parameter::compose(BOOST_PP_ENUM_PARAMS_Z(z, n, arg))   \
        );                                                                   \
    }
/**/

#endif  // BOOST_NO_SFINAE

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

// Emulates a variadic constructor that is enabled if and only if all its
// arguments are tagged arguments.  The enclosing class must inherit from the
// specified base class, which in turn must implement a constructor that takes
// in the argument pack that this one passes on.
#define BOOST_PARAMETER_NO_SPEC_CONSTRUCTOR(class_, base)                    \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        1                                                                    \
      , BOOST_PP_INC(BOOST_PARAMETER_COMPOSE_MAX_ARITY)                      \
      , BOOST_PARAMETER_NO_SPEC_CONSTRUCTOR_OVERLOAD_Z                       \
      , (class_, base)                                                       \
    )
/**/

// Emulates a variadic constructor that is enabled if and only if all its
// arguments are tagged arguments.  The specified function must be able to
// take in the argument pack that this constructor passes on.
#define BOOST_PARAMETER_NO_SPEC_NO_BASE_CONSTRUCTOR(class_, func)            \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        1                                                                    \
      , BOOST_PP_INC(BOOST_PARAMETER_COMPOSE_MAX_ARITY)                      \
      , BOOST_PARAMETER_NO_SPEC_NO_BASE_CONSTRUCTOR_OVERLOAD_Z               \
      , (class_, func)                                                       \
    )
/**/

// Emulates a variadic function that is enabled if and only if
// all its arguments are tagged arguments.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD(name, impl, is_m, c)       \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        1                                                                    \
      , BOOST_PP_INC(BOOST_PARAMETER_COMPOSE_MAX_ARITY)                      \
      , BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD_Z                          \
      , (name, impl, is_m, c)                                                \
    )
/**/

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* no_spec_overloads.hpp
8adhb39AyD87vo410y6eNx267RIhOkASK9dpiMdpJBA7gkCSOCATA0xXov1HsP+ItiLm8qYAtdjByccXS+knk+qS9KJdvDBCq1+0cOc2WAlJFp0lbFYdwYT8gVvvtp8LJV3eesfjP9XesplsHtT5irK8l+FiZsIe2/px++bH7OsjYQJFek2IW+t6ssK8jl4Jof3g3fPQJmC/Y+r4UCMSQnae1VQl2lLygBpofypkYSFLhqBQ082TMCmGw0Yqsl/gmZ2zqhfCjUaQ3xjtEcIYBaVRJeyNOwRzBh3SXdWfl35f/Ve9VJonNLcPKwf560PfPv5cuTXmp4g8/cH+DqZtDmKJ0vXlZIGGODcGHsONY25fILjPT2nFfSqK7CnKnwIv0Ru94XmntbEuI5ap+6mxy7/pCe8XC7zCa4y5zUuD7aoYj4rp2qmb1BaeahpGhYQschjsz3mXeU5J+ckrJnzg090pfteuGy799TJ2z8c8ZBivTW01oBsue4bmh5eCHinRUZCMgYiYRmAiNicgcco8bqt0cek4Ix7smWdDQ71AKnmihIwFjeG9Fj+tkZ3Qhva95ylb+Ytew/b+2uXyHKLQET6Y51/Qrad03JWWGU5nKzBHAVzrUzQ6qOOa1yTDl7XWOZH5KqqXw9MyTOXQVXAbYzK3yEcH1Y/jkyYWAvv6CHqgJfHwooZtYz8a1e5j5TKW4qrikZ1u9/DpnmpIYMeav6ex/Ltlb78f7G4WokFrtnxyW8+Ld9kJiyb5+fnxF/mjnA/3lIWg9rPjnvJwC9XXka0gChhI7Edy2EmuY5AgPsgdYlxYAC/YAREhArDnj1GRf3bNCFAg3G59fU5viHYl1SgcHzmPsOtsTxg+dWtPMI/z2yuKUXR6KyYQMVPVZtDq5wBJRbFSPDCbgKU/g88qMnHPRmqRjpY9Wp+MjVQcj5Ewj9pf5ItR/YIIEiblI3nTlb9R7pi09tqVLtEa4nCVPfq0zYGw+GlP0NyM73X2SmBCh7odJZbI8PFCemtmPb4Qkr9WQM/J6XU5uypTgi65rlWpcvThM353YzvX6rXwc+I5Vb6wYnhSIKVIvj7rgyUtXaNtdcdfc+OYDAVYjE542vUmZ13yWErf6KvoFxfzD2dGFhxf758LMbmaVJ1tERBdWwbtMHlgVFwj+q1JUIvkGOZJ1AO5qVfSPnfZ5lCuewGKTtZQGErjK4o/vuKpjyaqqEpenUqc9LpH/n5PK6fUS7KqjAM3sTdO7GnZ6ZEbdi3HfLft187o/tqkiwV5Ky5Uj3yTFWbysDq+9RC17Guo78OAVc7ubONyPsV8sOwABRleUANlKGLgH1Fzkv9RiaFW94Grj/0sZ0EvlMrPVm5E06daOv+1dMAVz5DoyCa7JjyZCJXatr20YfzFZs09fs0oS41GyhLtTSt3csaCaYB7kHZUVTuiX7r7SHZ9dhLokBpQvVHSKWlOT0UFpTyPt0ihcwGkohIalkGBEirIzHzwHs3Y5dkSkiLCHMoAw2Qr0KJNn+5Fh/F+5RKqLPXij5X/rji/JM6stwiflpVlSzxpL/O+vXNw4HPWhRvu8lFbO9OsHZfaIhQr3SLC8oeq+oFtw2Bc/ZxFV0b2O+Xoa8HB8IT8itDeyfY4/vCGx8DAoB38mD59hBcWT0ZGJr559Ws7Nji4Q/pMkeOXGP6WzbwbY3p6Ts6zFra/43N+SclxgTVhHAHVLsSpDmpq5vMF+tgmuTFSsPVcNje/jF/3JQsprkPKG0nFh0n/xIuFVl21KZX15KwHOZEe8vVT8/BlHEsHmD4niRl503dByWBdCHNHvOqIVNNoHdbN4jInTgbK5+Txeawj1aLn7YB4k3qbyD4ThUL0koqrAwdCO8WHHPopFVrzHhJopsHV7RMcKZ/CCeTeVlV4zKZvk9C8cUwzo/s3NZjOOyaly4BPY805a2fVlG3sQDjsIMgdBtlgoLx9MZay29UV5pxVbTQLH6f2PoJJUVwbYV9hnLpaDzWVVOZwZdxw5tR8sNAxVWdvrqC+XTXT47LjAJVfOqFTY3FlhAlsz4qastVb2Q7OityaOVHs8PFcRf2nbhg69uPPZBtnFw+YKxuzPItDS9XCShnvS50WzNU6EVGgy4hl8ShvIx+o8drtzV1mFDjwQCmqurxo4eIhMUu21+uPZJPcLyyIKFcCkpbf1t1QyAjdqCKzhjRi8zTtOiq9o1bNcZPnzx+DByzJugTkqqRfaqvZitdPsG2v3k8/ncf5k0voauaHhwePRSfco8VP/yST/Nap7EPBTI8sEQb2sinSXqU+RnHWslOG9fKB3cA1ywsN5fWM9Y7RJND1SuiZPil9Vz87KW24yxAaMT/8DTOiKhTY5OyzcueQelN2q2qurbn96LWG0xkekoAEYXrSMUocBx+y89S00sDWaYRcP6rlt2ptIcjH2SaZvPxBWfjTdMh0MuGosbmeN5qImfPvFfW3qhdX/L6nKdl3n1OP1SLoukRq18Rv06B7rQIi1aebYs5BUmdmkTIWGXOfbL76iE/uSjImGhYKWx4TzjEjk+L6XyVCMjqiq/NV3ZTNhKjUSHbG54RlKSP4Pp6tldUo0SU70y/cqd3l75qVe9ivuJxcHLCppI+FgTPT+U9gh6pq1PXVnHNt53mdf3dB+6YqVdHEt6mNxC4DGCBhRfH+bsMWVodKoLGNWhm+aG/JlmAKoGix4s4S339RahwuTdnX+gwfthsyDL6e+NVbW4Sqck2lMRhaUhmqgMLjZM3HLp7O2K9yres4QF2SOYoVuNxh4gpsMRdYIGxgDfFKztYi/dAZelbS8rfQHizSpuVEuPc89N/H2wv7NZPqVwbXdloOWp7gdu7NeyxKQi1a5R2tmsvRT23nzD+MwFU7Zm+N+DhnsWxq7d1PWrDOGJzs2Qu8gR+uRxXasHQXRf5Unn42X4QljEqcPOj6Jxkt9zAUQmFEtHyzy/VAtGeZ1E0/SAvRstZ/YsebbPuxmKlBiwZWmp+pAl+jQX9E82Jh3tFcHIOAI8b79SCyqFB1Sw8TdyLHF/EJiachfMlIJZDc41sSfS14XbpWzKZbVmu6rb768s4yeCTdaqr1PXuxXMcpaAJ9elc4s/797GdTB3D/nfyb1u4K+pFFjwtmweBDvjK5nNCnoCob06HSrYRcuT7Ol2ZIidsPVNsIubInk0D3ObTDMJ/SrhfN9JWNXKasvdQzlZH+0bDnxHaDaWcm7Q2eVONMcQKDoYCbCT6mItMoGFyl+t55TWc1f5yzLPlkLOSvu4DT5M7zkj/nvnPqTCtKCiOaA0nrPBkitxqG9Lyth6M87uld595jFNTkqTRiVbSXao1R5NSrocmkEnsmkLNn7ArdVlOGXMLqogZog7HDZHjd/mkjwpL1iLqHBPXQ6434ApczTj+bWMWPxtP4R/GHKVfE5X38NfU/1dcbpIefSk/FSs9hWKwT+KoMwv9MH+c96t9Lyy8wsxOtxsSW6+fMbNZePOK3i+t2KcujLczjFaUdgp5z+YREbjH1FqPwjDZ7dTTpsNRJSVVb+R+V6FkJPi2sMPzgC1wiTNoaFCL+xIFHc7HageBZRMvE/5nVToGCamwSGsWlVjv4O42KlJwcTInFjJIoDqMGrdqqKS0gi1RNNS3C6iqaeM17wIOyqCR7sIIiZenRDv4ttgO2vHztcRwSuWR8YSD9FsrahNoBK4I3lkxJ7EUBhd8ZAbUmcmmE9q7mL0e3xytjsaiY05OrQlxFQKxQWmP44ynl5shGUHexYjm6Qk3hEfaPxbym7VOYRAy2JXs3gVAnPJWr624/ig2SA6UPKZrTXV9vSD3dC8+0Yhx0JrWPTJdlJWNuVwYUI1CpOl1WuIGdKwlyuGDpikI8xiH52ItYZgSj698QJDCi9wZYxDLEes01BgSKlCp7vi3VJ9zHucGM2jSrbj7kmDlh9a/K2MMCVJ9LqlMDp5fLkSAUEMp/zdyxupuRzasRl59R8+cHIfXTwC48mJ0kfmvOWD3twrSZMzl9GsPPn/qjenVihJQwxXRrYGV21vzV5NOXQJXfOTejEs4xQFKUlJqxuDiHYMMQvRbTQae+EuDv4gdp36G+n/o4fjgkJm8MCRW9uNW2JeZYdoWoqpKo/CnnA+s9wGXCE4oJ7SSrgSwqQHFduCsxZCODIAPZ4XlgsxWAA9cV+6dfhcC8jlEzngTxLsiLx+FY+POKjxgkUpgv1aQfgXExKZsU0UsogvBupwrOt37nlyR+LKlr8fnfr4tLAqIa9TehVAbpfCWfql2lFhHl3eB+29c49w7ekP6CO9P1eZuPvyBmEZaQexcDwOxZlyADH/wQ1Pr06pdTS1Y7Kp9lERuEAn9nQomKgk3s18fu8aaj+u3PXbJ+1BM8JwZDPZUGYOnHcOV78vGt2GFCX3e6olO9aeMVxoff+a99vxapVzESnQCpMHdr3lZKij7ds2akB+HTi1Dd0ZUiyjQJedaYphSHgS81By1nBVva4BlIev+eVIx1f4w14boobJNAQvql8LjIr2HKU6U878j/Yok/m1VL9O7APxbTHdLWclJN623U4jmlR6C3TV+pLDqYdZcJ6nNx1STaXcpGWbreY09FCfarjofrwmCNszvMC87Yj9DHU0tWvxg/MyPs3ALbcD2j0DUYLH9WfXn13nEzLnkqUq+o24kP0egefMza5o4erMOKQ0gES4OYBBcBTgGDqr4KLyiQRL7zxHMIzMEGjstwebif2dyjW4lXaqGh0vzqE1PhtywBSlzQI1ybjmaRfINsXb9Ne5jTIG2LD1T10ccx7ogXE9IkQhOvl0kZbtBlVbBYz8Lb1eWAVeSjGn6lQ74AQsdPu+0qaQIl5dgG9HicHQ3m6rC8mb9gbi6PkCddVkQQznYVG/5N1upKjjcbWzlYEDi5nLDKAIqFQ1WcSXt2Q02tGDiNwR0ygSBDWLmtcFdze4qUSXvyeZJUzm/dx3rHHS/0U5dtHvXq9AkXycnJ/vUNiR97iJplwb4kuhGFuw4s1LRbX3qc/X6/EP1dDKK0oFWXLu3wxtyTIlPxLMKCE39J9yc7fF89SEwOFvyRcilagrop4LCtXN/53AVHQCcnqMhEQxrbGDjzrjiDDz6E98OJUqIP31XSrwgki7uIQaYjqlI9wYUY8RFAYsLh0Sc2F0rbxepLG0V6WiHpfZI1xHyBIJsgfoeBFBRMegCBHftsN3jhrOGHmPigbU0Y3/6xLmFCXD4o5Bpj9VBqcwle9wNzMAMx3YfZ5CN+FA33c3KjxL0GWdqKh8VymuFr0feuQ0HXW7aZu6kh2Wbf8zApp05u+SdKZuhDBD1WIgbMFNmHbjFhNpvBDnrgb2nPPFnhAEeOseaD4/Csx+RB7MBJNAFrTjD09RMuuL24AQTywAR4YbjYOfMb7x8YgdOSjlDpqciJsEJ13tL1N78l+pkl2eCJRRQHUGB/sA7sNzR0U6QuDKVqdLExlUHjityCO5W7EdOASWV9SMNyXCtqmor2RhNtNVV6Q4lVGxbFOgqjuDKrOGFROxxBVnufpYtFBID8LOBTeTcejOQ9blj/QgGOtT9GjXyXDtsS+zNcj/74Y96Brsoif6o8mEjCnYNea4HUp3FzW97jukyVbEB8zb0Jzw07IucrnaGf64ta53hXB55ciohZYeoIpkVl8kaAoCga/ADkRLT5REHYoaST9QMdO3VNyPKoYOxUzrtxyrAqA1xLBFafGyy5Mlv9BSg1DT6hUNEJC7itJ2OBJ5t1dPyubtLk84LIIJNypvbttjPT886T5NmyG7uuSwIrh0XYMHf5NIUSeJ4NhH/faq0zgE9Sxf0GUnnhIdj1pIr4M+qWHvllyqyivUR3HRE7TAQPHuE5Wf5KNw6f0KMsO2lUkBV0M98VnK9g9eycGHN5OoYF3BhNhRsj1Y7Ug3wT3ae/hNg3tiKIpgWc7Hbu/a3hHArI3j66WcjBvveSdSIrqE45w/ZTTi8ha5JFDbdyWhECkS13TUM/LlbvL5UHHqS01zfyuxLm8M885qXMzPeaoBhn6CBV2RDM37lVmxph1QhdI7wHX4khKDkSq4s51h5sYUyfiD/0v5d68qwXHch/FPl7CTJh0/X+MHXYCzWSLcrRMKintx0/llPGUIH5vXodW5sPNUCg9T6uuxX4e4+u/Z4PsrEuJT+k8vk7rs6w4C5IJoQBc58EjoasFGW7UXD9sHD6QkI6iTjVKX+agL9TergxrcGZ6ip9BASVJTBbiGFV7EUGsjcF5bfQee1wd6nUX54ioq3lRGIW+k6FjYPe5S9OuGIkKpkC3SCdOjqbc8R7k5/COFLDZM4N4sSZ4r/R98/vkR2lM6MRXEp6ck+aJQWnFCA34puw0ZjHdvzMak9pwmb7Fkt2YjlgBWkQqGDzCASfHa5bRGxcSBpE/LL1jrdPB6Xw//wBIlQ4kZab4PZHHmFuKO+pY2VoC9XCUtQwRq9ItRKkm2o1xfrbxooklCMkDgv4bj/bX7XE1Gp1TeK/El863iwgg1Secuhe8rc2jq8u2sOELfXlR12qY/B477vwYA4n0ccFKRMT1bUr7/Zqk4tqxU7ld+LZILTZKtJ17Kd1Sr9rtlaLl5of/fyepO695q9Pyk0uOPUMpkexpEzZ9rEGCst6JFidrjyrLx+VqKVWSI4IXtnbcpO6rBSmlBQE5abPUW+S7/MYeX0dMDi4kMURIf2KwjOPHzYZJ4srvmfFTkgka9CYmAPg5J7zJVViMZRdF8h2owkJDWyewWOukzNtqj9NDYYDvXQXzkeUymPTo06/I2SKL2JG1H4UjR04reFs3Sgv1TqX/lD5sQtV3HFcXGDoLhZbloTyF4Mp9OcG4mq7LkHjQ6Y9ZX6NsJeQ5iA7lCsddqVPYWGUEzy8JfG2Aa24JxYhpYc1dKA5LXpfdyGDAGN0xVfUffb9BuzOaGGCiW12/P7tEBMO+iyNX5a1s2/s489ONKbefIwv+bmDci0LyW4Xd2fDdn+ls+EyeLzVuq0drh7sCUrlUOdbSO/cqEnFdq6o/vtpHOyB5pKXYQ/vtWtXFMmqn6h9E7TLuE1GcIS6cgxuxl/9lT4/qLRGB7rUEN6OjuUuWfP8jv2CVlynrxlYMx63g1JcI+WiafUspe3Hi89EOuEFats2pg/e29rafAlMvbc915t1Zup81dO1vFsnWDv6SSszVOZk3/5eOZjQ501FnVTVPHeSQPpdHfTYf/K1JFZbHeguLy+78vkd40AyvDp1aGu2Ueu/zOKP9ProM/x/fLxjjDDAsi06tu2Zb2zbtm3btm3btm3btm2bb+/z/rybe/KS7pXKSiVdqe50aiVdXVPrSoCN7cfIwPR5gyoeAZK983wMnLOWXRdWuxcFWkOZW1gvhz+bOhTm9e1K7Flb9ftyH/SJBvTsAPtNuhhR+1Xq6gkNbzWAeX4uoPKxju03UGjvMulSUo8xMWyb2WxUDrLGkI59bh7wYhTP+GKJeNxzEb3Chnqc2NIKICMDrHJxFh3r6BQuO8sOYlQlKOxZroQjmFTdodbZXJ9zxw8ZWhB1Uw5bhcYjRTeWLsdKhFu0CNDBPUFLvDRQWDRMoA+PndS64X8SKsh6C2PbqkFx5qfzXRy+2Whgv/Htc2E+NF8z
*/