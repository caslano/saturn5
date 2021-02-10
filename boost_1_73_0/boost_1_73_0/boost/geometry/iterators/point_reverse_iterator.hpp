// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_POINT_REVERSE_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_POINT_REVERSE_ITERATOR_HPP

#include <iterator>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>

namespace boost { namespace geometry
{


// MK:: need to add doc here
template <typename Geometry>
class point_reverse_iterator
    : public std::reverse_iterator<point_iterator<Geometry> >
{
private:
    typedef std::reverse_iterator<point_iterator<Geometry> > base_type;

    template <typename OtherGeometry> friend class point_reverse_iterator;
    template <typename G>
    friend inline point_reverse_iterator<G> points_rbegin(G&);

    template <typename G>
    friend inline point_reverse_iterator<G> points_rend(G&);

    inline point_reverse_iterator(base_type const& base_it)
        : base_type(base_it) {}

public:
    inline point_reverse_iterator() {}

    template <typename OtherGeometry>
    inline
    point_reverse_iterator(point_reverse_iterator<OtherGeometry> const& other)
        : base_type(other.base())
    {
        static const bool is_conv = boost::is_convertible
            <
                std::reverse_iterator<point_iterator<Geometry> >,
                std::reverse_iterator<point_iterator<OtherGeometry> >
            >::value;

        BOOST_MPL_ASSERT_MSG((is_conv),
                             NOT_CONVERTIBLE,
                             (point_reverse_iterator<OtherGeometry>));
    }
};


// MK:: need to add doc here
template <typename Geometry>
inline point_reverse_iterator<Geometry>
points_rbegin(Geometry& geometry)
{
    return std::reverse_iterator
        <
            point_iterator<Geometry>
        >(points_end(geometry));
}


// MK:: need to add doc here
template <typename Geometry>
inline point_reverse_iterator<Geometry>
points_rend(Geometry& geometry)
{
    return std::reverse_iterator
        <
            point_iterator<Geometry>
        >(points_begin(geometry));
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_POINT_REVERSE_ITERATOR_HPP

/* point_reverse_iterator.hpp
o64Qi2qDgkqK6hSjKMKLkvy4AqCSaFiP6LhgPdL+GaiDIJUMoFUqmloFGLwoUUw7ra5cs9atjmiAi82te589gN+3GdatK1QUMqvtGzEW3hR90/5NlVCHV8Pr/qB30u92VrL2QlW0L4YfXYuHfU7SNqO2RZ9BsI2ns5qdoKNqzwihqzxomIoVhGQHxeKpopPSfOJaKysNeh+658daVpBqu/y9QWDS5MS1/laTjWRgikwWxjo4kile/1S/yoAdotmo7+iSSHJJQPO2UUF+MO33SwZD5TczFrVMKJP7byTCTXAk7sDGMJOEAKtZb+0WiVhvvfh7Iuamvd5aTvC/m8B48PgDsBNP3EGgAuOFvV3g1RM80sEA03PHIQSHrLG928yN8RCb9dnjd2N4XF/GubxirYbKDfSO9Qq2o8TCMusWlNjScFLDbe+pBr3YX0FAU/6WBDhEy0bzf0Ljk7Y6niJ3oxZ+LXlGUSqbg18d4g5hr9b2IDGcDiCBV2YC+7vvzgR2+ngKg8ai5OeeNZWBsIAOBU0Q30wE3sMWbGeLLOw55kLP6RQjtIECSGM/JfiAjSlS5hYMyAvyPM2F/lkdXnah6aADr1h8k+GbLDrKq7XqK9qLVSK3daB10B6PMyeFmChE54SJsI86MUKEmG8z
*/