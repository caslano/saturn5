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
2/NOAUuaxb7vz7puT8ujXNoXeefgUfUHajmqyz6XrQWwiWTU/XpQzUqM0sbngVqgMQ1l/pf/Q05xo+7MoCH9K+FXlBWPCX6tqXx8DNqRLscjK/5qimbaS0D5vhfi3srPST1J7OTc3bgRvLu/DNBfnpiZzzoAqiheirZJrRk8QsaWZhmNAGbOniG0IB408wEko+jEccWlW5MNq0M7mq2qQSIq9FE5lFkg29TQ3Lk2FtqPVowEF2zHmfoDldg5QctuPHU0qSei2TnUcV5JJqCmVTgVNRBxuHVwYzTfgbrMup/r8NGCoUTuvQGMeIBnQFKc5v6HNBAIHoLKU5gZUoLfBit5jGb7jHmtoK+gepZ9baKMu1jgp75GDPxn5B5GhJjZdl7mccsK1Uwf1HtrqCjs/GIVs9TwIO3plhD89HQhhaEdHRRQ3wLiCNNZlgor9Ij0orrQvl8tInHUhVvnhOv1O+kTisZvTtTBmYTRrWAUZhm15ahfx3IMT60b/OxwWquJWxcTByASJBUhbLStLOWqCLWGs9p5lXcCvevZtY/cAQgd+OTECUIPAgaFbA==
*/