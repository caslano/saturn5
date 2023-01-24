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
en2i5Qbx+zzxvyfHiX/WKCv+i7LGWsEAIzBaYy2xcH+JtdgAb8R9tjLX4aksSDTtEKk5ysGSE4DQzvLPLWTXpTDJXQuP3J6AL0l9IzcW1zi+e3zLwiRgfhfovRIL6G5f45+M8v23djEE90HKBTCpRxfyNpgUGDUZRdlbdyMBfaURZCWvyXdXXp2cA+KsX3hhuSR6A+OTo/LTiyz+i9HglEf5VOz3XaVUf9F2T/lv/gSvLKGZxeRXXIimkzQQkBXwLBKf1dbG5JITfUjTr2RdLhqD3aN2zoKuutMnOpzP1zVGXVXH5rjGozmuVH37UZ/dRALlsRmw+5SsV3FTOefRxFpraozF+frOR2INNd9wG0q4mym2v+YZZrvIwzx69YKh9puUNuMvlBxTh4cEV46gfPnOGFDu+81Ztkv8KDl5Ec7VYjyH/eTVMlftPIxudbnZgLAzcHUFhiWh0PFuT/ddYnjcrBQyN0Z/u6ZbkUfKGUukyGAX4Y/FkBC7q/KCOGkpuDImGewnodcG+AFboGWFw0Ly6nmBm05orn9dACd2ZrIDLHu6K7MswdXRAHlHhPzNKIY8O7CWpsPORqGkFkWrGMrh00n78zzSKmHAldknjmU3f4mmfElE8NVcBf7VGG9bq2UJNjB+TiYrQXyIG/LophjwhTqatm7cT9vBfjr5/DgLWbIIvscNZEjaSDT/2wR9V3VWPBotN36FLajI
*/