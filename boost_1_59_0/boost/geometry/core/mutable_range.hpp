// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_MUTABLE_RANGE_HPP
#define BOOST_GEOMETRY_CORE_MUTABLE_RANGE_HPP


#include <cstddef>
#include <type_traits>

#include <boost/range/size_type.hpp>
#include <boost/range/value_type.hpp>


namespace boost { namespace geometry
{


namespace traits
{

/*!
\brief Metafunction to define the argument passed to the three
    traits classes clear, push_back and resize
\ingroup mutable_range
 */
template <typename Range>
struct rvalue_type
{
    typedef typename std::remove_reference<Range>::type& type;
};


/*!
\brief Traits class to clear a geometry
\ingroup mutable_range
 */
template <typename Range>
struct clear
{
    static inline void apply(typename rvalue_type<Range>::type range)
    {
        range.clear();
    }
};


/*!
\brief Traits class to append a point to a range (ring, linestring, multi*)
\ingroup mutable_range
 */
template <typename Range>
struct push_back
{
    typedef typename boost::range_value
        <
            typename std::remove_reference<Range>::type
        >::type item_type;

    static inline void apply(typename rvalue_type<Range>::type range,
                 item_type const& item)
    {
        range.push_back(item);
    }

    static inline void apply(typename rvalue_type<Range>::type range,
                 item_type && item)
    {
        range.push_back(std::move(item));
    }
};


/*!
\brief Traits class to append an element of geometry collection
\ingroup mutable_range
 */
template <typename Range>
struct emplace_back
{
    // When specializing it'd be enough to only implement it for one argument
    // because we'll use it to pass one object of type potentially different
    // than range_value but which range_value can be constructed from.
    template <typename ...Args>
    static inline void apply(typename rvalue_type<Range>::type range,
                             Args&&... args)
    {
        range.emplace_back(std::forward<Args>(args)...);
    }
};


/*!
\brief Traits class to append a point to a range (ring, linestring, multi*)
\ingroup mutable_range
 */
template <typename Range>
struct resize
{
    using size_type = typename boost::range_size
        <
            typename std::remove_reference<Range>::type
        >::type;

    static inline void apply(typename rvalue_type<Range>::type range,
                             size_type new_size)
    {
        range.resize(new_size);
    }
};


} // namespace traits


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_MUTABLE_RANGE_HPP

/* mutable_range.hpp
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
*/