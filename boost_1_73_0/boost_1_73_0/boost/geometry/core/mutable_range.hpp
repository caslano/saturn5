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
2/Zh5x217uW8aZ20D1vQsCDcIDo7D2Ok2t+gW1FfEi8FLi10Hfg9LyTlaTfIiMgrT2gmDoIsV8+ULYKsmJlpfRayCIiQaZCDYYAL4ztKozjv+61QxjAcJumNnwFpvfBsfG7GAzoM3Hv4bH3ubyrqx/j1uHP0K3zTtKCvagMSuL+m23N/M/nt1m6nfXx8dFwtURcXs+h72MkbammtYWudnB596OztHxzg5Jtcax1GLcuDPOoqTlPIpZ1sfIYiLuukYdBb7F4EQJuzcb8fpk1TDv+xX+IoD4dZc26i+MefyyTqqSdRDCMVBsOmOkuSgXpyEWTYUGNrDsetHXcTGI1sGcfDRy7krE6cjKaiRqCDPEz60/HiIYWek2B/gn8BGd02ZSb9fqF9bGVxYsUC0i/Oovyvw7rQOAjT8PnGf5RoGoU70+2PhxzruyL9x8SBthVh0QRc8nTc1TNI1zdwss9f1bb6FyD3r4WzKA7Sm4VmiZubJf66bVKNn4Fz7lL+hV/eMl5tBR4aUUWwSylR1PtjnMC6vURSErUbAeGPIo5/yBb/q3181Dn8eHDQVFUfb+duWRa8oSYZRhSfK2pFyAUmPHEGY4d0hgYWWm92dtt7b9/t/89fD94fHn34+/HJ6cfffv/Hp/8KzrogJ88v
*/