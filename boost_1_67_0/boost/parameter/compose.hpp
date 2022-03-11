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