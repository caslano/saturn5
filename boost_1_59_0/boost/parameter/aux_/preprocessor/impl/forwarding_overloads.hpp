// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FORWARDING_OVERLOADS_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FORWARDING_OVERLOADS_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#include <boost/preprocessor/cat.hpp>

// Expands to a forwarding parameter for a constructor or forwarding function.
#define BOOST_PARAMETER_FUNCTION_ARG_TYPE_Z(z, n, type_prefix)               \
    BOOST_PP_CAT(type_prefix, n)&&
/**/

#include <utility>

// Expands to an argument passed from a forwarding function to the front-end
// implementation function, or from a constructor to its delegate.
#define BOOST_PARAMETER_FUNCTION_FORWARD_PARAM_Z(z, n, type_prefix)          \
    ::std::forward<BOOST_PP_CAT(type_prefix, n)>(BOOST_PP_CAT(a, n))
/**/

#include <boost/parameter/aux_/preprocessor/impl/parenthesized_type.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// Expands to the default constructor, whose job is to pass an empty back to
// the delegate constructor of the base class.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_0_Z(z, n, data)                 \
    inline BOOST_PP_TUPLE_ELEM(2, 0, data)()                                 \
      : BOOST_PARAMETER_PARENTHESIZED_TYPE(BOOST_PP_TUPLE_ELEM(2, 1, data))( \
            BOOST_PP_CAT(constructor_parameters, __LINE__)()()               \
        )                                                                    \
    {                                                                        \
    }
/**/

#include <boost/parameter/aux_/pp_impl/argument_pack.hpp>
#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>
#include <boost/preprocessor/control/expr_if.hpp>

// Expands to a 0-arity forwarding function, whose job is to pass an empty
// pack to the front-end implementation function.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_0_Z(z, n, data)            \
    BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(BOOST_PP_TUPLE_ELEM(4, 1, data))  \
    inline BOOST_PARAMETER_FUNCTION_RESULT_NAME(                             \
        BOOST_PP_TUPLE_ELEM(4, 1, data)                                      \
      , BOOST_PP_TUPLE_ELEM(4, 3, data)                                      \
    )<                                                                       \
        ::boost::parameter::aux::argument_pack<                              \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(4, 1, data)                              \
              , BOOST_PP_TUPLE_ELEM(4, 3, data)                              \
            )                                                                \
        >::type                                                              \
    >::type                                                                  \
    BOOST_PARAMETER_MEMBER_FUNCTION_NAME(BOOST_PP_TUPLE_ELEM(3, 0, data))()  \
    BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(4, 3, data), const)                 \
    {                                                                        \
        return BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(4, 2, data), this->)     \
        BOOST_PARAMETER_FUNCTION_IMPL_NAME(                                  \
            BOOST_PP_TUPLE_ELEM(4, 1, data)                                  \
          , BOOST_PP_TUPLE_ELEM(4, 3, data)                                  \
        )(                                                                   \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(4, 1, data)                              \
              , BOOST_PP_TUPLE_ELEM(4, 3, data)                              \
            )()()                                                            \
        );                                                                   \
    }
/**/

#include <boost/parameter/aux_/preprocessor/impl/function_forward_match.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

// Expands to a forwarding function, whose job is to consolidate its arguments
// into a pack for the front-end implementation function to take in.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_1_Z(z, n, data)            \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename ParameterArgumentType)>  \
    BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(BOOST_PP_TUPLE_ELEM(4, 1, data))  \
    inline typename BOOST_PARAMETER_FUNCTION_RESULT_NAME(                    \
        BOOST_PP_TUPLE_ELEM(4, 1, data)                                      \
      , BOOST_PP_TUPLE_ELEM(4, 3, data)                                      \
    )<                                                                       \
        typename ::boost::parameter::aux::argument_pack<                     \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(4, 1, data)                              \
              , BOOST_PP_TUPLE_ELEM(4, 3, data)                              \
            )                                                                \
          , BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_PARAMETER_FUNCTION_ARG_TYPE_Z                          \
              , ParameterArgumentType                                        \
            )                                                                \
        >::type                                                              \
    >::type                                                                  \
    BOOST_PARAMETER_MEMBER_FUNCTION_NAME(BOOST_PP_TUPLE_ELEM(4, 0, data))(   \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, ParameterArgumentType, && a)     \
        BOOST_PARAMETER_FUNCTION_FORWARD_MATCH_Z(                            \
            z                                                                \
          , BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(4, 1, data)                              \
              , BOOST_PP_TUPLE_ELEM(4, 3, data)                              \
            )                                                                \
          , n                                                                \
          , ParameterArgumentType                                            \
        )                                                                    \
    ) BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(4, 3, data), const)               \
    {                                                                        \
        return BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(4, 2, data), this->)     \
        BOOST_PARAMETER_FUNCTION_IMPL_NAME(                                  \
            BOOST_PP_TUPLE_ELEM(4, 1, data)                                  \
          , BOOST_PP_TUPLE_ELEM(4, 3, data)                                  \
        )(                                                                   \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(4, 1, data)                              \
              , BOOST_PP_TUPLE_ELEM(4, 3, data)                              \
            )()(                                                             \
                BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                             \
                    n                                                        \
                  , BOOST_PARAMETER_FUNCTION_FORWARD_PARAM_Z                 \
                  , ParameterArgumentType                                    \
                )                                                            \
            )                                                                \
        );                                                                   \
    }
/**/

#include <boost/preprocessor/comparison/equal.hpp>

// Expands to a constructor whose job is to consolidate its arguments into a
// pack for the delegate constructor of the base class to take in.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_1_Z(z, n, data)                 \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename ParameterArgumentType)>  \
    BOOST_PP_EXPR_IF(BOOST_PP_EQUAL(n, 1), explicit)                         \
    inline BOOST_PP_TUPLE_ELEM(2, 0, data)(                                  \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, ParameterArgumentType, && a)     \
        BOOST_PARAMETER_FUNCTION_FORWARD_MATCH_Z(                            \
            z                                                                \
          , BOOST_PP_CAT(constructor_parameters, __LINE__)                   \
          , n                                                                \
          , ParameterArgumentType                                            \
        )                                                                    \
    ) : BOOST_PARAMETER_PARENTHESIZED_TYPE(BOOST_PP_TUPLE_ELEM(2, 1, data))( \
            BOOST_PP_CAT(constructor_parameters, __LINE__)()(                \
                BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                             \
                    n                                                        \
                  , BOOST_PARAMETER_FUNCTION_FORWARD_PARAM_Z                 \
                  , ParameterArgumentType                                    \
                )                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
    }
/**/

#include <boost/preprocessor/control/if.hpp>

#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_Z(z, n, data)              \
    BOOST_PP_IF(                                                             \
        n                                                                    \
      , BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_1_Z                        \
      , BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_0_Z                        \
    )(z, n, data)
/**/

#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_Z(z, n, data)                   \
    BOOST_PP_IF(                                                             \
        n                                                                    \
      , BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_1_Z                             \
      , BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_0_Z                             \
    )(z, n, data)
/**/

#include <boost/preprocessor/repetition/repeat_from_to.hpp>

// Helper macro for BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS_AUX(nm, impl, r, is_m, c) \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        BOOST_PP_TUPLE_ELEM(2, 0, r)                                         \
      , BOOST_PP_TUPLE_ELEM(2, 1, r)                                         \
      , BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_Z                          \
      , (                                                                    \
            nm                                                               \
          , impl                                                             \
          , BOOST_PP_IF(                                                     \
                BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(nm)                \
              , 0                                                            \
              , is_m                                                         \
            )                                                                \
          , c                                                                \
        )                                                                    \
    )
/**/

// Helper macro for BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS_AUX(class_, base, range)       \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        BOOST_PP_TUPLE_ELEM(2, 0, range)                                     \
      , BOOST_PP_TUPLE_ELEM(2, 1, range)                                     \
      , BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_Z                               \
      , (class_, base)                                                       \
    )
/**/

#include <boost/parameter/aux_/preprocessor/impl/arity_range.hpp>

// Expands to the layer of forwarding functions for the function with the
// specified name, whose arguments determine the range of arities.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, impl, a, is_m, c)   \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS_AUX(                          \
        name, impl, BOOST_PARAMETER_ARITY_RANGE(a), is_m, c                  \
    )
/**/

// Expands to the layer of forwarding functions for the constructor in the
// specified class, whose arguments determine the range of arities.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS(class_, base, args)            \
    BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS_AUX(                               \
        class_, base, BOOST_PARAMETER_ARITY_RANGE(args)                      \
    )
/**/

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#include <boost/parameter/aux_/preprocessor/impl/parenthesized_type.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/cat.hpp>

// Expands to the default constructor, whose job is to pass an empty argument
// pack back to the delegate constructor of the base class.
#define BOOST_PARAMETER_DEFAULT_CONSTRUCTOR(z, n, seq)                       \
    inline                                                                   \
    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq)))()   \
      : BOOST_PARAMETER_PARENTHESIZED_TYPE(                                  \
            BOOST_PP_TUPLE_ELEM(                                             \
                2, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))              \
            )                                                                \
        )(BOOST_PP_CAT(constructor_parameters, __LINE__)()())                \
    {                                                                        \
    }
/**/

#include <boost/parameter/aux_/pp_impl/argument_pack.hpp>
#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>
#include <boost/preprocessor/control/expr_if.hpp>

// Expands to a 0-arity forwarding function, whose job is to pass an empty
// argument pack to the front-end implementation function.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_0_ARITY(z, n, seq)         \
    BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(                                  \
        BOOST_PP_TUPLE_ELEM(                                                 \
            4, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))                  \
        )                                                                    \
    )                                                                        \
    inline BOOST_PARAMETER_FUNCTION_RESULT_NAME(                             \
        BOOST_PP_TUPLE_ELEM(                                                 \
            4, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))                  \
        )                                                                    \
      , BOOST_PP_TUPLE_ELEM(                                                 \
            4, 3, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))                  \
        )                                                                    \
    )<                                                                       \
        ::boost::parameter::aux::argument_pack<                              \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(                                         \
                    4, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))          \
                )                                                            \
              , BOOST_PP_TUPLE_ELEM(                                         \
                    4, 3, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))          \
                )                                                            \
            )                                                                \
        >::type                                                              \
    >::type                                                                  \
    BOOST_PARAMETER_MEMBER_FUNCTION_NAME(                                    \
        BOOST_PP_TUPLE_ELEM(                                                 \
            4, 0, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))                  \
        )                                                                    \
    )() BOOST_PP_EXPR_IF(                                                    \
        BOOST_PP_TUPLE_ELEM(                                                 \
            4, 3, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))                  \
        )                                                                    \
      , const                                                                \
    )                                                                        \
    {                                                                        \
        return BOOST_PP_EXPR_IF(                                             \
            BOOST_PP_TUPLE_ELEM(                                             \
                4, 2, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))              \
            )                                                                \
          , this->                                                           \
        ) BOOST_PARAMETER_FUNCTION_IMPL_NAME(                                \
            BOOST_PP_TUPLE_ELEM(                                             \
                4, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))              \
            )                                                                \
          , BOOST_PP_TUPLE_ELEM(                                             \
                4, 3, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))              \
            )                                                                \
        )(                                                                   \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(                                         \
                    4, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))          \
                )                                                            \
              , BOOST_PP_TUPLE_ELEM(                                         \
                    4, 3, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))          \
                )                                                            \
            )()()                                                            \
        );                                                                   \
    }
/**/

#include <boost/parameter/aux_/preprocessor/binary_seq_to_args.hpp>
#include <boost/parameter/aux_/preprocessor/impl/function_forward_match.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/size.hpp>

// Expands to a constructor whose job is to consolidate its arguments into a
// pack for the delegate constructor of the base class to take in.  Each
// element in BOOST_PP_SEQ_TAIL(seq) determines the const-ness of the
// corresponding argument.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_R(r, seq)                       \
    template <                                                               \
        BOOST_PP_ENUM_PARAMS(                                                \
            BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq))                        \
          , typename ParameterArgumentType                                   \
        )                                                                    \
    >                                                                        \
    BOOST_PP_EXPR_IF(                                                        \
        BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq)), 1)         \
      , explicit                                                             \
    )                                                                        \
    inline BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_SEQ_HEAD(seq))(                \
        BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARGS(                           \
            BOOST_PP_SEQ_TAIL(seq), (ParameterArgumentType)(a)               \
        )                                                                    \
        BOOST_PARAMETER_FUNCTION_FORWARD_MATCH(                              \
            BOOST_PP_CAT(constructor_parameters, __LINE__)                   \
          , BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq))                        \
          , ParameterArgumentType                                            \
        )                                                                    \
    ) : BOOST_PARAMETER_PARENTHESIZED_TYPE(                                  \
            BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_SEQ_HEAD(seq))                \
        )(                                                                   \
            BOOST_PP_CAT(constructor_parameters, __LINE__)()(                \
                BOOST_PP_ENUM_PARAMS(                                        \
                    BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq)), a             \
                )                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
    }
/**/

// Expands to a forwarding function, whose job is to consolidate its arguments
// into a pack for the front-end implementation function to take in.  Each
// element in BOOST_PP_SEQ_TAIL(seq) determines the const-ness of the
// corresponding argument.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_R(r, seq)                  \
    template <                                                               \
        BOOST_PP_ENUM_PARAMS(                                                \
            BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq))                        \
          , typename ParameterArgumentType                                   \
        )                                                                    \
    >                                                                        \
    BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(                                  \
        BOOST_PP_TUPLE_ELEM(4, 1, BOOST_PP_SEQ_HEAD(seq))                    \
    )                                                                        \
    inline typename BOOST_PARAMETER_FUNCTION_RESULT_NAME(                    \
        BOOST_PP_TUPLE_ELEM(4, 1, BOOST_PP_SEQ_HEAD(seq))                    \
      , BOOST_PP_TUPLE_ELEM(4, 3, BOOST_PP_SEQ_HEAD(seq))                    \
    )<                                                                       \
        typename ::boost::parameter::aux::argument_pack<                     \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(4, 1, BOOST_PP_SEQ_HEAD(seq))            \
              , BOOST_PP_TUPLE_ELEM(4, 3, BOOST_PP_SEQ_HEAD(seq))            \
            )                                                                \
          , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARGS(                       \
                BOOST_PP_SEQ_TAIL(seq), (ParameterArgumentType)              \
            )                                                                \
        >::type                                                              \
    >::type                                                                  \
    BOOST_PARAMETER_MEMBER_FUNCTION_NAME(                                    \
        BOOST_PP_TUPLE_ELEM(4, 0, BOOST_PP_SEQ_HEAD(seq))                    \
    )(                                                                       \
        BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARGS(                           \
            BOOST_PP_SEQ_TAIL(seq), (ParameterArgumentType)(a)               \
        )                                                                    \
        BOOST_PARAMETER_FUNCTION_FORWARD_MATCH(                              \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(4, 1, BOOST_PP_SEQ_HEAD(seq))            \
              , BOOST_PP_TUPLE_ELEM(4, 3, BOOST_PP_SEQ_HEAD(seq))            \
            )                                                                \
          , BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq))                        \
          , ParameterArgumentType                                            \
        )                                                                    \
    ) BOOST_PP_EXPR_IF(                                                      \
        BOOST_PP_TUPLE_ELEM(4, 3, BOOST_PP_SEQ_HEAD(seq)), const             \
    )                                                                        \
    {                                                                        \
        return BOOST_PP_EXPR_IF(                                             \
            BOOST_PP_TUPLE_ELEM(4, 2, BOOST_PP_SEQ_HEAD(seq))                \
          , this->                                                           \
        ) BOOST_PARAMETER_FUNCTION_IMPL_NAME(                                \
            BOOST_PP_TUPLE_ELEM(4, 1, BOOST_PP_SEQ_HEAD(seq))                \
          , BOOST_PP_TUPLE_ELEM(4, 3, BOOST_PP_SEQ_HEAD(seq))                \
        )(                                                                   \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(4, 1, BOOST_PP_SEQ_HEAD(seq))            \
              , BOOST_PP_TUPLE_ELEM(4, 3, BOOST_PP_SEQ_HEAD(seq))            \
            )()(                                                             \
                BOOST_PP_ENUM_PARAMS(                                        \
                    BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq)), a             \
                )                                                            \
            )                                                                \
        );                                                                   \
    }
/**/

#include <boost/parameter/aux_/preprocessor/binary_seq_for_each.hpp>
#include <boost/preprocessor/control/if.hpp>

// Expands to all constructors that take in n arguments.  Enables
// BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS_AUX to use
// BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_Z within BOOST_PP_REPEAT_FROM_TO.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_Z(z, n, data)                   \
    BOOST_PP_IF(                                                             \
        n                                                                    \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_Z                         \
      , BOOST_PARAMETER_DEFAULT_CONSTRUCTOR                                  \
    )(z, n, (BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_R)(data))
/**/

// Expands to all forwarding functions that take in n arguments.  Enables
// BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS_AUX to use
// BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_Z within BOOST_PP_REPEAT_FROM_TO.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_Z(z, n, data)              \
    BOOST_PP_IF(                                                             \
        n                                                                    \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_Z                         \
      , BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_0_ARITY                    \
    )(z, n, (BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_R)(data))
/**/

#include <boost/preprocessor/repetition/repeat_from_to.hpp>

// Helper macro for BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS_AUX(class_, base, range)       \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        BOOST_PP_TUPLE_ELEM(2, 0, range)                                     \
      , BOOST_PP_TUPLE_ELEM(2, 1, range)                                     \
      , BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_Z                               \
      , (class_, base)                                                       \
    )
/**/

// Helper macro for BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS_AUX(nm, impl, r, is_m, c) \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        BOOST_PP_TUPLE_ELEM(2, 0, r)                                         \
      , BOOST_PP_TUPLE_ELEM(2, 1, r)                                         \
      , BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_Z                          \
      , (                                                                    \
            nm                                                               \
          , impl                                                             \
          , BOOST_PP_IF(                                                     \
                BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(impl)              \
              , 0                                                            \
              , is_m                                                         \
            )                                                                \
          , c                                                                \
        )                                                                    \
    )
/**/

#include <boost/parameter/aux_/preprocessor/impl/arity_range.hpp>

// Expands to the layer of forwarding functions for the constructor in the
// specified class, whose arguments determine the range of arities.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS(class_, base, args)            \
    BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS_AUX(                               \
        class_                                                               \
      , base                                                                 \
      , BOOST_PARAMETER_ARITY_RANGE(args)                                    \
    )
/**/

// Expands to the layer of forwarding functions for the function with the
// specified name, whose arguments determine the range of arities.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, impl, a, is_m, c)   \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS_AUX(                          \
        name                                                                 \
      , impl                                                                 \
      , BOOST_PARAMETER_ARITY_RANGE(a)                                       \
      , is_m                                                                 \
      , c                                                                    \
    )
/**/

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* forwarding_overloads.hpp
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
*/