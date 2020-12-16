// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_ITERATOR_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_ITERATOR_TYPE_HPP

#include <boost/range.hpp>

#include <boost/geometry/core/interior_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/iterators/concatenate_iterator.hpp>
#include <boost/geometry/iterators/flatten_iterator.hpp>
#include <boost/geometry/iterators/detail/point_iterator/inner_range_type.hpp>

#include <boost/geometry/iterators/detail/segment_iterator/range_segment_iterator.hpp>
#include <boost/geometry/iterators/detail/segment_iterator/value_type.hpp>

#include <boost/geometry/iterators/dispatch/segment_iterator.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace segment_iterator
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct iterator_type
    : not_implemented<Geometry>
{};


template <typename Linestring>
struct iterator_type<Linestring, linestring_tag>
{
    typedef range_segment_iterator
        <
            Linestring, typename value_type<Linestring>::type
        > type;
};


template <typename Ring>
struct iterator_type<Ring, ring_tag>
{
    typedef range_segment_iterator
        <
            Ring, typename value_type<Ring>::type
        > type;
};


template <typename Polygon>
class iterator_type<Polygon, polygon_tag>
{
private:
    typedef typename detail::point_iterator::inner_range_type
        <
            Polygon
        >::type inner_range;

public:
    typedef concatenate_iterator
        <
            range_segment_iterator
                <
                    inner_range,
                    typename value_type<Polygon>::type
                >,
            flatten_iterator
                <
                    typename boost::range_iterator
                        <
                            typename geometry::interior_type<Polygon>::type
                        >::type,
                    typename iterator_type<inner_range>::type,
                    typename value_type<Polygon>::type,
                    dispatch::segments_begin<inner_range>,
                    dispatch::segments_end<inner_range>,
                    typename value_type<Polygon>::type
                >,
            typename value_type<Polygon>::type,
            typename value_type<Polygon>::type
        > type;
};


template <typename MultiLinestring>
class iterator_type<MultiLinestring, multi_linestring_tag>
{
private:
    typedef typename detail::point_iterator::inner_range_type
        <
            MultiLinestring
        >::type inner_range;

public:
    typedef flatten_iterator
        <
            typename boost::range_iterator<MultiLinestring>::type,
            typename iterator_type<inner_range>::type,
            typename value_type<MultiLinestring>::type,
            dispatch::segments_begin<inner_range>,
            dispatch::segments_end<inner_range>,
            typename value_type<MultiLinestring>::type
        > type;
};


template <typename MultiPolygon>
class iterator_type<MultiPolygon, multi_polygon_tag>
{
private:
    typedef typename detail::point_iterator::inner_range_type
        <
            MultiPolygon
        >::type inner_range;
public:
    typedef flatten_iterator
        <
            typename boost::range_iterator<MultiPolygon>::type,
            typename iterator_type<inner_range>::type,
            typename value_type<MultiPolygon>::type,
            dispatch::segments_begin<inner_range>,
            dispatch::segments_end<inner_range>,
            typename value_type<MultiPolygon>::type
        > type;
};



}} // namespace detail::segment_iterator
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_ITERATOR_TYPE_HPP

/* iterator_type.hpp
Z211uvjUHRp7bq735ftNZ29aqA95ys43jZ1sjUd34n0F5oqjiPeW5sR2N3bwk8J8kLuWyXHah4SE11eMxOKGPtEwJ6j9wll2htry5hlzXJb+hbSOicJe9+Sae6q55ylzvCh9bVobzzxllmxQOHaBTxo7lemr0jS3w2oP8s5Xtml2pr1OuHI8j+Nd5nhp+tfSjpGOrS/sfkpN/SJ2nmSN6qf53vg3O5/5cXNvVfoGrtyFWZXaJnRC2ln0saeGlqf1sXs3Tcq2ZV9Meuii8nSfcWdG+piUEaGL03qr7ebed7InjZSTSKL12N7TItfPik1Dnj1SXjTuzid8vPux1ISbGrCjfS/+auwUpdeleductPo9bcg+xv8j4p6rS2StN/JmZM3+z3FfRurnO2W0dtYP30y67a90uxzT5GkDrfT8/jzmSswXMKtUn16FuRpzDWa1rn0Rc63q9S/p+pqI0fnrMF/GfAWzFnO9zq21xKj8vAFzI2bdodtjyk8ZgHrP+Dt6XKHjTtTtec7vPkXThw0J6Vzf6Lk899xvT3PPDT3TPZcTPWfvPSF6Ltc992o/99wQe+/90XMj3XM3Rc8Nd8+tiZ4b5p67InpuqHuuNnrOPssF0XM57rm/9XXP5Vn3Xo6es+79InrOhsF3ouese9fYc7kj3HOl0XPDQ2pDnWbPjdCclNhybr5PObfAzv2n/NC5Cjv3n/JB81Tu76vxJp1jy8Ic1V43ak7kdZgTOJdp6x8zG95TFpba+qG3YyeUEZ0Lqfs6xeZbT34bY65fSDlzPvWi6nzlhZswNyjNX3OE8+GdcCr1+k0pmXykunWF/LbgdOs33hlwI1rOV3rrv2XG3pJQfnQtbN3bJb5ckv/WmOslocH8r/admeO5Xn76esR/hzEfT3WY/GWeK8Zv8zvJsubZnYk5Drv50TqstrGh3us3Uw/KH7I33rf9M9Vz3bMHn62Hlptrx5h3mEznYUOXmzVsOkQWPWzdvkP7/pEf7f3aV2oDzDZuDI5vX0mj2Fzvb8pbdy7gzYcxF7BTTHrAzzo3MqYNFhuWtVrkbi0iPcWMSFj2tmFZx5xOv/aA7Jxm0/diczzB7PdQa+poZvpHw1X2qT9VR5eb40Idp4S+dqpd941w1/1VNly4P9pvUMVxqTmekhKzLomnnfo9c72tXX/oLnP8uo5j9JSe6xeGPPXwV5z7U9pF3bdtlEpzrWvK3yPvvOqDmG/c49jYIfTMcU9d1zHP38X7vEw6JoDreVm2fRkXG7d7p7xn3bb3xr/bqr6/wdxz0MxFvpA0OaWz6u62Kx+LpKPhpKMM7DcoD35TdeqtMmt9zHWHVQY5Jc2WU6N1Zs2ptny3dcj50XO2DpkUPWfrpBHRc7ZeyY6ey3Xri6d62zqY45jyws7fJQ1ybNKgOVds6xClK+qGtqfauiHmPSpdC1jOUb7Ih8dEwiXL5gu7HoNP3sBebN64zxwPSLFlQmzewH5s3rgnKzZv7O7VYt7g/ti88QNznJswb7yTFZs3Dprj3+g4qudJ+3atr4nmWqpNr1vNve1TvuZJ+/f3ikn7HB867Ufcvj/iFv/WxLuVMO2/ZO55Jb7eVT5+0Vz/h8kbDZR35V3dvPF5s/9KHnmjvSdvbLDtTa9RXjnsfOGfJltlHjpNru8VmyZPV5pcrzQZQQeZXOzsdd7tI/OMTRgM5hz18ByOlR5dO90Oe81M3OCZ5AbP9A/ut89k58Ummi+YaN5qonmxieazJprHmWge7ZHPc/WfN3nk81+vTYmc7/taTtOmNV9Ye/eHp2w+6fHMKxPNs0w0XzbRPNQjn0ebYL5ygnnGiea5Hvm8Vf/5tUc+rzfB/NoE82I=
*/