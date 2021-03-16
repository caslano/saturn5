/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_09272006_0719)
#define BOOST_FUSION_BEGIN_IMPL_09272006_0719

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_tuple/boost_tuple_iterator.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef boost_tuple_iterator<Sequence> type;
    
                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
asraS7JFTHOFm7lNGnejQmK3Db0n7Qv3tqEEnure8FTzhqEj0uS2e6oRMoAGGjwYyNfnlvpEs7I71ktNtavU1Vvk+MJy3WH3J/Ne/q5k3PV2bs8Pv2Lfn98h3v78fhInSbT7oen+f4cvmv6EFbYbqb1ImMnptVhja5JYP94jy576nBpobRLHU94gy/GyfDSJ0wHdn8RDkQe0Z1pKSZg6sgdlSbvaH5cl7Qp9OInTA62X5UmNk5IogpIoUoI+Hlg=
*/