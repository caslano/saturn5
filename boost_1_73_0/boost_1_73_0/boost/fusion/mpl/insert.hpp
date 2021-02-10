/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INSERT_10022005_1837)
#define FUSION_INSERT_10022005_1837

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/insert.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct insert_impl;

    template <>
    struct insert_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Pos, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::insert<Sequence, Pos, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* insert.hpp
7fYu59euWZHCbtc2xAXkEQiYsQdoe9zHPqRLBglOI/oX069C+c9FpbKWPNjqs3KAazioSg5WL7aUXL1uKyHKDg83DMqttkvvY9sbcKS1hCXeq2xUcW84HodkPpxPe10y6U3ng9kB7oPUWYHg6v+iC9/gCxPjQb1efz/p+r2sa0pwHGKlrA6Rl1OQdeK7cuDa8HCKFS6jXuZLafJkTu6xkQrNlwIbaksp/U+t3GBpEB0E2zNIMYMHtIamPUx16vt4JHrw8cR+ZUplLdiouWuKPSZZgr2WdVlxnylOLTxRMbraXpOSlcLeCeu+1bZd9JKsbGU7VvjeSphUCS3ljGi8VeVedzc4v7hftG9CH12oS8cc3rxJd3RjczseDac928Kfms3mDqAzbN/28rtm65ez0vq4jfVB8AZ/1ZvY9eOzU7xHnDRbxatagt+078aT0d19cXVtNU/Py4DZbIwefZ33pjPHd9I6r+3haZHsn4hpxnMYNpu0+4MCdwDWHk/6w9nV84X6vOmeEmYymzrHcrt2o3uYStaycOxBuRCQzmg47HVmzxs5Oft0flrCfR2Mrsmr4Fum8v5OCosZ4LT561Z68OAYY3avSee2e9Cf/m17nAO2vc5G9r9QSwMECgAAAAgALWdKUo3yuemqJwAA
*/