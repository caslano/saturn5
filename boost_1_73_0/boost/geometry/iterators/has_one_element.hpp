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
cS1Oc/6/qMrj7GM7/otCG0y5RofzXxpcfdxsLDn/gqj43u40FimtsFHvmJBrdFptSqNi/XGYrJYs7DLtlQ5lwwTL2IIclRGLOiZ30Tss7VTGHI8i2Xq7QWlMvd2CPUztplGeJpUh8Ti92qmKg5jFkWO0K42Jc2KhXuk+5sxx2pTGM5otRqWTEs/1nMZ89XMSR2Wn1ZqTo7ayWtBxiiNqT6qUjiPENBQoTTsiZuPJgtKQNrNe
*/