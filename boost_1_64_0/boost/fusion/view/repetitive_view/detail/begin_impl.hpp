/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_BEGIN_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_BEGIN_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/view/repetitive_view/repetitive_view_fwd.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_tag;

    template <typename Sequence, typename Pos>
    struct repetitive_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<repetitive_view_tag>
        {
            template<typename View>
            struct apply
            {
                typedef typename View::sequence_type sequence_type;

                typedef repetitive_view_iterator<sequence_type,
                    typename result_of::begin<sequence_type>::type > type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(View const& v)
                {
                    return type(v.seq);
                }
            };
        };

    }

}}

#endif


/* begin_impl.hpp
HpsrDyhd+ie7Vucy3iv9BMb6MHbp0cY8VZQ45Y9LAXS7I4NMkgiahDOQ8leeTg2cBtxmeZMJ6i0AUzNsL+5l7lvQ+SPR/ACYApASzLy7ES8GsFOeK5pmd+jX/K6/m/+OAN06vOYhpsFNKC7PZs0oE1546K96Yoiqkw7iTtbZh/RyLXNyvQGV32SonQ3VdsHghA9tk7rXUGKBlVP556YApILJlxAtZCU1Sx6Qboq1mOg3sjMwktmfHopu9fUJ0iHxq5EhTe9vrL3WRHj01X6k6tPkL1rmE4MxCI+GNlSsuhumsqvzroyoncHIe3m2No3dGLAXE+vED15jdWcKS9/epTXmsAYl4lGYza35FujZa/+dtWA/DBEyiijuTDg+dy4LuqqwxACS++ek6KXDIELGhZmIes0iz+8DzDAAEQmOcG5y2MxhZ2AkuFjDjc2Bx5TrFujj77hGk81RGQxH+wgsuv/rakY+8TSinZ9eqYILEfDJ0Z54B6W+3lR7in7vzZTtmvlqQoOgNmAmTVAZJ4MZb2+cEUUs9d1RbdXCVk+xbIT6346lNDDbq4GAkg==
*/