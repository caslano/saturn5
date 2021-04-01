// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_unique.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_UNIQUE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_UNIQUE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_unique
        : is_std_list<T>
    {
    };
}

#endif

/* has_unique.hpp
D1zyHnToaRuOi0EyfaEot7IhHTXA3qzlcHC3tY2GtqsNz+5wljXPSSeNd4j0EECe0P89r54+CyhB/xo0Sag2fi5U6c9CGVtbQUeovdEStezCDPNvCqRb+LQg0uHMOB1gGKbt8bFHhMVn5gBRBhw3BzTfUQKwfelsvoh9VA0BBMOSuhpIxSLC/z0t1LotcVhZtbywOrvecVBnLRJaa+oh9i9WCtifZFVs8txSVNSPtLlyTg10U7QYTIpwr0+JkpdU5DoKJMMmlgcUv7pFBJzwMT0a+/OQXefTVtvb9u2LGGzsdzQId1yOkEYWG0Cq6kQ0jSAMCGa1LoHanSlYLMEMKnHeB0J7htpb2bkC677G485CU5nIhc+djU6UsKTYq/jD5uf+J/frl1E9OWPR0mLWLnNf090LkVK8dLgo8ONLSWg8DmkHENJQW+Tnld2UW89ByKg0Yvk3UUFuMX3mXBoCFB2pQTOarJZTWunAex6I4OKobmpB6KA9RDbTwfcXnzG3U3tmJVawaBt0YaAwVfZo4FSHTrxufIUc9s06HD2IziuQrW6VWUc25FDhjQ==
*/