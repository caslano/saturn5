// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_COMPOSE_HPP
#define BOOST_PARAMETER_COMPOSE_HPP

#include <boost/parameter/aux_/arg_list.hpp>

namespace boost { namespace parameter {

    inline BOOST_CONSTEXPR ::boost::parameter::aux::empty_arg_list compose()
    {
        return ::boost::parameter::aux::empty_arg_list();
    }
}} // namespace boost::parameter

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    template <typename ...TaggedArgs>
    struct compose_arg_list
    {
        using type = ::boost::parameter::aux::flat_like_arg_list<
            ::boost::parameter::aux::flat_like_arg_tuple<
                typename TaggedArgs::base_type::key_type
              , typename TaggedArgs::base_type
            >...
        >;
    };
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
    template <typename TaggedArg0, typename ...TaggedArgs>
    struct compose_arg_list;

    template <typename TaggedArg0>
    struct compose_arg_list<TaggedArg0>
    {
        typedef ::boost::parameter::aux::arg_list<TaggedArg0> type;
    };

    template <typename TaggedArg0, typename ...TaggedArgs>
    struct compose_arg_list
    {
        typedef ::boost::parameter::aux::arg_list<
            TaggedArg0
          , typename ::boost::parameter::aux
            ::compose_arg_list<TaggedArgs...>::type
        > type;
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#include <boost/parameter/are_tagged_arguments.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace parameter { namespace result_of {

    template <typename ...TaggedArgs>
    struct compose
      : ::boost::lazy_enable_if<
            ::boost::parameter::are_tagged_arguments<TaggedArgs...>
          , ::boost::parameter::aux::compose_arg_list<TaggedArgs...>
        >
    {
    };

    template <>
    struct compose<>
    {
        typedef ::boost::parameter::aux::empty_arg_list type;
    };
}}} // namespace boost::parameter::result_of

namespace boost { namespace parameter {

    template <typename TaggedArg0, typename ...TaggedArgs>
    inline BOOST_CONSTEXPR typename ::boost::parameter::result_of
    ::compose<TaggedArg0,TaggedArgs...>::type
        compose(TaggedArg0 const& arg0, TaggedArgs const&... args)
    {
        return typename ::boost::parameter::aux
        ::compose_arg_list<TaggedArg0,TaggedArgs...>::type(
            ::boost::parameter::aux::value_type_is_not_void()
          , arg0
          , args...
        );
    }
}} // namespace boost::parameter

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#define BOOST_PARAMETER_compose_arg_list_type_suffix(z, n, suffix) suffix

#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_compose_arg_list_type_prefix(z, n, prefix)           \
    ::boost::parameter::aux::arg_list<BOOST_PP_CAT(prefix, n)
/**/

#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define BOOST_PARAMETER_compose_arg_list_type(z, n, prefix)                  \
    BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                         \
        n, BOOST_PARAMETER_compose_arg_list_type_prefix, prefix              \
    ) BOOST_PP_CAT(BOOST_PP_REPEAT_, z)(                                     \
        n, BOOST_PARAMETER_compose_arg_list_type_suffix, >                   \
    )
/**/

#include <boost/parameter/aux_/void.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

#if defined(BOOST_NO_SFINAE)
#define BOOST_PARAMETER_compose_arg_list_function_overload(z, n, prefix)     \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename prefix)>                 \
    inline BOOST_CONSTEXPR                                                   \
    BOOST_PARAMETER_compose_arg_list_type(z, n, prefix)                      \
        compose(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, prefix, const& a))       \
    {                                                                        \
        return BOOST_PARAMETER_compose_arg_list_type(z, n, prefix)(          \
            BOOST_PP_ENUM_PARAMS_Z(z, n, a)                                  \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(                                 \
                z                                                            \
              , BOOST_PP_SUB(BOOST_PARAMETER_COMPOSE_MAX_ARITY, n)           \
              , ::boost::parameter::aux::void_reference() BOOST_PP_INTERCEPT \
            )                                                                \
        );                                                                   \
    }
/**/
#else   // !defined(BOOST_NO_SFINAE)
#include <boost/parameter/are_tagged_arguments.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace parameter { namespace result_of {

    template <
        BOOST_PP_ENUM_BINARY_PARAMS(
            BOOST_PP_INC(BOOST_PARAMETER_COMPOSE_MAX_ARITY)
          , typename TaggedArg
          , = void BOOST_PP_INTERCEPT
        )
    >
    struct compose;

    template <>
    struct compose<>
    {
        typedef ::boost::parameter::aux::empty_arg_list type;
    };
}}} // namespace boost::parameter::result_of

#define BOOST_PARAMETER_compose_arg_list_function_overload(z, n, prefix)     \
namespace boost { namespace parameter { namespace result_of {                \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename prefix)>                 \
    struct compose<BOOST_PP_ENUM_PARAMS_Z(z, n, prefix)>                     \
      : ::boost::enable_if<                                                  \
            ::boost::parameter                                               \
            ::are_tagged_arguments<BOOST_PP_ENUM_PARAMS_Z(z, n, prefix)>     \
          , BOOST_PARAMETER_compose_arg_list_type(z, n, prefix)              \
        >                                                                    \
    {                                                                        \
    };                                                                       \
}}}                                                                          \
namespace boost { namespace parameter {                                      \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename prefix)>                 \
    inline BOOST_CONSTEXPR typename ::boost::parameter::result_of            \
    ::compose<BOOST_PP_ENUM_PARAMS_Z(z, n, prefix)>::type                    \
        compose(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, prefix, const& a))       \
    {                                                                        \
        return BOOST_PARAMETER_compose_arg_list_type(z, n, prefix)(          \
            BOOST_PP_ENUM_PARAMS_Z(z, n, a)                                  \
            BOOST_PP_ENUM_TRAILING_PARAMS_Z(                                 \
                z                                                            \
              , BOOST_PP_SUB(BOOST_PARAMETER_COMPOSE_MAX_ARITY, n)           \
              , ::boost::parameter::aux::void_reference() BOOST_PP_INTERCEPT \
            )                                                                \
        );                                                                   \
    }                                                                        \
}}
/**/
#endif  // BOOST_NO_SFINAE

#include <boost/preprocessor/repetition/repeat_from_to.hpp>

BOOST_PP_REPEAT_FROM_TO(
    1
  , BOOST_PP_INC(BOOST_PARAMETER_COMPOSE_MAX_ARITY)
  , BOOST_PARAMETER_compose_arg_list_function_overload
  , TaggedArg
)

#undef BOOST_PARAMETER_compose_arg_list_function_overload
#undef BOOST_PARAMETER_compose_arg_list_type
#undef BOOST_PARAMETER_compose_arg_list_type_prefix
#undef BOOST_PARAMETER_compose_arg_list_type_suffix

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* compose.hpp
Vmk/L1HT+r5bKv79pVJG4SX54qfyVXbbKSofzhrIib6XpFuKnJcjmZXhbu3E3MjD29ISGFsZvuqigKZ0+VsWiv3WXKPitrWvKZD6yv1L2LPV+XKgf3kiT+GBISfGooJOEikbV+j0rWui61JO/yqooBNzz53fu95JQ7dpDyUTFZWAvV9d02CbNrhmhjzwIw9PHTdJHd2E20t75XrqWFNQVl1QsrxoQXlJsaWt7PfZN7Lc3nYY5N771lbRsl80gjcij2M8ZaSbxvC+h/SxCYr2raTelGwE7tc07s5gC85uaWkrO2lb+6w+B3+qCs8LZPD/4cS4Sr4VXKb8b006gv8H4ybgpuLOxi3BVeAuwNXhrsX9AHczbj3udtxm3H24rbhHcI/jnsFtx72B+wiXHSRt3FRcPu7MYCp79VoFbubvB4L2szepj/d+Hg4PjfSx265V3/PkfGX6nHo+G610hFXPkJ7n/NRK0rOeGaxp2+p7HMv1mfMPqLCZgTS4OBzr6HhK63zruhu53Ia9+ggaLy217nl3nOjBs3nf2pE8H4XraRk/UmLWI6QB6PrryNN4HiLPmaxXSAn/fdTUaUOGBcTvwLXab6jrtzfiN8T1eyPiN9j1eyzil+f6rdd+g4e7fpURPx13fsRvkOs3JeI30PWbGPHTeYzRfoNGun7HRfxGuH7DIn66LAMjfpoH/SJ+mge9I36aBz0ifroeh0X8dD06R/x0PTpE/HQ9Wmq/gboewYifrsfn12g/XY/6iJ+ux7sRP12P30f8dD1+HfGLtGXET9fjJxE/XY+NEb+8QBPGWrlTiv6kzwWW835VH1Pjbz+R2aKcaH2+M1Wf7ax+nWXM2oPh39CVzoRSBq5F5UWLq32NWeE0zDFLxbXomxhafhVVZYa+qVfhbXyPDfHHNFUGYx2oGFkVXQSHq0OfY3ggQ5rPMVvFj8xZezVizkra1jlGvazTATSW0F65lrIuc46Pdo4P9jnHIA3dBosz9Noea3uZtLmqbVVuFt1voaVtSdiq+3M9POvdRJ65bU49otYUqPLgOkp5pb+IH+Xy8Htfun1Ol2fhN5wO9w6f/M5b679/QJuwf4xS4e2axat4/WOypHijJHQDbjz9Iz+KB9I1mFbFe/fpBK5TcU5hJhRnbYXUM0fPo1iEW8YZwUyWnRVoJXZ51PF6MBf4kjbbw8S0D7KTPKFly+QOLVPSkrqnFgPt2wb0Wf59Ca+UtTDixzPxfMwNbHzsbupoS7nNOWqlKJvVQeoIruK/JchV6HqTp+FFiW01L4v0+q+Oik7df005JB6pHckpFgY/xT/6zO50iTNYhRUEs+HZ1BD05HF0eD3TV2ktQroPbs6QOZTQ9eH5Q1xaqO4jl+a5UDTNVMKXZSqaN+PRVEJzLy6tdd0L8fK6MULzTDyaR3k+poOi2eTS9JN5X3eh+QSa/vglH488dGyZlNyDe3tbtRVZkPWWnnVRT1H+Y4kzAPc7/s4DB+IG4QbjdmRKPHG/V88Ny056lOwUybNex23qH9YnaL3Dj3DceTlOJ4ySk8UlNXnmIeW+3rfCaTT9fUvf5yplTJVIbXHfc8YkWxlryisWF1TXVFT5K2NuM8vo6rAzs2LLeIGjxy1lZNZUtMyvDm9k+eKN6weyYseZlZRvjKV8YgbBCuLvvXpMI8to8tC8e+/ujmFi9SDj9YWUsdBSRlZy1laV1ZzPjWLq7ia/NoDCZpbV5efU7Og7CFvhLqKsdTFlVd0mLJE+y1jXzDKKTOrGbi+R0nEXU8a1MWUUO2x1bPn0nfMqTlvqaR9X1zazzK4M3N8plq91lHlrbJmLSxYV1ZbXFLiH9S/wa+va2siyevvUNCk=
*/