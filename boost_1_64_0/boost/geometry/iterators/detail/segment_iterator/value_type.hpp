// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_VALUE_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_VALUE_TYPE_HPP

#include <iterator>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_reference.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>
#include <boost/geometry/util/bare_type.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/geometries/pointing_segment.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace segment_iterator
{

template <typename Geometry>
struct value_type
{
    typedef typename std::iterator_traits
        <
            geometry::point_iterator<Geometry>
        >::reference point_iterator_reference_type;

    typedef typename detail::point_iterator::value_type
        <
            Geometry
        >::type point_iterator_value_type;

    // If the reference type of the point iterator is not really a
    // reference, then dereferencing a point iterator would create
    // a temporary object.
    // In this case using a pointing_segment to represent the
    // dereferenced value of the segment iterator cannot be used, as
    // it would store pointers to temporary objects. Instead we use a
    // segment, which does a full copy of the temporary objects
    // returned by the point iterator.
    typedef typename boost::mpl::if_
        <
            boost::is_reference<point_iterator_reference_type>,
            geometry::model::pointing_segment<point_iterator_value_type>,
            geometry::model::segment
                <
                    typename geometry::util::bare_type
                        <
                            point_iterator_value_type
                        >::type
                >
        >::type type;
};

}} // namespace detail::segment_iterator
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_VALUE_TYPE_HPP

/* value_type.hpp
GO+S7i83SZcB0GbETGSUKbNE6tlrviFgbTdNjUnTelF3SrucdGzilzFuSdLcJs17tkQ1k52OB6RrHM9dUc1PKh3fIu3LN0e1k5GOXb920zyHDd44nTV7XHFd5bLShvDU8PJI5Aar7eahtdK+JKF2cnTbtnZsb/Tqxno4UF03La+Q7mp/3UA13fT0hjRrNns1546fOvG8QPXcsC3XXIt8rx9tuUjGCTjPurrPSXezJ88mszx2w7dIY//3b5Tu+XMLp88ZPrSksiEpeg9J73Wr58olx38DjnFsv+DVG5IXuN5wt7yX3htuPW7K3WXhuspFy0vKwiybT4W3tE61XbDP4Kal7HZaZ2ST/zMkq369RbrpMbqNtQzYWZSs9JvRXnuUbPRoErtB67n1zWrpfRgTv9oP+hKm0ZXUlFaHk6OdnuHYXn9XnHbl4prShsa6cElNZXmg2m6aWiHtzDubay+hxmmMbPwYqK7r5wPSvTXOz5X19Wy/YoI74LjOk3ZTB8f2oE3NtZk2Ea4x8+wWVZUurg9Y3w3z/dJfs9lHv4QKIkm6Fcc6tlc2181hjPRC4jtgXTcv75Hu0zF5mZeDgPOTqzflOKXpmPgtq64N2H9uWt4pvau94aqNaGudZlTJkoDbUW6cjtG8hXabYrXZklcldLB+dvPQQ9K97a54XeNzyk2GxC5MVnk9UnMaHtgSo08lWLmosiwS4mzVE3D6Gu76XdoFMfE9b+KswknnlRSPmzVumtkJqaGusT7w+sp9hvxOWku3xWcgX9fVLq0POBxGue/8eoYLW36GiqX1DaY4TVZYFB2vifUtP0d5uLahIuhncMPiGT3D3ttbfIbSxoaKkqrwsnBVwM/hhsX8zo7t4hbDIpdICT5tDnLDQs/wbIthkZsU7WLNYRmQ2P/MdQrW324a2CPtVxL7u3rpsnBkd/m6SPMm6PDPc9NAF8f2yMRhUFlTEa5L1rvSc9KvSKy/ONn5kXH95m9hi8+Qk7S4cNPjXj1HXuLnoCEUbBt7uBsGmiMwL7F2aXl5csoC2/+hZ7g6Jk/MnjNj1sSktE9cvy/o7tjutzlel8LHbutcW9pQEXQ7v59bDuoZLvfxO4VQoJpu3p/Tw7G9ZVO8ZtXS0nL+o3XEG059sH524/sJ6a/08TMJPWn5bMqJsu0T3yRyvL10SWNtcrR3Svu22/21aZUGnr+Gu/7uqfdoH+0Jc+ZH0rrtIVoY8DO4aW6XnuHRxM+QlPdpV3/KSepjTazPm3VJZB2WpOjvkv6TifVV3gTb92r9f7Jj+5nE+jn4vibo/hQ3z++Q/hp//cDLOjffjTlF/WYJdCtrgu8vtO+/0t6WQHtxWD3CSdIfowmHDyXWz3Vex5Oj/5D0dyXWz6FyrSutTo7+mF7a86gF/WT4301726V/g79+Uuo6t10xoLfWdYrW8fruzO7L9RVJ0dwgzSc2NtcMvv3qanY+VeNTbo/TLA+6Lnc1V0uzS1zY0oEYsKbt/9dg8M4xbZeiGTOmzi02MVpSXhl0OWL7/6Xdw097UWVVsuqMt6Wb5afLqlNB94+4YV3b17HdYHVjxk8kJd/2dt8Fpf2ym4fmJuebpRvG8/upXeD20c6eVUzBGH35WTw9UF3b/yPdXV7dsrowvbJOW7SS7zvjg9W27z+nqS3m0VaH9JIaFvXDz061FHAc2/cf6adv9ejPcxrg4+n+KS8J1t+ubkG2+p7uitcdlwRdN03fI923vLoTSqvKSpqSotenv77Dx+k1BqrnpuUN0ns2Tq8+XEdijnzYCbq8cLV7nq5v0nHaztqwydB2w3mNtPfGaY9Pit4H0jsQpzcuUD03vzScIesbXb0p44bl5pU=
*/