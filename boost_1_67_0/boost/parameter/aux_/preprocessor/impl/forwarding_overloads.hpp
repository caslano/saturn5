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