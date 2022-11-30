// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_HPP
#define BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter {

    template <typename TaggedArg0, typename ...TaggedArgs>
    struct are_tagged_arguments;
}} // namespace boost::parameter

#include <boost/parameter/aux_/is_tagged_argument.hpp>

namespace boost { namespace parameter {

    template <typename TaggedArg0>
    struct are_tagged_arguments<TaggedArg0>
      : ::boost::parameter::aux::is_tagged_argument<TaggedArg0>
    {
    };
}} // namespace boost::parameter

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace parameter {

    template <typename TaggedArg0, typename ...TaggedArgs>
    struct are_tagged_arguments
      : ::boost::mpl::if_<
            ::boost::parameter::aux::is_tagged_argument<TaggedArg0>
          , ::boost::parameter::are_tagged_arguments<TaggedArgs...>
          , ::boost::mpl::false_
        >::type
    {
    };
}} // namespace boost::parameter

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#define BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_END_Z(z, n, false_t) , false_t>
/**/

#include <boost/parameter/aux_/is_tagged_argument.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_BEGIN_Z(z, n, prefix)           \
    ::boost::mpl::eval_if<                                                   \
        ::boost::parameter::aux::is_tagged_argument<BOOST_PP_CAT(prefix, n)>,
/**/

#include <boost/parameter/aux_/void.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

#define BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_OVERLOADS_Z(z, n, prefix)       \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename prefix)>                 \
    struct are_tagged_arguments<                                             \
        BOOST_PP_ENUM_PARAMS_Z(z, n, prefix)                                 \
        BOOST_PP_ENUM_TRAILING_PARAMS_Z(                                     \
            z                                                                \
          , BOOST_PP_SUB(BOOST_PARAMETER_COMPOSE_MAX_ARITY, n)               \
          , ::boost::parameter::void_ BOOST_PP_INTERCEPT                     \
        )                                                                    \
    > : BOOST_PP_CAT(BOOST_PP_REPEAT_, z)(                                   \
            n                                                                \
          , BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_BEGIN_Z                     \
          , prefix                                                           \
        )                                                                    \
        ::boost::mpl::true_                                                  \
        BOOST_PP_CAT(BOOST_PP_REPEAT_, z)(                                   \
            n                                                                \
          , BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_END_Z                       \
          , ::boost::mpl::false_                                             \
        )::type                                                              \
    {                                                                        \
    };
/**/

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace boost { namespace parameter {

    template <
        BOOST_PP_ENUM_BINARY_PARAMS(
            BOOST_PP_INC(BOOST_PARAMETER_COMPOSE_MAX_ARITY)
          , typename TaggedArg
          , = ::boost::parameter::void_ BOOST_PP_INTERCEPT
        )
    >
    struct are_tagged_arguments;
}} // namespace boost::parameter

#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost { namespace parameter {

    BOOST_PP_REPEAT_FROM_TO(
        1
      , BOOST_PP_INC(BOOST_PARAMETER_COMPOSE_MAX_ARITY)
      , BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_OVERLOADS_Z
      , TaggedArg
    )
}} // namespace boost::parameter

#undef BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_OVERLOADS_Z
#undef BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_BEGIN_Z
#undef BOOST_PARAMETER_ARE_TAGGED_ARGUMENTS_END_Z

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* are_tagged_arguments.hpp
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
*/