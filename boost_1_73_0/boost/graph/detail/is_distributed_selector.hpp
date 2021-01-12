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
6cFS6q2DyMY3y2dIZ/E0EeDONyOsrCwKRD1oHrnG8+mZ2s5v8ZO434a/NfS/+ivH31L8He89td64ESLGSxMqjYz4DH7SLqf1CSPAnZ8bqDcCaKVdt+rz1Sa0Ea8SBgNUzlUKD4nZdQa1jUdefhWnaD/6hFD8QejpkkpTMAjlLHdbSmSw060PqdIGl3scBwULuXX9UuhkVegJvJd+dPlym92p2o6D3G2C+A+lgviD4NPtm87t
*/