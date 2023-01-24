// Copyright 2012 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Andrew Lumsdaine

// Selector to determine whether a selector is distributedS (can only be true
// if <boost/graph/distributed/selector.hpp> has been included) so that we can
// disable various sequential-graph-only traits specializations for distributed
// graphs.

#ifndef BOOST_GRAPH_DETAIL_IS_DISTRIBUTED_SELECTOR_HPP
#define BOOST_GRAPH_DETAIL_IS_DISTRIBUTED_SELECTOR_HPP

#include <boost/mpl/bool.hpp>

namespace boost
{
namespace detail
{
    template < typename > struct is_distributed_selector : boost::mpl::false_
    {
    };
}
}

#endif // BOOST_GRAPH_DETAIL_IS_DISTRIBUTED_SELECTOR_HPP

/* is_distributed_selector.hpp
MLpRJr28EVudTWaEAzo9g6hKAWy1iONhqxvPiCux2FeaA2iHy7P9DT9IuwoN7fIp7oDlZHs+RDb9ZYVgbo67fdYms60uRLh2hjkn23yVbHpOCyBbZh/dswWrYrRhTQHZAqYMSUmhjJyISbq/wcJlww6AP3EfLuBkLUqzCGtmMPq9+RCnH1jKJajWWzajWif9sKVMJGe470VnTLquvfxUUenHhnCVTkKVPt7PXibyulC5nx6g3L9WrCZxJjH1VmJz+4dy3d4codszTkTq9s6TkSo77Jii20NPRFrNB/tlvPg+12364VHVYCY2Mqj1kQbz3fcjDWYiLYsDnS7zMp1OpL8QQacT0WASpOxNmxhlf8BgJoLBlFnkl3dGS2b8M2bzrwqNE+M0NP7LD9P4uQE0fkk1oP2IvHjIYEQ+eTySyFNORNJu11GFyN/GRhrQqH4ZHz+qEBm8KZXItqPbjTwkrCGy52ik4Uyk0UYg8sklCpFv9zEiKzGx5FE8JnbrcU1MbMxxTUxs2PH+MTHp/XBMjDaHY2JtzeGYWEtz/4jiLKWl945pWtp9TNPSK8f6tzRO09JWTUvlmpbWDGjpgBIldWtbyta2lDagpb1Hwy1ZNS0ZNS31NfWPKLoUnDre17TU9r6mpZPv929pvqalN5rCLf1nU7ilX0S0hPJdgMaEOibjmmW+Sthp8th6vGwg8uLkcCSpODgB84MncY6O
*/