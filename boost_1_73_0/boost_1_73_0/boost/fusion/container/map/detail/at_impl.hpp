/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence>().get(index()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get(index());
                }
            };

            template <typename Sequence, typename N>
            struct apply<Sequence const, N>
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence const>().get(index()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get(index());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
+PtgsGSYPiKGP9rYsT/AX+HJ2gb02wumD6E7GsfM3KuxV1vb26wJ/7zaarB9y3e5x85i7l/zcNRgbxx68tPYur9vRfxtg/GYWV6LAJ2P3YhFwTC+s0LO4HfPtbkfcYdZEXN4ZIfuNXxxfRaPORu6Hmd7xye/Hhx9aLC7sWuPAcZDMGPROJh5Dhtbt5yF3OburQAxtcKYBUPoDbAdN4oB3ix2A78FQ3MW83ASAQgc3PKigFm3lutZ1zCMFbNxHE+jnXbbnoUeYN52Ajtq2wnprXE8kVT8ChhMrAcWTGMWB2wW8QbDdg02CRx3iP8CK+DhdHbtudG4kaECA/lOOwhZxD0QVOzm8kigzNmZ5EwDW6EsT9wY/4kCP8KR7sbBRGsILAQgw1nowzDAAmjjBMDgBpv5Dg+pLRGdjCC5SaydMyUZrg4LfMCEGd0zdnBmsGsrcqMG+3xw/svxp3P2uXt62j06/5Udv2fdo18B1t8PjvZhvl0YKWT8fhryCEYOmTuZei53aMBv91lbA84zRNaOd+l3IMF3/VG0u7Y2eWCViXU/sANvNvFZh/319S49dIExfgwPXslWSSd4tCWaRMVHPAyDUG1SeDCbErnc2WUbLLpxp1Pg3zQMQLhA5rAJ8lw0dtywY7QM8eUORCTu
*/