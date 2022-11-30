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
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
*/