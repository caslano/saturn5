// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_REF_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_REF_HPP

#include <boost/parameter/aux_/unwrap_cv_reference.hpp>
#include <boost/parameter/aux_/tagged_argument.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <
        typename Keyword
      , typename ActualArg
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
      , typename = typename ::boost::parameter::aux
        ::is_cv_reference_wrapper<ActualArg>::type
#endif
    >
    struct tag_ref
    {
        typedef ::boost::parameter::aux::tagged_argument<
            Keyword
          , typename ::boost::parameter::aux
            ::unwrap_cv_reference<ActualArg>::type
        > type;
    };
}}} // namespace boost::parameter::aux_

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

#include <boost/mpl/bool.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <typename Keyword, typename ActualArg>
    struct tag_ref<Keyword,ActualArg,::boost::mpl::false_>
    {
        typedef ::boost::parameter::aux
        ::tagged_argument<Keyword,ActualArg> type;
    };
}}} // namespace boost::parameter::aux_

#endif  // Borland workarounds needed.

namespace boost { namespace parameter { namespace aux {

    struct tag_keyword_arg_ref
    {
        template <typename K, typename T>
        struct apply
        {
            typedef typename ::boost::parameter::aux::tag_ref<K,T>::type type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = typename ::boost::parameter::aux::tag_ref<K,T>::type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_keyword_arg_ref.hpp
M/H+ytkmE+9vgpl4j4v6vlmzvwu2RbN/COavmfun5J2WezWCxy2vkbzL8lrJuy2vk3yj5fWCb6b+dpHk1N82SE79baPk1N82Cb6F5C+WnOQvkZzkL5Wc5C+T+VIOjebLXc6/m8w5+oaHuBz9w2bJO638Fpej/FaXo/yVLkf5bZLHrfx2l6P8VS63Zyu63J6vKHmXlf8Ul/PvLHPOv7XMOcpfI3m3lX+Ey1H+Wpej/HUuR/kR
*/