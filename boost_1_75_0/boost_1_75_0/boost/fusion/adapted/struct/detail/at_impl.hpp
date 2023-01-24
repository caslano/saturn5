/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct at_impl;

    template <>
    struct at_impl<struct_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : access::struct_member<
                typename remove_const<Seq>::type
              , N::value
            >::template apply<Seq>
        {};
    };

    template <>
    struct at_impl<assoc_struct_tag>
      : at_impl<struct_tag>
    {};
}}}

#endif

/* at_impl.hpp
+31jD8rLNbuaTFRA2jtIzUVwrDh8Yc67zjbNzHl34n4z591bAynn3RCbxkPSXTdjzrvW9ys575qNkDnvxJPOI/mJx0qAF6rVlwDPLjc7lAR4e0coGLd/YzvVkwDvJ03uT1oJ8M47qWtmArx1AW8GJMD7yhwdS/6nBHj993NTnjMBHhsEIXmrZ5O7J5m++nPg/XE6GkbCX+my/zRp9U766eFhs4p+PhDScD6mJ+9sNKfUG0JMgnNKeZQEeFLWrQR4NHIFJcC79Ue9CSmmNs6Sh4/BSP/+U9F8RvHPKbZXlAPvhXv//82B92B2UA68/nsVXRu6Q1mpfEq6ljgRda3Gjbr2jVuuVLbsNFcq4XvN2e9Py4J1LfkHPTgHXp5e4kVx64dbWhe41AR4dK+Fq2yYR4paAznx1tyUF5j6bvU+vQmp725+l3qhbuq7J09GNyhHVw5uPK9X/326VjevV149ue/kx1i572hp0++k8V3d3HdH9upNyPr12DsNSdZ7J6RkvXkCleXlE9EN5b7LHNSorjy8t66u5Cq579acbinMfvZePSD3XdLepqjG5zPliBmcfe3gcfkBe45H15/77pWBjfL99Z56+ZZ54zJommgsbx2UN+7xPU3h/OSMhji/3OQ8/jg2/ep/o+vFwYBv2HpHo99wdHej35DJ3/Bvq6Bv+Hx3U77h6ga/YeQ/8huG/oPfYPs3OtD3YBB/QKzy
*/