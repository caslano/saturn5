// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// #include guards intentionally disabled.
// #ifndef BOOST_DETAIL_FUNCTION_N_DWA2006514_HPP
// # define BOOST_DETAIL_FUNCTION_N_DWA2006514_HPP

#include <boost/mpl/void.hpp>
#include <boost/mpl/apply.hpp>

#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace detail {

# define BOOST_DETAIL_default_arg(z, n, _)                                      \
    typedef mpl::void_ BOOST_PP_CAT(arg, n);

# define BOOST_DETAIL_function_arg(z, n, _)                                     \
    typedef typename remove_reference<                                          \
        typename add_const< BOOST_PP_CAT(A, n) >::type                          \
    >::type BOOST_PP_CAT(arg, n);

#define BOOST_DETAIL_cat_arg_counts(s, state, n)                                \
    BOOST_PP_IF(                                                                \
        n                                                                       \
      , BOOST_PP_CAT(state, BOOST_PP_CAT(_, n))                                 \
      , state                                                                   \
    )                                                                           \
    /**/

#define function_name                                                           \
    BOOST_PP_SEQ_FOLD_LEFT(                                                     \
        BOOST_DETAIL_cat_arg_counts                                             \
      , BOOST_PP_CAT(function, BOOST_PP_SEQ_HEAD(args))                         \
      , BOOST_PP_SEQ_TAIL(args)(0)                                              \
    )                                                                           \
    /**/

template<typename F>
struct function_name
{
    BOOST_PP_REPEAT(
        BOOST_MPL_LIMIT_METAFUNCTION_ARITY
      , BOOST_DETAIL_default_arg
      , ~
    )

    template<typename Signature>
    struct result {};

#define BOOST_DETAIL_function_result(r, _, n)                                   \
    template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(n, typename A)>        \
    struct result<This(BOOST_PP_ENUM_PARAMS(n, A))>                             \
    {                                                                           \
        BOOST_PP_REPEAT(n, BOOST_DETAIL_function_arg, ~)                        \
        typedef                                                                 \
            typename BOOST_PP_CAT(mpl::apply, BOOST_MPL_LIMIT_METAFUNCTION_ARITY)<\
                F                                                               \
                BOOST_PP_ENUM_TRAILING_PARAMS(                                  \
                    BOOST_MPL_LIMIT_METAFUNCTION_ARITY                          \
                  , arg                                                         \
                )                                                               \
            >::type                                                             \
        impl;                                                                   \
        typedef typename impl::result_type type;                                \
    };                                                                          \
    /**/

    BOOST_PP_SEQ_FOR_EACH(BOOST_DETAIL_function_result, _, args)

# define arg_type(r, _, i, is_const)                                            \
    BOOST_PP_COMMA_IF(i) BOOST_PP_CAT(A, i) BOOST_PP_CAT(const_if, is_const) &

# define result_(r, n, constness)                                               \
    typename result<                                                            \
        function_name(                                                          \
            BOOST_PP_SEQ_FOR_EACH_I_R(r, arg_type, ~, constness)                \
        )                                                                       \
    >                                                                           \
    /**/

# define param(r, _, i, is_const) BOOST_PP_COMMA_IF(i)                          \
    BOOST_PP_CAT(A, i) BOOST_PP_CAT(const_if, is_const) & BOOST_PP_CAT(x, i)

# define param_list(r, n, constness)                                            \
    BOOST_PP_SEQ_FOR_EACH_I_R(r, param, ~, constness)

# define call_operator(r, constness)                                            \
    template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(constness), typename A)>    \
        result_(r, BOOST_PP_SEQ_SIZE(constness), constness)::type               \
    operator ()( param_list(r, BOOST_PP_SEQ_SIZE(constness), constness) ) const \
    {                                                                           \
        typedef result_(r, BOOST_PP_SEQ_SIZE(constness), constness)::impl impl; \
        return impl()(BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(constness), x));   \
    }                                                                           \
    /**/

# define const_if0
# define const_if1 const

# define bits(z, n, _) ((0)(1))

# define gen_operator(r, _, n)                                                  \
    BOOST_PP_SEQ_FOR_EACH_PRODUCT_R(                                            \
        r                                                                       \
      , call_operator                                                           \
      , BOOST_PP_REPEAT(n, bits, ~)                                             \
    )                                                                           \
    /**/

    BOOST_PP_SEQ_FOR_EACH(
        gen_operator
      , ~
      , args
    )

# undef bits
# undef const_if1
# undef const_if0
# undef call_operator
# undef param_list
# undef param
# undef result_
# undef default_
# undef arg_type
# undef gen_operator
# undef function_name

# undef args
};

}} // namespace boost::detail

//#endif // BOOST_DETAIL_FUNCTION_N_DWA2006514_HPP

/* function_n.hpp
27OdfUqVLerdF3kMQnK066gqlw0Wd3s45tqhKqaP2U16rNE+3v96px4CP/H+Th5tDPXy/jc7cau+l/MmaE7ltO2L1IFQCDfPfGa2BmV9HeVSRScupg1/5jiXVZH3S8Un5Laspw7gZoj/0Kd6LlcMZUDkRKRCar5sPKd63hTR8+Y51fPmEvK82TLA8+YCdN5ZwBxlSpJZi6qGotw63NG3J7scrHl1nyLNMVqP5cFElHag6eKsCsYvPwNfINWbrCF+y245HP5UGBYO1ptffvllJ/s98h3WUGUMDq1/B7dnGiaPGCms8A/vBSDY5B8xEmqIfBEDwKlxPwPAAEfZjwjuFhvVxlmPvctpqmWv/UfPyS1N/jjUasmxtdX0rAh8A4lbAxiRGgziAx5nuQ0SlkEJwUAvlgVlYgKHR1fGGr2Kor2CFrn637mAltKjI9H7qnHxAcXR26umPJ/GjdRALN1USmeR9/Bb/MVYzUYdHxgBg7ZR7xvV9Ax9aa5tf00nenegDnl0e6xDUrFD0PvWf6HY5oapMB2b/XRtoutqvHoy3O5igAZjgJjBfce9UsURqeKEVHFcquiAaeFJYLcjnSNV9LL3SdbdSSq2LwmaX6ZhB3Ej+LiDfRmLOXsAYzoc7LlYzFcQw7Z4MPdu6Yq5c8yCOJyh7Fkcfhxv7rnYhE9Ga868QmhetwDyrNt9pyoLxhNZbvcclFanombOaTtt
*/