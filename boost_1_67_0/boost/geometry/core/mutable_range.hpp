// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_MUTABLE_RANGE_HPP
#define BOOST_GEOMETRY_CORE_MUTABLE_RANGE_HPP


#include <cstddef>

#include <boost/range/value_type.hpp>
#include <boost/type_traits/remove_reference.hpp>


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
    typedef typename boost::remove_reference<Range>::type& type;
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
            typename boost::remove_reference<Range>::type
        >::type item_type;

    static inline void apply(typename rvalue_type<Range>::type range,
                 item_type const& item)
    {
        range.push_back(item);
    }
};


/*!
\brief Traits class to append a point to a range (ring, linestring, multi*)
\ingroup mutable_range
 */
template <typename Range>
struct resize
{
    static inline void apply(typename rvalue_type<Range>::type range,
                std::size_t new_size)
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