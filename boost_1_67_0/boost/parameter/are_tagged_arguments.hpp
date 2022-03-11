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