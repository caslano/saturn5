/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<set_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return ::boost::fusion::at<typename It::index>(it.seq->get_data());
            }
        };
    };
}}}

#endif

/* deref_impl.hpp
pucXwlHwEng+vFzdr4Bnw3VwPNyk57fIea3Hto7F6PjVJtgGwz2Q4xFN33YYBx+DTeETWk53wO6wG/ntDX+H/QzYBvsY2BaeD3+ScsuBfQaw4RwYB1fCeHgPbASf0/hehEnwLRiGn8Bk+AVMgV/CZvA72BLuh9kw1SY8zIRvcd2e8BN4OvwrPBPuhUvV31XwU9U7/hm8Vd03w3ccecF34cMwF/fnYRf4hvirX/3rrvWpVz3r
*/