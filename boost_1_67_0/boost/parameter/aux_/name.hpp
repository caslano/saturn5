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
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
*/