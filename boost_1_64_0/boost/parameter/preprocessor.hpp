// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_PREPROCESSOR_060206_HPP
#define BOOST_PARAMETER_PREPROCESSOR_060206_HPP

#include <boost/parameter/aux_/preprocessor/impl/forwarding_overloads.hpp>
#include <boost/parameter/aux_/preprocessor/impl/specification.hpp>
#include <boost/preprocessor/cat.hpp>

// Helper macro for BOOST_PARAMETER_CONSTRUCTOR.
#define BOOST_PARAMETER_CONSTRUCTOR_AUX(class_, base, tag_namespace, args)   \
    BOOST_PARAMETER_SPECIFICATION(tag_namespace, ctor, args, 0)              \
        BOOST_PP_CAT(constructor_parameters, __LINE__);                      \
    BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS(class_, base, args)
/**/

#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>

// Defines the implementation function header.
#define BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name, is_const)                   \
    template <typename Args>                                                 \
    typename BOOST_PARAMETER_FUNCTION_RESULT_NAME(name, is_const)<           \
        Args                                                                 \
    >::type BOOST_PARAMETER_FUNCTION_IMPL_NAME(name, is_const)(              \
        Args const& args                                                     \
    )
/**/

#include <boost/parameter/aux_/preprocessor/impl/parenthesized_return_type.hpp>
#include <boost/parameter/config.hpp>

// Expands to the result metafunction and the parameters specialization.
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args, is_const)  \
    template <typename Args>                                                 \
    using BOOST_PARAMETER_FUNCTION_RESULT_NAME(name, is_const)               \
    = typename BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(result);            \
    BOOST_PARAMETER_SPECIFICATION(tag_ns, name, args, is_const)              \
        BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(name, is_const);
/**/
#else
#define BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args, is_const)  \
    template <typename Args>                                                 \
    struct BOOST_PARAMETER_FUNCTION_RESULT_NAME(name, is_const)              \
      : BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(result)                    \
    {                                                                        \
    };                                                                       \
    BOOST_PARAMETER_SPECIFICATION(tag_ns, name, args, is_const)              \
        BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(name, is_const);
/**/
#endif  // BOOST_PARAMETER_CAN_USE_MP11

// Helper macro for BOOST_PARAMETER_BASIC_FUNCTION.
#define BOOST_PARAMETER_BASIC_FUNCTION_AUX(result, name, tag_ns, args)       \
    BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args, 0)             \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name, 0);                             \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, name, args, 0, 0)       \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name, 0)
/**/

#include <boost/preprocessor/control/expr_if.hpp>

// Helper macro for BOOST_PARAMETER_BASIC_MEMBER_FUNCTION,
// BOOST_PARAMETER_BASIC_CONST_MEMBER_FUNCTION,
// BOOST_PARAMETER_BASIC_FUNCTION_CALL_OPERATOR, and
// BOOST_PARAMETER_BASIC_CONST_FUNCTION_CALL_OPERATOR.
#define BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(r, n, i, tag_ns, args, c)  \
    BOOST_PARAMETER_FUNCTION_HEAD(r, i, tag_ns, args, c)                     \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(n, i, args, 1, c)             \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(i, c) BOOST_PP_EXPR_IF(c, const)
/**/

#include <boost/parameter/aux_/preprocessor/impl/flatten.hpp>

// Expands to a Boost.Parameter-enabled constructor header.  All arguments are
// accessible via args and keywords only.
#define BOOST_PARAMETER_CONSTRUCTOR(class_, base, tag_namespace, args)       \
    BOOST_PARAMETER_CONSTRUCTOR_AUX(                                         \
        class_, base, tag_namespace                                          \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled function header.  All arguments are
// accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_FUNCTION(result, name, tag_namespace, args)    \
    BOOST_PARAMETER_BASIC_FUNCTION_AUX(                                      \
        result, name, tag_namespace                                          \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled member function header.  All arguments
// are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_MEMBER_FUNCTION(result, name, tag_ns, args)    \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        result, name, name, tag_ns                                           \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 0                     \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified member function
// header.  All arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_CONST_MEMBER_FUNCTION(r, name, tag_ns, args)   \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        r, name, name, tag_ns                                                \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 1                     \
    )
/**/

// Expands to a Boost.Parameter-enabled function call operator header.  All
// arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_FUNCTION_CALL_OPERATOR(result, tag_ns, args)   \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        result, operator(), operator, tag_ns                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 0                     \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified function call
// operator header.  All arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_CONST_FUNCTION_CALL_OPERATOR(r, tag_ns, args)  \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        r, operator(), operator, tag_ns                                      \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 1                     \
    )
/**/

#include <boost/parameter/aux_/preprocessor/impl/function_dispatch_layer.hpp>

// Helper macro for BOOST_PARAMETER_FUNCTION.
#define BOOST_PARAMETER_FUNCTION_AUX(result, name, tag_ns, args)             \
    BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args, 0)             \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name, 0);                             \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, name, args, 0, 0)       \
    BOOST_PARAMETER_FUNCTION_DISPATCH_LAYER(                                 \
        1, (name, BOOST_PARAMETER_FUNCTION_SPLIT_ARGS(args), 0, 0, tag_ns)   \
    )
/**/

// Expands to a Boost.Parameter-enabled function header.  All arguments are
// accessible via args and keywords, as well as by name.
#define BOOST_PARAMETER_FUNCTION(result, name, tag_namespace, args)          \
    BOOST_PARAMETER_FUNCTION_AUX(                                            \
        result, name, tag_namespace                                          \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

#include <boost/preprocessor/control/if.hpp>

// Helper macro for BOOST_PARAMETER_MEMBER_FUNCTION
// BOOST_PARAMETER_CONST_MEMBER_FUNCTION,
// BOOST_PARAMETER_FUNCTION_CALL_OPERATOR, and
// BOOST_PARAMETER_CONST_FUNCTION_CALL_OPERATOR.
#define BOOST_PARAMETER_MEMBER_FUNCTION_AUX(r, name, impl, tag_ns, c, args)  \
    BOOST_PARAMETER_FUNCTION_HEAD(r, impl, tag_ns, args, c)                  \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, impl, args, 1, c)       \
    BOOST_PARAMETER_FUNCTION_DISPATCH_LAYER(                                 \
        0, (                                                                 \
            impl                                                             \
          , BOOST_PARAMETER_FUNCTION_SPLIT_ARGS(args)                        \
          , BOOST_PP_IF(                                                     \
                BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(impl)              \
              , 0                                                            \
              , 1                                                            \
            )                                                                \
          , c                                                                \
          , tag_ns                                                           \
        )                                                                    \
    )
/**/

// Expands to a Boost.Parameter-enabled member function header.  All
// arguments are accessible via args and keywords, as well as by name.
#define BOOST_PARAMETER_MEMBER_FUNCTION(result, name, tag_ns, args)          \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, name, name, tag_ns, 0                                        \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified member function
// header.  All arguments are accessible via args and keywords, as well as
// by name.
#define BOOST_PARAMETER_CONST_MEMBER_FUNCTION(result, name, tag_ns, args)    \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, name, name, tag_ns, 1                                        \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled function call operator header.  All
// arguments are accessible via args and keywords, as well as by name.
#define BOOST_PARAMETER_FUNCTION_CALL_OPERATOR(result, tag_ns, args)         \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, operator(), operator, tag_ns, 0                              \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified function call operator
// header.  All arguments are accessible via args and keywords, as well as
// by name.
#define BOOST_PARAMETER_CONST_FUNCTION_CALL_OPERATOR(result, tag_ns, args)   \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, operator(), operator, tag_ns, 1                              \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

#endif  // include guard


/* preprocessor.hpp
7YEwaU6BhtbNRDe1ra+OZ5omjZkmsnQhzvOy0TVjunDkzSs6XVDpm7hrW//vRroFfTr8LOvixF6yUpJ9lGqtG9Gckmhsa9lY9+xvXZ8m1jY/Rv69sMK8Hr9zMc9A5F9n61o0cUf2XKJJ8dLbRUgrrROKKl3ta815sdRuRjlY00N1VZRVqe3k8if14VBfXea+ZIE3NsbcyndV9aAAFXhCdlFu5vgcDImKcwqRpqrzpifRJlNV+UcY1ruIRRm7lvzqOLartD6e49L3sw4kfqwzd3vbVDcqtNed2WxTM0R6qPdN95ilYxvt6JxCpU3NIfqWqnQhLKlfw+dBHHRgk/zdjbmZ5b6AGVrB/Z4A21cl9xhx30VR+qgpdPqz+gyapcTTQiU7wnPWnilkFWOezU0NWcvggvRybe6x95JVnP+JviWKTXbOZMt92+J+60PEN1M7H3b0SpSJ6+BuUN8PjDgsto/76c04346S/xStEf5eCncN3GApr6bGVu/+gtGK+yAmN6/qX0dw//rXxtDHCV/p59/6qc6+zqMg3gRlmhGu2KMTTXxScOp+i+BJ1G1RiDdPOqzSmOJc0R4sJNpUrbl67bkIK0LcTZYlbOHz5Ie14JZ9yWKdKPm70cYGCfv9ag32M5rnP0Trz5b0NzPPjguBnyKdXucxJBt5l8r71a7W8w6NZqUq7wAYE9HiQ+VeUuK5HBbfx13sfvT2F/m1h50KUq7TT/ieOMXe0QvpOViU4zUNaqZH2VYOaGHoYiYz3AfXOQG6QVyyLsaOmUBKsNgbsWegL9HfpqXhjUIPCI/nMMR4yjBj6rIr6MX+Asyl5WdL+24fIv8EZVmVeVtQqjCkTc/UmrFeryP/W6GLIO0CuBS4a+Ar5ZFor/9BtBNttiaRw8ogf5y2h1azASRvCqwax1e/bx0vjwtZR/KeBugC76ELyzji3PlGPo7jPYVj4fZBUZUiH6sacOqLOzhfpFLoUbpPWZ1fgpb36cl3LyvyyBI2aYjHBlw3zpH/TdZzBkX+u3/Q/ftK/LnZY4rQf+V+dRD5X681Q17odTw51lhjPR5uLTL2Rjy/ExN4D5++Z/a6HwLf6wD9SHcFy3OqrAdLflW2NPLrNu6jTOF97aU/mPmF9nJssdxHUZ7new/RF9NevkFqG4QwbXdgINSqMcxi8h+BcVGQ0Nc6PrfqYeAD1LepXpvJ+vH6xnCklZHmzszQifuZyT9WpblA9C5t/Utha1qCXrebTdRjLoSn6HNyfW5Lfm0C9n189Tl7/ij6nPQ8mJ/vReDyuTq5F7gs+6H5LJGqtBaMd1AHPT/WvK9mtnctWxuy5DGDHm9rZHypkMW4ajKrIC+9uEDffEzXwUt1WRyXJPqXM4g3V13eHMocb53D5Djk+dbsNobsw7meDINbD9ndlUL2whxPXmYWWzXL3IIo4w2JfrB2hbqOIDz/+/u6kX89pe0Drzjfpg10HQKZ9TNrIl10vk2Y6nwbPt+B7NGemIDzGT3U8xnq/W9ynRvW1tDfHVwGb4d7KBF5JPRXdfMEZs+kdeqZos7MINpkdV5z2qv4Rgmd309+CWSbVHpj3oDpNss2wpfnTvl5lFd657VziflumgeHW6zbmJ9s6SUFWtOrB9KSaMN4HxTzIsSmyH8p7XjPaRf9jDzR572F/CJJtnixd0q6tUc6M7c10faAPatDtHOJVj9etghzFpjZ0HXAslxJtBcFrFtWnSXyM8LGsxS2pb61aW/oLwPgBo4E6mPnUll/OCwks2i88iyoeD0Ooh3oiieZmRchdkNMPbVGLq/ywzqM5TEKLB5doKdJfYGFhn5cUv9M1MvHyO87bhtc2tMn8YzeXAPY+Fg=
*/