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
XeT5M/mmsVXS7Sv9qpsTjgvI3TVJ4CgwAzwO7AgeDw4GR4PDwUpwJDhG5g9jwZPBceCZ4Hh5D54EVoEngWvByeAPJf5N4Cngg2A++Ah4Gvg4OAd8GzwL/BRcCH4FFoNByrxIxuslYAa4FMwBy8Fu4DLwcLAC7ANWyni9V38zgRfC1xxwt9T/e6L/VoIh8ELRLxeBA8CLRQ/eJXpwNTgDvFT0ymVgIXg5eAG4Blwl9KvBa2U8ug7EBW6ScegW8GnwVvBF8Efgb8H14E6J/zp4G/hn8HYZn+4APwbvBP8ObgK/UPQiv0FcZ7lbUdr7mDAf1W+y3Ek7BQyBp4jcTBe5OR08DJwF9gRngP3AmeAA8R8IngEeB84GJ4JzwVngPLFPzRf9chZ4PlgIXgcWgfeAC8AHwRLwV+Bi8CWwFHwXLAM/BJeB+8EK0JGDc8B0sAbMBi8Ce4F14ABwNTgcvBLMB68Gi8BrwWXgDeA5En4VeCv4fXA9eA+4AdwK3gg+Bm4EnwDvBLeDm8BXwLvA18DNYHGKv7s6wvdyfLd3cjyMexG3G+fcxzGkCXdy/C/cx1E63t+dHHIfB3effHd3chj3cTT5Lo51uLrYuzgafQ+H9w6Od1f/b93Doe6jAaeO/9+6j2Pd+IN3J0fK2cgKBsEvcUcx2OTjVuDuxu3COQNtP1wh7hrcw7g9uJSj8cfNxK3AbcLtwO3DdcOQOBVXg1uP247biwv1Iw5ucr9D91wc+h36Hfod+h36Hfod+h36Hfr9//xScIu+w/P/ly1cvkhdABAINOsOgGxW6n3Thfe5Ex27t5Oyc3ZSdaA7/rWk3Sfav2BhRe1y7CTq7oDWGPKGuWcPBO3nTIa+NM9GJ/ryRWWLfZ4pSVzPelXKYFvvL7Tmnto2HfzvqY1/XhX5efa/j5C7kjtLQur+bfLK0/VUm25UE1UU15YTXcoE+iiTWucteWUl2/ct5+u8hJ8+9vfkN4KX+U3gpWdfQnw+yvrpbVK3FjgX+2PorAzXrXppwfjp0yYVnDF26qyJBRzzFhCZOQYa6riUR/vZzJ6yPxtKVPbcqDOwnLQ7StpmWe9PiS3rAGjrbGVlL1Btib+yEt+zD7qsON49EHWeem1vYr2iz48lP6nrMKnrVjl/3rExJgv2Iv5aqStyXVzhip1H7tw9pjcr2nfgX7Ksx3bjz9Z1Er+E+xNP/JcT2sa+vyeOPGdK3FYqbodgu8C/7Ht+jPgD1Wal5chYJP4KFX8I/bydXu+9R8VZJ8/BwE8VTVDX8QMVPkKtiR+k0lxIhSJ7S25R4ZcHR/F/v2DQ3Leoefc9leZdgeHuWU46n8yYcyx6yFr8H6l0Lw0OpyVvhl93B6azjiAVs04SsaAh9DLSIFdqk6XS2Wvsf8yUdAYpmhmk0DpuvNxwvZYVG3uDL1Q0d8CtjjG8kXNO1Br01A7wHuf83Q5Mx7XHhXAZuExcB1yqpvGzb6NFxs9UXmrBvF0PWXR8mkU3uX1glyx4fwYXxD2N65ONzHwlfcDV7QWLqkqkr8/p6NDCFntfl7hRba730d6hwu4zwpZomfulCivWfP2Zes4I5MDXFg5lKNZlB2aoMX3lPKcweuwmDemf4fwa5K2rP5y6dZS6mXxaJ+eij0qCB+Aw8ChHL37t5VPZ8rIaf3wiru6XHZT+ZKJj7KH+kQp/IljCbGd74DO7rpQ0csK6gR9FUTqLfVELa9j6HZHdDYq2Cg63NNtG9idTnwNO+E2cJ/QmayBnO31dnVE57EC4z9na7EkVdqs++3OCel4aDPHVcWGQfffEuSVL+lFBeVl1TbXem7VZlecfwfmBFtTuEd0Pb/7G8e9Cy7fQe2XuU7Q=
*/