//=======================================================================
// Copyright 2005 Trustees of Indiana University
// Authors: Andrew Lumsdaine, Douglas Gregor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPH_SIMPLE_POINT_HPP
#define BOOST_GRAPH_SIMPLE_POINT_HPP

namespace boost
{

template < typename T > struct simple_point
{
    T x;
    T y;
};

} // end namespace boost

#endif // BOOST_GRAPH_SIMPLE_POINT_HPP

/* simple_point.hpp
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
*/