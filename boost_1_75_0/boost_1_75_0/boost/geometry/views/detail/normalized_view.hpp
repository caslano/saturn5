// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_NORMALIZED_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_NORMALIZED_VIEW_HPP


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/geometry/views/detail/range_type.hpp>
#include <boost/geometry/views/reversible_view.hpp>
#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/util/order_as_direction.hpp>

namespace boost { namespace geometry {


#ifndef DOXYGEN_NO_DETAIL

namespace detail {

template <typename Geometry>
struct normalized_view
{
    static const bool is_const = boost::is_const<Geometry>::value;

    //typedef typename ring_type<Geometry>::type ring_type;

    typedef typename detail::range_type<Geometry>::type range_type;

    typedef typename
        boost::mpl::if_c
            <
                is_const,
                range_type const,
                range_type
            >::type range;

    typedef typename
        reversible_view
            <
                range,
                order_as_direction
                    <
                        geometry::point_order<Geometry>::value
                    >::value
            >::type reversible_type;

    typedef typename
        boost::mpl::if_c
            <
                is_const,
                reversible_type const,
                reversible_type
            >::type reversible;

    typedef typename
        closeable_view
            <
                reversible,
                geometry::closure<Geometry>::value
            >::type closeable_type;

    typedef typename
        boost::mpl::if_c
            <
                is_const,
                closeable_type const,
                closeable_type
            >::type closeable;
    
    explicit inline normalized_view(range & r)
        : m_reversible(r)
        , m_closeable(m_reversible)
    {}

    typedef typename boost::range_iterator<closeable>::type iterator;
    typedef typename boost::range_const_iterator<closeable>::type const_iterator;

    inline const_iterator begin() const { return boost::begin(m_closeable); }
    inline const_iterator end() const { return boost::end(m_closeable); }

    inline iterator begin() { return boost::begin(m_closeable); }
    inline iterator end() { return boost::end(m_closeable); }

private:
    reversible_type m_reversible;
    closeable_type m_closeable;
};

} // namespace detail

#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_DETAIL_NORMALIZED_VIEW_HPP

/* normalized_view.hpp
pkyWtMxYGBtG8beUr2NxkW+0eD0wJWdus8PDFnP8q56jbdtjZVfCg0L2Sokpo2b8De9oaFrD4BTXQqgjTsvl89qLafy2FrOvWXM03mhfk2qy3n/q+mGR4Mibl5sbP/PiTIavrzVJygKzYU5GO2MKn5KC6pRwga+VXBaJPse4UDinkIiZfyUZx8d5jopXxNeYrExL92VB7hNLVATxIq0g32GBUF8KDWditVX8Y6BQkaZsb7PiqKN+u5D9UtrsCiyFA5Y/urLkz+zw+hwJY/64TLre+U7r5JvkV/YONbqJp2DeuAaB9HDq9x4CZlQeybYx6bNoRYKFLjibPHnpFQoZLp7kE1E4dVYe7p63nl+gZUfyVjxrvC+/fcGQa52fqIwLUhNZWK5hmaNYJsI+OXr10rIoDBACfJtNU2ejvd/fi+15vSf3svXU61yeiTaS+jndWwqfV3IXQdRHaG9RVTFR6du/hKIOaZr1F8eeH0cMK79KHvm2nr+XRCA8nOaPM7ov/w4T68CZMtgiSiqFt5mMIsQ3C6MhSp2T14PIrGmWgNWMeNfNS3BQ0CBFiDZKY/LV7QvRa5zwr7X5CmZjNPVmKJPimaXox7PbQglqSaGllVM/xBoGtoKTBtAVqCnEyZ0HSipRSCM12SM1FajTAEub33CaLfU5uNT0qFukqyP73b33qnwUMRvUJbxPT5Y3+zeGc/vlTTVUTRMVVJ4F
*/