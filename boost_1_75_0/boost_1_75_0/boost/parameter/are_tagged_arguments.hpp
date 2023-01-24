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
z/3KRXiEuPxvDFeam98wWfn3Trkk5y/WA25l27E52GxZC5nxWbNM4G6IRWZekzSNEFBhrOl+PCxA7n1wgmUPET2a+40QJ7hojCS57z71WX26wZUdn52WVlhCUNfewreutNKA8TyQy/Q8Gd2fDqnHf8SxLY4qBRFRaKnrofdpTUZ97DfI5HWZ4k32JHZeDWIn1LClg+/JjeGeCsGwat0t3yyHXlKyRK6JH/Dur8v+Dxx3WEqznHgDzvVX/XWhNz3POGNbVMBtQpVgkVEnCXbT22RR0SR8Eqeb4e79p8alGce+3dN+YfAuz2OJM5+5uzvvcMHxuVDnx8lpW05qrbTA5VP7Jv2CB7O/eb+on+DD9oMkWyygg5vFzZaNDRae9qGgYVxjC5PWaZDZvTjbfJ3azrvnNqhg8GXAvEBdoUx0ofsCuONWoIJUSmL1n6wZYAbIOZTtpp59q3aIjLz9UcW6cPWz4bz6iTQ47exbgUOk77DCbkmfWXMp2iaNaWFc//I2oJo2+gjSOUJp2Fos9loX+u7eeclKdK2Vc62k78rY8+VKM8mI93XmkHOnT0GHfjRhwx5LC4gy9ewi0yFyv3VytaSPsPG/UMz9quYkxD3UDO853NsU2z1i5IH4zN1AsMAZhLKxCMbC7uBawuHEggdyVUNWk5+aMIe8bRhC0tYUREARJfMaDY4HkL/PWzpAlWqSe1WNuPtzXOUwaddO
*/