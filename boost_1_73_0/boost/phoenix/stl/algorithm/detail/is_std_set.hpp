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
H3Hyn9XCt1XH1vF392HIxFDeRcL35dzC/i2a93lCiNXm8d7vRobCTkU1ghb38GuNiXsrk2vfmxzYGdxUoS/3/8DekX5mAxa+Zu4fEm1samVLvYmheObGxj7JCk26sk6VA4iNPZ2dJzb2uxzU2yvkpPO8ir/KhWwKvOR515u4JDe2jncHkj/Jn+RP8if5k/xJ/iR/kj/Jn+TP/+snpYxLrd7XSCsG/8sqZb0U7gNwWUqmcOCm
*/