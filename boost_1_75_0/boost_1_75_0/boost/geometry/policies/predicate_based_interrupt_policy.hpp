// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_POLICIES_PREDICATE_BASED_INTERRUPT_POLICY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_POLICIES_PREDICATE_BASED_INTERRUPT_POLICY_HPP

#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template
<
    typename IsAcceptableTurnPredicate,
    bool AllowEmptyTurnRange = true // by default, allow an empty turn range
>
struct stateless_predicate_based_interrupt_policy
{
    static bool const enabled = true;
    bool has_intersections; // set to true if there is at least one
                            // unacceptable turn

    inline stateless_predicate_based_interrupt_policy()
        : has_intersections(false)
    {}

    template <typename Range>
    inline bool apply(Range const& range)
    {
        // if there is at least one unacceptable turn in the range, return false
        has_intersections = !detail::check_iterator_range
            <
                IsAcceptableTurnPredicate,
                AllowEmptyTurnRange
            >::apply(boost::begin(range), boost::end(range));

        return has_intersections;
    }
};




template
<
    typename IsAcceptableTurnPredicate,
    bool AllowEmptyTurnRange = true // by default, allow an empty turn range
>
struct predicate_based_interrupt_policy
{
    static bool const enabled = true;
    bool has_intersections; // set to true if there is at least one
                            // unacceptable turn
    IsAcceptableTurnPredicate const& m_predicate;

    inline
    predicate_based_interrupt_policy(IsAcceptableTurnPredicate const& predicate)
        : has_intersections(false)
        , m_predicate(predicate)
    {}

    template <typename Range>
    inline bool apply(Range const& range)
    {
        // if there is at least one unacceptable turn in the range, return false
        has_intersections = !detail::check_iterator_range
            <
                IsAcceptableTurnPredicate,
                AllowEmptyTurnRange
            >::apply(boost::begin(range), boost::end(range), m_predicate);

        return has_intersections;
    }
};




}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_POLICIES_PREDICATE_BASED_INTERRUPT_POLICY_HPP

/* predicate_based_interrupt_policy.hpp
EdZ7ZvZ6dPZmzgSRqEu9ioW3GpP6zACoDl0wemeYF/M6m2WKnlDVN6tKG/ycQas6jpMGNm6HT7y4ZrzfVawDLqATkug5wzF6ZJBUruXU3N6yhj/4w6locQqaPhUEQ5AIG4o+maM4EOcMsOgRVVnx/UrfnFyqxz5j7L1n6qG+5tVGiTR9FosLzKe3cLhiogJJ1uRI0PwJQKhOq42dqvqBXZB9e4JY1LZPM7jc0cVUF36Ihey+KspfwG6i2pLEbha7iv+ApN2X3kAREXI5I7GyHV5VmLRIb58c3Y0SKAhKwbGJlzeXoEdH+BFhnVFJEPXydeWyE7g/oHbZ9k2z+ayHerM9taFA/2rZZf12H7K2RzYAn6DusLSg1inSIroz6FyD9tCmZpQiPzq/BijprJIkEs6rKBW0TkJytsxuNmN7ImEcYwL1kfLdIWLKN+znlGOPTTQpAZqs1jfs1eljIB6JlEtrg6wAgY74Me8WI+XuWrFeepi5cveI2PhezgY6I2S/htZJ2vDhaq/BvVYUfHYMjckwkPqecNTdOn+3bU4P2XzqWEtQF8XDElmPk5ZjOrk7Ftux4QSGuo6fJjVWdyld4ow/vHapEt1ivlyYGHrHoKFXpTmMQF71pc7rbUTbR1z8iuvzfwa8U7837NYVjVo34lJVlKBi4YfQjA3vIt1imwgBkXWnIG/SbwWC9x8EgsM0cGv8XzAuu1amnwRf
*/