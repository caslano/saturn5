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