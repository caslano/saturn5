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
uyxSwErylESiU6XgWtPk/LoQ+MgM7HYnMJjswswWXLTh/WD6dnQ5hffd8bg7nH6E0WvoDj/SYu8Gwx6aniOxCNhtGDGBxCPgy9DjzE1oPt51sLNz0IKR791BGAXXHF1JCTojWZbc58t4SWrxuP8VbpAtfJqRlYFQ/8J9x4tdBq+EdHmwvzgpDiFseSzi/hWN5YO7QsYz60oIO+T7i13F0BNnwZyvInKekDaVl02GF+PBcPoavS8h7rI59xmcdz9Yp+N+b2Kd9Ydvpm/h+ctn2WT34mI8+mBNR+/6Q5pXkzvMR6lQOotFkeUEyMSfO7Sd30wm1ugdHMOzdvY+HFnn/fPR+GM+NBj+3j0b9Kzu+M2kOqp4WTE8/ZAPTvrj3/tjqz8elwidvs0HzrqT6c6Pzs6OkLbkDnq7LyQ4CzuCVsq8JN18+oIskwRKlXuoyiPwA8D5INptV8aXbBlEd+UJ7l/bHsdYEF3FS+ZLUQfgRMzFeY5RoBYk8CW7leVpwaJrdOuISdxxuDlWMujYvh9I3GG4h23kFeXF3blUYMPLs7NEI1GM2QIRLEfeWty1pEVR0EomSBnKyH/CcDTst+Hd+LeXbRhOz84P9e0F/EB+fNlBSO5LFRCtr9HsZWHAl96SBkbnVoyDL57D3LOv
*/