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
jjubkF8YXLiy4ntlOrdgSTJ+V9+zR7CmxM3GD6LVBFBCoMbPePkG69314vdWmnJxxlocuE7b6jWZXe3qGGEao6Lu561NTObHlMGKVMx5usAICUHijpFpDn9k57HTFrXZztKJs0zvNAVTly7Avy5V8E1c/KzzS321kR20RLmfmhQa1tU/mcde9v6VF8gacavsSlGuJAb+JXVrzSI8nfxcLag9l9PfRNcewYKXQIMeB9+x+LCVMIPZzio20mIGj4ErsCAD8RIloyyTwCCzf9qBRDLfwXZS194RyW61k8xzJ03uSZLz4Q/mwsK3S5UdtlNzz3mfnkf07cgWzgixoJP3RZfInCTdiKzu6HwDk/cO0112fbS5gf0blEBbNnj8kUwmFCpcIqoKsr6/rkveu0mKbPKnyR4pw5ypVXueqq9sWnhcvTunb9CN8o6xAinmDsvj29RgJ4FoTuurXaKNAQQJdGP+xQED7zaghCY+WDucbJ7PS9gniWaGlyqct0yqhHoc1pFyxBJMjHMmSZxWvNn0nC0WWYwKwUO2riFgl4vJUXGb42tgCKe/yCaYMg==
*/