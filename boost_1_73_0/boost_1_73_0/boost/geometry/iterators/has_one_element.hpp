// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP
#define BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP


namespace boost { namespace geometry
{


// free function to test if an iterator range has a single element
template <typename Iterator>
inline bool has_one_element(Iterator first, Iterator beyond)
{
    return first != beyond && ++first == beyond;
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP

/* has_one_element.hpp
CfU1LaifnL8hoOe0BnXsMCUbV6EFcWGO+ZnOT6gA9CbcuJjeYrp8i6GnBb4FbVur4euSvSva31oNbQ3pyFDDIXSRuZZCdwtzYv8BCK2kEFodETr7hjB7bq3C7LmpCn1/CkL4HryHQrhZp5TDGFZSaCNzdyrsrqGYOfiOQz8pZl7A/jXygpvZyLzgCj2ZlwtUMz6dQ7iZpox5PTwmN1IIh/xl6DGXGd9Wl+m08D2f7eQ2Q2e6Tblz3KbclW5zkUM=
*/