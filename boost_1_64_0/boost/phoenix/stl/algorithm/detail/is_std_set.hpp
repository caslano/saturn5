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
// is_std_set.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
# pragma once
#endif

#ifndef BOOST_PHOENIX_IS_STD_SET_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_SET_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include <set>

namespace boost
{
    template<class T>
    struct is_std_set
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Pr
      , class Alloc
    >
    struct is_std_set< ::std::set<Kty,Pr,Alloc> >
        : boost::mpl::true_
    {};

    template<class T>
    struct is_std_multiset
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Pr
      , class Alloc
    >
    struct is_std_multiset< ::std::multiset<Kty,Pr,Alloc> >
        : boost::mpl::true_
    {};
}

#endif

/* is_std_set.hpp
AJYAFsiqCSb6+kAnpGkp885xSuqzXQv2k9y9IbwjokAmg55xQEAb06xFOFok7Ylh2rzk7bBula06DBaHr08t5vUc6KKiw7x/XUMvIP0GmGJTMlexKTFArWP/TXObYQfg/T+C69AHVb+THH7BDxouSfewubuR/+hFtXRJmpqHUOqDZTDQrFrDfZtzw7NLpKTCMKnVcdVrYLPmoVtRUvHvqxr41UT/TO34GSoU0Y28IBzJV4XIQ0ZMWpd3lkL/R7xteTOw6b5EMSeFH/Ls02oNzCN1iX4Vu5JZVHvPVBAnvb4i3dXRcDHrdZtBCLITg0czSi0M3tERVIe6pdQ0D1G7rW71YzdOaU0IWL1jmIMv66gdLgoGnPKemcfJCCW6LlRPnkyGufVe+1Vv4DP9t9/v3qmmhA+gx7EzfiyrNGY6BWd5sF5kWXBuH5s9NadBecgWM/tM/j5ngOJ0MDl2jR/ukYjUJK7ETlE4tB/VqoI3e7CoxJF6e9a66JHXmGOQrB0mCrSr4L4SAdrUaN559gKFh6EAbvhHX0G9NRYSRLvjoL0gltOAWI9OB5b5Ng==
*/