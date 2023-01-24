/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09222005_1104)
#define FUSION_CONVERT_09222005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/as_vector.hpp>
#include <boost/fusion/container/vector/detail/convert_impl.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_vector
        {
            typedef typename detail::as_vector<result_of::size<Sequence>::value> gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_vector<Sequence>::type
    as_vector(Sequence& seq)
    {
        typedef typename result_of::as_vector<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_vector<Sequence const>::type
    as_vector(Sequence const& seq)
    {
        typedef typename result_of::as_vector<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* convert.hpp
wqYnczmsbNvvcHr6Lhcru/hji0mcP/Cl/SUOY4sU8hlAazyb89k0LMyTjBNzZbUFj6odI+hLFv5Y9wP+GKiNPhlG33aNOIUgJzYcds5ZGvbxSBp2IJKG/X0kDvvLSJF7NgEM3+1HSf7p3V4NtzH5sqZJ8hHlBt2+1Pp0nNG+dPAXZJLRkrfaFrxCsy2daeBxg9/7hWxLPwpjDCvYTfLdO803uFvpQJPBunQk3LpUmmoKtS4N5oy1FujHHQj0osG6dBsDcE8pTb3VPUZAPMiNS5nCuOTmxqVSsC2BdU9Sd2impTEG09LBaIJ8mpuWWN0eP/sncGPT1qX5iUbL0jcdz21ZeklBGnSiKzcQXbPOYLJ5seO5LUvTCXCjAGx4zwB4Z8dzW5ZSCLC0K7csbXuPW5au73huy9LZXxFoWFduWVpqbO3fDue2LH1EgK27csvSCAAMsf1cx5WNq2DBrrCvZ7LWdNzkjIuoTBaMta9voTrG4ivPb2EWoDA7Ug9uR+pSmpbotpSmtfC0A3vYSaBWw1kNjU1I+j7P0/WfO3mXJkOXJjAc8hRKahUXUX0RSn/dNLRYGI/MIcajS/QSYP1cau4/zv1l//GUIEFStzc2G2m659uXNmMxmvMLTufOLoJlmd/VrTeeS5ux3vQnSJ8GWf2ODpl+aTMWowiCHK5B+g2Q5ubarPkZIR0a5E3vhNoC2hviDenWIhRjfjKY
*/