///////////////////////////////////////////////////////////////////////////////
// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_find.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_FIND_EN_14_12_2004
#define BOOST_PHOENIX_HAS_FIND_EN_14_12_2004

#include <boost/mpl/or.hpp>
#include "./is_std_map.hpp"
#include "./is_std_set.hpp"
#include "./is_std_hash_map.hpp"
#include "./is_std_hash_set.hpp"
#include "./is_unordered_set_or_map.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_find
        : boost::mpl::or_<
            boost::mpl::or_<
                is_std_map<T>
              , is_std_multimap<T>
              , is_std_set<T>
              , is_std_multiset<T>
            >
          , boost::mpl::or_<
                is_std_hash_map<T>
              , is_std_hash_multimap<T>
              , is_std_hash_set<T>
              , is_std_hash_multiset<T>
          >
          , boost::mpl::or_<
                is_std_unordered_map<T>
              , is_std_unordered_multimap<T>
              , is_std_unordered_set<T>
              , is_std_unordered_multiset<T>
            >
        >
    {
    };
}

#endif

/* has_find.hpp
omiC4CxR0BKPwVSfu2YovREpHEjtp4JdZgyZvOwPIyx8RBeYgsKHOL80sxEpXhwwlyQeUA2k2WWEXnlQnPX2F5sXp1R9C9syexbDx7Vv+Ec6VruS8Dq19/Q43XHL8U2+LtseQMFxyGpK2UxwudJXf8Y9M85Ctwz6JKUAfn0S/KbMnrRS4ONnmJkNRze84EbFtqiLgVDqWsgsZECP/BcpX/Qf2CUV+csG+XQrekYdzG6jKb5xQTNdWU2tZbGogp/E6IFj+q7HR69GdPwYNKmNvn8Qnq835eUMsubBngdvmhAW9DYIte7k3FZ9zg1UXhXMH/QIafMzAoM3Q3LDg7xZ/U7bCUGstSQDbLvBoECx1zVIO/4N2spuZ9qX7qIb+0mTRYeBtbwecfjSJhqw2NITteA/2pkn3Cw/Dl27xq0gX4s7+BbLVfRmVL/0Wk1sly6VGQzPvVsmT6t6TtoGsA32SPlnDLKL8Qqz+ebm15/12t88rQPqw/mqotqDAW19LmWk04tNnS00TXPet2PIn63xJ9ejNgSt7ISH/mrP7NGWVeUeOiQOE5D+5XGXxw3Z+Ke9oroJwbhuogrdGcrV6uYyaKxYqbgK88o8sPPbjrdvnnD3WHOQJkBq2iBDhuiA7eimmGYRL8hKm9vSSRF4M6N+X2Cq8w/ADyDZiMwwuUaKdroNdpb05zcm6zg17y+kp71JiXpSH/MemHMo/fAm
*/