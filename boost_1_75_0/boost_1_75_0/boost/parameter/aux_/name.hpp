// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_NAME_HPP
#define BOOST_PARAMETER_AUX_NAME_HPP

namespace boost { namespace parameter { namespace aux {

    struct name_tag_base
    {
    };

    template <typename Tag>
    struct name_tag
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/bool.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_name_tag : ::boost::mpl::false_
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/value_type.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if !defined(BOOST_NO_SFINAE) && \
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))
#include <boost/parameter/aux_/lambda_tag.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace mpl {

    template <typename T>
    struct lambda<
        T
      , typename ::boost::enable_if<
            ::boost::parameter::aux::is_name_tag<T>
          , ::boost::parameter::aux::lambda_tag
        >::type
    >
    {
        typedef ::boost::mpl::true_ is_le;
        typedef ::boost::mpl::bind3<
            ::boost::mpl::quote3< ::boost::parameter::value_type>
          , ::boost::mpl::arg<2>
          , T
          , void
        > result_;
        typedef result_ type;
    };
}} // namespace boost::mpl

#endif  // SFINAE enabled, not Borland.

#include <boost/parameter/aux_/void.hpp>

#define BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(tag)                            \
    ::boost::parameter::value_type<                                          \
        ::boost::mpl::_2,tag,::boost::parameter::void_                       \
    >
/**/

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_TAG_MP11_PLACEHOLDER_VALUE(name, tag)                \
    template <typename ArgumentPack>                                         \
    using name = typename ::boost::parameter                                 \
    ::value_type<ArgumentPack,tag,::boost::parameter::void_>::type
/**/

#include <boost/parameter/binding.hpp>

#define BOOST_PARAMETER_TAG_MP11_PLACEHOLDER_BINDING(name, tag)              \
    template <typename ArgumentPack>                                         \
    using name = typename ::boost::parameter                                 \
    ::binding<ArgumentPack,tag,::boost::parameter::void_>::type
/**/

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* name.hpp
BGDXbUv0+OvmU4mtk6qWKGbQeXpnVe/0/pA97jHlsCj2RFu02ILQ2WelYNWQGOENzjbKcgkghevX1Pd/bhTfJmAG2dIsllmAMYk00Ck36QnBfFvSXca/wVRbwWy9kyJRv5J4VavKuM40MsyS65T1S6tm5o6ygM4/n1R+Abw4apQ19wXbTJJyu0Nf5kc+wQQ7X715xxdJB4gir1Ug6MC2pu/H8bfjG3H5bSf6B87l2uzyV7Vr4peSFeE1rqNPwCjTuDeF5M7tFZhnfocgIAZz3+RO/TDxYSSMAcYcO8rXs8PKmb+mv4mD3RU1fZL/UVb4Sw7RXnZjQaxbeyKhtcL9bQDzFR7Adrkx1XGy+aC1U8bszwr0N/ng0segUF6Q42QI7wk61gifj9B6zkhFGTv5iL+gWsVy+BTfHsBW3ifi6hnNyNxxU6ZMkeJsVNOU3ddyyrnEFtKrK4Ar5tzD3u8OwLF2DSKoux+vkuxGvmeZVv9T9L3rleRXJZq8IzwBzdQYI60qRAD9Q0Wi/19tp5EInzADvkoWkZJMb0w7B1phboW0XKqmC6B/d6oCZy7xF4swxpF+pp8G1eSq6HE9Kj8tTpkeZHDArgltQ6b9jdJnmDkvr0siBylLqUpHi+Hpw4FgokC9YenruhT32cN7gyp4rRGi5vbzmPt07hfNskG9eMZt9Y7XCtQsWg+SP1W2904ydB4ElYObDBhrMU1Z
*/