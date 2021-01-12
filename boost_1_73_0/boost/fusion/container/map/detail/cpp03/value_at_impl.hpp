/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Brandon Kohn

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<typename Sequence::storage_type::types, N>::type type;
            };
        };
    }
}}

#endif //BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP

/* value_at_impl.hpp
AgtgOpwCG6u9mdrnwqlwOSyEV8IieJWef1DPP6PnX9Tz++BCM4eItkzvfzKmMrJPmuq/PRtmwHNgMzgWdoHj9ftiIrwPOvYq4pkML4aOfRksgNfAqXADLIIPwmnQSccGx5TpWJzKQfYZ0nQUk14bTocZsAQ2h+WwDayCneFsOBTOgePgRfBcOB8WwYWwHC6C8+ASuAwug7fCS+FWuBw+Ci+DL8DLobTHto696xyFTbA7ZqPW
*/