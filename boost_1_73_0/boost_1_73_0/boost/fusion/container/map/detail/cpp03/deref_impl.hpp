/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<map_iterator_tag>
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
                return fusion::at<typename It::index>(it.seq->get_data());
            }
        };
    };
}}}

#endif

/* deref_impl.hpp
U/wKPdboUED8jRj8syxpYWv8Iv8ii1ZWcJjVFdxh3zlyq6d94ruswrYoLCfeKdXldlN2ZFVNS0rUrTICyyD0fcX4Tgqaqk/04bO6duzH3ewOGe6cM7CYntf+D1BLAwQKAAAACAAtZ0pSqWebh3YFAACbEQAAIAAJAGN1cmwtbWFzdGVyL2xpYi9jb25maWctYW1pZ2Fvcy5oVVQFAAG2SCRgrVhfU6NIEH/3U3TFF92KRl1393Zr7+pGIJEzAQ6Ibra2agphMLNHIMUQV6/2w18PJIbAEB9u0UjoX/+b7p6mx0MepxGL4doguuFSbeqOqWZbQ3NEycQcEduj1weHyMFTtp9p8ObXXQfwBl69aPmheOG9lHDy7DsLCzU3pT+h+kGpb3h/zcgAtiI/6TG8LvITjkoRurbyWX6n9DVD36Rv8s9ASn6j8itSUExKatnyOecP8wKOtGM4//jxNziBi7OLsz7oQcpZAl7B0nuWP/Thc1RS/pwHT0+ngv3RB1ZAkJyuVflzLkBkcfEjyBng94SHLBUsgkBAxESY83t84CkUcwYxTxhotjMzrVEffsx5OJdKnrMViHm2SiKYB48MchYy/ljpWAZ5AVmM4qg84qJAhauCZ+kp2mZQsHwhpA5pPkhEBsFjwJPgHg0F
*/