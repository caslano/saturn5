//
//=======================================================================
// Copyright 2002 Marc Wintermantel (wintermantel@even-ag.ch)
// ETH Zurich, Center of Structure Technologies
// (https://web.archive.org/web/20050307090307/http://www.structures.ethz.ch/)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_PROFILE_HPP
#define BOOST_GRAPH_PROFILE_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/detail/numeric_traits.hpp>
#include <boost/graph/bandwidth.hpp>

namespace boost
{

template < typename Graph, typename VertexIndexMap >
typename graph_traits< Graph >::vertices_size_type profile(
    const Graph& g, VertexIndexMap index)
{
    typename graph_traits< Graph >::vertices_size_type b = 0;
    typename graph_traits< Graph >::vertex_iterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
    {
        b += ith_bandwidth(*i, g, index) + 1;
    }

    return b;
}

template < typename Graph >
typename graph_traits< Graph >::vertices_size_type profile(const Graph& g)
{
    return profile(g, get(vertex_index, g));
}

} // namespace boost

#endif // BOOST_GRAPH_PROFILE_HPP

/* profile.hpp
YqsMW/FD0u+pEvL7LckSaWI0KlLkqYKOtAoWzNQRkX9nCT6liqxB4X9nCcczeeN52R95uncQ2zW61CKee2o2n9eVZcCBbXmKd1PhIdza+MzL0Je//CeXB5N6Vi/dQeaL36CwoIi7PebiRMtEmg4hHLAdOBsgHchGvzr9HHF3P17xIvUMUxZm+UN0csYmwYCwNEpJVqjrkhEr/4nIy4RKxpLlU3NVF0Mh5Gci2ypc6DW1gYa6WtNydFlV4xwFwHBTm/xF/I+Yk6l/eErGjR8OIrWlX8mLmbhE5rdh3Tl8msm8Pv6Z6FkQc5FXWJbGCFAFiWQzI/h36aZudxYfy5oHPadELeFpK/04gNpKRCYHxlbgqmcutWdtQSg263fxetK0vf43j5mWBIgxnmulsrGgxWd3IcPUg6BCe9tpu/GtRK261sSIWXHv97npBO5/Hkg6WRgZD+JJ6aw/fuR0MTkROhA7LKDwLq5iOb2ZOQC+CHQj3xyJ/PGdMULfNPwNL5Zg7jI8xRBxgsz5Zg5lDsPkDz3Ry30Nyek3nOgGIUrBPwfiQrLecKKtvMnCBzoWHw1MB7MFs4W0DmgP/JQN4u+5GuAb8N012BXa9TVDcQn7lJW0gZV+lFxOy2mg+8aHuQ25HtUEbdOqxX7Ub7xCTKym8udG+c3d9f3FRtiWRv/1nQ9ssMAYBdbFc5oEQTPy7WA7vEh6DA05fh8oFBbi
*/