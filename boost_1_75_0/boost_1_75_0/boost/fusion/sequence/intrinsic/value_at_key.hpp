/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_KEY_05052005_0229)
#define FUSION_VALUE_AT_KEY_05052005_0229

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/category_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct value_at_key_impl
        {
            template <typename Seq, typename Key>
            struct apply
              : result_of::value_of_data<
                    typename result_of::find<Seq, Key>::type
                >
            {};
        };

        template <>
        struct value_at_key_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : Sequence::template value_at_key<Sequence, Key> {};
        };

        template <>
        struct value_at_key_impl<boost_array_tag>;

        template <>
        struct value_at_key_impl<mpl_sequence_tag>;

        template <>
        struct value_at_key_impl<std_pair_tag>;
    }

    namespace detail
    {
        template <typename Sequence, typename N, typename Tag>
        struct value_at_key_impl
            : mpl::if_<
                  mpl::or_<
                      typename extension::has_key_impl<Tag>::template apply<Sequence, N>
                    , traits::is_unbounded<Sequence>
                  >
                , typename extension::value_at_key_impl<Tag>::template apply<Sequence, N>
                , mpl::empty_base
              >::type
        {};
    }

    namespace result_of
    {
        template <typename Sequence, typename N>
        struct value_at_key
            : detail::value_at_key_impl<Sequence, N, typename detail::tag_of<Sequence>::type>
        {};
    }
}}

#endif


/* value_at_key.hpp
YliCa2O/1RMLtvr22m60xrxKYlvDt+NZA3Lj6oG+Har9dXo51wZ4p+DalNUoZpX2Y3Ypv/0bruwL25f4mvuZxP6jHbIivhlXiF6GOZRrOeiHDrF+8EwSz+bsSiWfxlp/b91Tbacy7d90MBuWBVBWngxLs3sm6v0lqVXzh3Y3+ZtwZ2vBKTy5Iiw5gCbZiaAW8+NglHpxu4eFOLZP2KmnnEE/Re5Yb+KuVJZaccEZNGiV9ZNkUZDyQzMTpYpoRsqGRiUP98ezGyQZujJiU775AeFqloJltshFsCKEvwBigZP5TWxiPLq3SlqHz9Eg2MohaOlK/X0HmZziLyX7i9b4HBueNVmINcOKC3cmw7+e0SkSPA29yg+CzD1NxEmwt+v6+/BNq9oG/4BU+lfXdkXzMAqXQZ/Aj5KHbXY5atFRFs3JNzjOoH354O26fTkURrrL1s4XJZvCxKO06R0cn5ka9aaFeqaUCvOg0+HXk5kDv+MzC+CXWB+dNzdChYrfCqNKeJSKPUrFHqVij1Ix3PNl4zNnefTQ6Gw5D5se+HxKxKQCCawrU/9PQBQhEI3x/0cgeiMQT5Ad3toDrx/l15fi9SR+fQleT+DXRwS4HsOvk/5vCPytGBC45v+KwHNCFIFnhCgCTwpRBJYJUQQWxyBwK17fxK9n4LUD5QK3QTVZizE9XCpO+BiWS8HNGPI/QhdGGPFvdKMIGu93Qxti
*/