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
BxY+eDSPK4kFW4tY9e4NsTJcXVAOwlJy2vdqjxYKrLYbuBi2J4b3tBZ793YKzt3GlIKACEjqF8grS+r3Ccd4jG0EMvsteEg9aLQYaJca9MDHXrLegCPSjBbWaIu5nYt1DTQF4pR8QXsJe17YrwcapiHXmQiN0+oQd6FjMnO5C0iF3Ok9fnhniFCRSgUHDE3ffNkpdXvfejZ4dlREHHTMoWaIbNd6tokgsx1bXNkMuGIT5bCHhKsOgjIvQO5cwse11IFtyIQBiPOOoa+BpB/XWsBemRhub1l4R2U7qqn7h9UoeH04srz3PCIjiaTZL3qyQZRgcd87/2gTxxEI5PYz2C5g24KgB6CZj0D0W1uzLbZuieDDqDXEiL6jj89uLJrKfi9kVPGTKOve2VKVL8sOpvp2Gz1rAiVTUYdzJ1fhF0QWKY/eD2se247/bthR7mc6g6aVLhRhqb0eV6hEbA4HaT30i/56nvObYgFQYNbsskpU5Tb1WN/T18j1/JrKxTZNac3+LL7zquS6ATExPE/cYtfGd1sPVUlcHBwkaDGrLbP+RrEnuqazAPBOmO/zs4SsqPjcFUq5CImuExcZGHY4PwrslFnem3yM/8/5y7jdP7q8TfJkV7HBbXAL5h23lp6llsCwtsvzjVc3v6jBorDWKtFgL4JVAwhxSrNSTM3kOlwGRwXCcarsg7dTNf10QKWXnGdiMJQXJjHs3PZt
*/