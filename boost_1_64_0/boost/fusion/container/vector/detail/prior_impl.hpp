/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_IMPL_05042005_1145)
#define FUSION_PRIOR_IMPL_05042005_1145

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;
    template <typename Vector, int N>
    struct vector_iterator;

    namespace extension
    {
        template <typename Tag>
        struct prior_impl;

        template <>
        struct prior_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef vector_iterator<vector, index::value-1> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }
            };
        };
    }
}}

#endif

/* prior_impl.hpp
pIIL4JthLvkg6m2wfwUuVXEBHqF90RV3+ozIfh17w5094+h9O9LxqX0whz3MrcsXfOAKM6XoHrpPp4czOHC9ShylbVeIXlO21umPbeDJh7lGk4aXLXt3HupClYXbrh/4oze7o1UrtXj4LQFDeStdi1pWv21zndL3AgFPP2alGBtJemnrPn8lhw9eP6r4cLyGUnM/fif1JYEgViM13mMwLAEPVKS9VxI+wEjBpmxYfsKa/jo3AxgVq9usliSiCMbUSarrukkG7fxE191pKzyCgHE/tB8gfTixx+C3Vx65VIpcDt665StZ7+r2f5tiClzOu7RRgWqkYNS2P2mFWz/Tw5b+Tw6fHf6z1VdjanHl0bafeVHca/pT9Qc3F2dqU2Nx87kK/DnypmRh1CnMXcColy/WlNpQHZw7syRBPumdVYZiCmLXdgoBjG64tWvEVWAab5zhrU+jCv5wUAe7+V0ZVsB3FcXHWnlnVCao5Sap7Pi7v/hFSBYJ3d/5hL/Jk9L7e+6KHek6xPAFwfTiQQIA3cb1B4WFYDukKVzgXKvPV7TI+c6OwmC4xOEOZA==
*/