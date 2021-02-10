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
EXrXN9PB8EuMh1JlZQiyMg1caZoqRykXBEsZqcU6Ri2thykYzsFz5TwHbLwy+pC5CZ7s3IUYgV5WzkAupKpkykTSo/S+dh+SJGtsxeqT3GQuyZ6Of1j6+e+TTFnEXK5gag9v0DiKETxjzE2uimA5IbxZN2mlXBk/q2EqnSfGwlFVhViMU+TWsgnjTXri4IaaFSsfjDPaBaqH0sz/cOQ8hihFYzUTcR7YKTec5hgNXyvbOrcnf6LY5LRN8NbSPOvNYTSLwZvuGIPxG6TSKRfjbjC5vL6d4K47GnWHkymuL9AdTkOwr4PhOZdeMZkFLWtLjskt1LyuFOUbztcbSRSx2IZvXqVST84Lb2VGIitm+BGBG4qrFHa8mtMp36wOjrhvgi7S3uGiezXuh4SvuHH0DFQ5wmR02weHXsO1KWl5urmY/wP/eRpFtOT8a2zV+LSTU9rMRGZ0oWYMC7x/fUr3e7ejK3RKbo4q9By3qlC6MH5Vc5V5iqMX73ijnZpprmVWSotOLr2M4dR3Er41W2ALo3J0uL1tfcCK9khzd4cEbP8jDof+BVBLAwQKAAAACAAtZ0pS2DUbVeQFAAAJDwAAJAAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvdGVzdHV0aWwuY1VUBQAB
*/