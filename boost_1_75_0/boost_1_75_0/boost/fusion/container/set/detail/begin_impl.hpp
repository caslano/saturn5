/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct begin_impl;

    template <>
    struct begin_impl<set_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    set_iterator_tag
                  , typename Seq::category
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
jBiulI1LHehelSa1xsM7jKAnIHWyt/oBD9N7tVIJjE8oJYBLWnYE1DFwJ6pzKf6Ff6kbx+S7eyDZsPqevx8jInUKVK3uNLZqyMDyOPErhkMaBMxz4YS2hO3KNsVK5tCLu5e2NGy9u7c6mc1n/wRWFdMisQ4qWmYkAYID7lOh4G3EnC7M96MVin/IF96a7ziXbQkzfiUBZfwyndW1TMmROQCYZAEgkBlAPhNBZNMLvH2osIIw8wrxdN7g+8T0g12lVJOoYcyWee0GVMsACiz104QoPTv+wjYLc0K+4QJE/EP2EsUAAoZ9qMz9kg4cjcpOBguDdNG65XOXYWg6Ei1lSU2V3eRG8nz9rOYyYR0TovgWrswJ7oUBTHRpm2RpoE4aL6CD9up7WYGs9i7aAGsvckFSdtgTx1aJLSOxvDvbhY8dDFlovLnrlEsxdnTTvbomejDNaNmxecEC+Ka3wNyV8ptS93+IlW1ZYch3+Kt+dIh9nX+VleL/fPyf4a/60+GteRi3HuzML8Yap3e2GBLWl8lXxYW96imovUzWxobVToHarI6GeTvU9pTvDW7T665wagwR0Nk9Yy0YanGB6nDwud7qOL471w5ZWyZLyGqcZ0HW3Ci4IyGrbTxA1hflffKCVhRMlTL2E/HZLd3hYqe3dmOcHeaY9yGrlkXQT3Bjy6txHYFdp8n/J2AX3AhQd0ncIaCuYHwE1ME39ItT
*/