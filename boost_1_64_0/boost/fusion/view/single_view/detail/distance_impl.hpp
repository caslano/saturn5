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
/n6e1J7ii3i1/OKnPGfbhb+fayuwDoXeGTc5N0DWvh8os4TyBFMalRlnjZWOFP3KxmMdAqlfU7gISf/xOKHCLEi9IBLdYuw7GR/5AfRcfSdH6Z/vHF3D0sBROIQ2eEAHBKJ3ldMwhEUdK9edlgkieXUEQ1dqxj+oL1YJAXa0xTBvuLjb7NHy9ze+9dlDxn4cqvPKKW2JiZC4wpZXbxDPdlZJQ9yg17Ii6xIXaksk+N8QcfaxVnoCZizSaK07Jnjp9M/NN0k2CHeTY3+aN1BO4XdA0r3nwhaabBV1fItLFSVy17VGR0R3Tk1R9Yot33kZQckxjYdzuEcf16GEJrUNpixOKb8lvmZfsGmdaJXQRwlWSB6WRzfQjkBhBi8PJAQK5JxL8mUh2YJXtq1FqYJzf2UMxO56/y8N1J51eWh+sIwKMXaJeWb4Lq3/I1Q2dS8mhVLvynl3YX47Sh9B5TsTubawz7hcb0K/4Udnb3Zyzxe4zFC5c0Lj1077QhY92ULOqYbssgNwYDRUsZa6VTCA1RCNcVpAZU+I4JUHJRUlKRjxHUL+e+IERvAafQ==
*/