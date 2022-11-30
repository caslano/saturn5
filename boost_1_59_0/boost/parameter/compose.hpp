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
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
*/