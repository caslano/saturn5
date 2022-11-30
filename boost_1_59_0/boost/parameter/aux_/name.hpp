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
    !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x592))
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
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
*/