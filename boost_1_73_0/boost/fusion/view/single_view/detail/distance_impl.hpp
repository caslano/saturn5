/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_DISTANCE_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_DISTANCE_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/minus.hpp>

namespace boost { namespace fusion 
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<single_view_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
              : mpl::minus<typename Last::position, typename First::position>
            {
                typedef typename mpl::minus<typename Last::position,
                    typename First::position>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(First const& /*first*/, Last const& /*last*/)
                {
                    return type();
                }
            };
        };
    }

}}

#endif

/* distance_impl.hpp
rsEn45bTRTPbhNF7fmnt7Mz5RIN5skd+xPFTuDtXzj6rQwuOkt90j/OcxZ0tfw70lz4mcBFbhuWV59D5kHkAfX/O5nn//Qh9xx6R4s82bIzT4LtHP/D4hHMMtrJ1egX2aLuZoh22Xewb3uZ9650HHsTi/vh+1NPvSQ5aGnvPnBuOs2i83LTPfafqe/362H6CUdNQ+37j42hfJ3d/9re5aIM1RVzwJ2T8sDJVo8Lu1fjA+a9d
*/