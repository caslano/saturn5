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
GMf5RJFSyKMr5CSW7jqlSwBXSmBju6vOZZ1jkPsOBAR7J0smGrao+oSkvVcStPzFulc94FO0wNaUmdb79uapnCa0iLzeYzTl45j6+OO96e8CWNBeswhkeZorBWrjVGXFlSUsnbt8vdrUCMWMF5Nj6e00R7+PPsejr6Ufu4TgrAj1YyrPnDd6DEXfbXTPYHTglsEsZeyGBBSDH5xyxC9AORKCebY1G8XU0JKhA7PGXrafX5/fgRnsDzVSwm7kkFY=
*/