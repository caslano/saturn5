/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR40_11052014_2316
#define FUSION_VECTOR40_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector40.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector40.hpp
CaaN0XWQ4vq/Q3wLxvHTW8i3QD5+g/5SlJvZX4FBbO6UWafYzKbyYzPPYTZTgGmJiKS/B7qq6JLdDB2+NstAh3/gdHjE60iHu+/U6HCyJKennMz0L4zISO1rL/s+EmjxjK7vjtNo7xikvVdx2gt6o7NnLelOiNzPcNrrQgx/kFWQ2s5e9ht7lg4c7+kp+YeaOTrfdBTJZCkS3K0GgvsWEtx0poAHBnD4bRw+aIBvo8PvN8DP/tDpm5PKy7nkz5THGcl3bkMyexdozAMvM1DZ+ggDlX2mjlsyOuzVaGa0ILMByBu1jQgsXJgtqeOE8/dPsXCCZE6HskiMn0b6CsXGimI1nyJ9TcaiTDXm9DUwE3vASWxKHZDYZz4lEnsTkdjSuZH9kKJGBXuUzo3u57FIkbXBTpv6oca74hOkr2zlYjNSr7GXXRKJBmVGXpM18hofAdMIlHUMm5U2gV9pHuzlK88CguJUBYcvtfa/laYGJ+tzVqj/ZZ4WWYD8YGvobySkEM+6PyOjbyPxo0XxO/5ZAJez9yjyG0BG57Addyrggxuq/iHJogMuX0KgkHeg7C8UWQ8F0BYL5PJKgUi/CHK5XJDLTARCaqkhQUuF7YteZhye8f1rv7L3bYFqrLerjj/3INW4COM6tVHMyE4YwTyK1AxQyN2iFMjb95y83fkrkLcPibzN6UbOhMrpH1mlt1Av7GVz2KZLbedeii08
*/