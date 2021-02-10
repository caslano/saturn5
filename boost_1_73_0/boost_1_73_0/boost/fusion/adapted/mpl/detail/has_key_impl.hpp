/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_HAS_KEY_IMPL_31122005_1647)
#define BOOST_FUSION_HAS_KEY_IMPL_31122005_1647

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/has_key.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct has_key_impl;

        template <>
        struct has_key_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : mpl::has_key<Sequence, Key> {};
        };
    }
}}

#endif

/* has_key_impl.hpp
N+KUKYN8srgNGbpg0ChjI8iw0xyT+3wLolNqznC2wsDlUClsDBUhuZ9jLF21KHmUzFGSOX+SYeGDaCIFsBpSui27Ett+63oCLZdn+IYhJruzSyFDmAvZX7nuZaplGiPj7/3DxxGkEpQbz65ltlaklwjn1h0EGw78ApFCvhBqeApe7ZwTKmSYCDB92SBdgujl8iMn8fsiSY+m83gNo72H+wG1mQozfdcpbanX3tv/eVks0/eDvRN+RJDXNfVnUBTmeIiNJvcY857SgkvC02XJzLlvTedCGa4vSA5VcKvNDEquLTX4S8323eiUMWJDWumgZh2KV8lcCz92zCWI/s4571xrBgYzrXpKpUYFpsmxtEinVeArj4YBPY5X8zw44jVzXL+emy3Hg9ZZIOWx/q+NELK98q4QtDydpPMsiJHQWLlVpWoNqm/JUceww0738chzGB3nC+fgY2MGaim9i+B1ni9CmL2NF2GwSBcPPYHeoslwHuNeOoFF2SOp4FLpc9jzsuaT5kJDls3H+TyDC6Qdk9bs+zyn7+O3i/k0eCWIYa4+Ougdjjjn8kzIq+uW6V4SCiHeIHD6HCCI/dhuu7HbFxEUIdkHJdpq/k+Pw0luqAI3Rb3GEbxE2jwLgkjWAd2K7gisW/i2vo4+izxC
*/