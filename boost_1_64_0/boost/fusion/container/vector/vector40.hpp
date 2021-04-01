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
gU9zENqVs/bUopZJwFi7Hct+aPC5gNCkVn3r+2bgh8iHIfBUqR/RlraprAmkNV3hKtZ334OnW6c0WF4CeG0Nr8oe83jhCQaH5If856IM+wgIUo/c6lm74ZOxsOiAUY5GzmC1u8k1j/++tZgvijc6jljzcfbawM0uWxjfWCrUDp6Pn9oAY3aekBt66oPN/Zc8d6L9T2brqEATIKzmhPWNYjE/j74Ug4J/6u3IE0w2bHAalPRwMlslipghyX9AgB1EvqE8x9yLFFblG2Lj3uakMfNN+10LXnGgqr6yH1bMhOFiNIx7O8fc+lI/qw62IR5SSahom85wr+fPpaE5OTLDtaK52T8QHR50FNAhH0blxHGqRNoslr8P9DoaOO04D16nXre/iAVyAMoovwEgLI7jNBZIllvNqSy8qxX4r4b431koWmfbwvxqCzEvubyH5UfMLkVzn/6TnfpC6wOY+8YCfjZVuSi84wcqqnMCu6FE8R08z7w4vaFmRcOg1iNDjAdFLAKxMjO6Bf/UTXau/PD/k1i7g4+z1Mh777qaxA3/nFwBR/P7XSU285XhqQ==
*/