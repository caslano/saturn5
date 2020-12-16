// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP

#include <cstddef>
#include <functional>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/geometry/algorithms/dispatch/expand.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace expand
{


template
<
    std::size_t Index,
    std::size_t Dimension, std::size_t DimensionCount
>
struct indexed_loop
{
    template <typename Box, typename Geometry>
    static inline void apply(Box& box, Geometry const& source)
    {
        typedef typename select_coordinate_type
                <
                    Box,
                    Geometry
                >::type coordinate_type;

        coordinate_type const coord = get<Index, Dimension>(source);

        std::less<coordinate_type> less;
        std::greater<coordinate_type> greater;
        
        if (less(coord, get<min_corner, Dimension>(box)))
        {
            set<min_corner, Dimension>(box, coord);
        }

        if (greater(coord, get<max_corner, Dimension>(box)))
        {
            set<max_corner, Dimension>(box, coord);
        }

        indexed_loop
            <
                Index, Dimension + 1, DimensionCount
            >::apply(box, source);
    }
};


template <std::size_t Index, std::size_t DimensionCount>
struct indexed_loop
    <
        Index, DimensionCount, DimensionCount
    >
{
    template <typename Box, typename Geometry>
    static inline void apply(Box&, Geometry const&) {}
};



// Changes a box such that the other box is also contained by the box
template <std::size_t Dimension, std::size_t DimensionCount>
struct expand_indexed
{
    template <typename Box, typename Geometry>
    static inline void apply(Box& box, Geometry const& geometry)
    {
        indexed_loop
            <
                0, Dimension, DimensionCount
            >::apply(box, geometry);

        indexed_loop
            <
                1, Dimension, DimensionCount
            >::apply(box, geometry);
    }
};


}} // namespace detail::expand
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP

/* indexed.hpp
XkYpUq8PBBxd9z8WnEj3aloxvvOBEqeqJNN4TojLqsRz8QyHqxL7R39+UA4ndo5S3YjaAp9fnyfqFTV+5wblZjufw2c4skmhP5uex3kVaZ+bTZurEL9PkuVwVQjKVzWbWywRqTYxB92c46N9s9rP/ia1Ad+gke3ffs82stt00C2JbxwPZfHoJD3r5zGFS05zbsOPqxzEkzkT9E+VZ7pujuupiMOb22UZUTFCXmZ9vV2EJ7ll3CHmRmXcMeaoZdwp5kVlfFbM4TLKc0Kex/erzI8w7ZiO8GNInoI/l3F5D4dPZxfGk6nS2VXyHN7gnTPUBrR7U86P5n3xGiz+7ujy9FLBo5E+vDtlj/kSD98nP0yEze793kuE43MycZrZczJ7y3BmtEbEg8WBsWqd+5p9Io7tv0BqzY0HXW6Z8VlZHCYpl/J9gDxyMeesDIezKs5ORByeg07LqeXnR04BWjUOf4v16czJlDndgMFnWtQykdp47Ng3E4f/Ujnqbvs2IzfnuzXLN2o2V8BQPxTlW99AInxEMj5qQYWq2NO6v8DZbxynQ+Wiz1muzZwm8CgLov86SKaRqHUD37MlJ7T7tBzYXU9L2l34tTIcbg5stxdlObrd2NeV5cNusi9bwH2ZPN7IvizZ1zHOPljCefyyWyngZA/mtCeRjtb1dK/tM7tDpD1XC0zruyYFnu27egSW7btGJIYdJTLcsvmMcb8W54dywnPCEyRmintMrV49qTyAvWjBfNBYX+4leW02XDyFpEqFMAubCsN7hWuSTzsp+E0UgWV2UHjOhODInRPUZuI05Kd7ac+XCd1qbfvIAB8P7NIhMGr3rPsNMu2kcd2/OgjXmO4bC1Pzfc56wY/3QbD+ThW8zN4Hfgcx4EBBwDLjPHq1dIIXvWuKvpF9MzSDl10k8iH388jekQcR49fqhh0O34PubXlmU34t5FfdN3efOr8/luyNcL5IpjVy3xDhYd+wBrgETZXJ7G/asrZjZe5+xple58wF5tvEaSzPBm/C16O97flTVR9DwvZiB6HHe2X7SDGzhGe8JMPzzkLeVyjweEdh3B7amw5Xa0l968jn8B50rnHnpupP3r1UDwb6iu6eQsj47inG4runGIvvnmJMv3uK8fjuKcZM46d443DYHhOFfT/j+XdTAeM7KJTzkMCxAguwixmzK6/GzvJZe9RRiRR7PKrW31fL+tk/StVX4K+R+Kby1mz9Lij1e1SEL8Y4YmmiPHQrqXYHvVq/BtL0+GbSZe3NpaWfY/6X6ufe0+2hon47WMEzx/leQHSMJu5Qp3zxAeswX0+rNi2nfWx4klnWr71dnpjk8zs7xigCEf9chYNfLf57cYhTFZZ3Mmi4iaFZnZiUI508c1+tXgxRveCTs0F5MhimzXKsOcmFpYBCj1KOQCLO2R5jFTa1n50P5Wbvp1fL90JRhux9Cwc4jIDm9tVvpuPV8fxgN5kPnm9CV+F3eLdXjjn1iMMHpx1njDgxQ95B7Nc6jDqbbQVGQpyda6Ze1TCxUvvPfYLytmb321M451yK964TTqst3gM4Nc/vBWTdvUPlYXoj1vVnqRya5GKRwPHF6fLGehHfS0OOtkHex3eYzsVoDp1MGR/FJPO2VONlfJ9HaBy/YG/srjdrdySv2X3+dHZHOLa7Yifg0k6q7sEJdK/pExxdn0eoHNZBI2eHhQ5quE9S0cMCoYfGziMHcS5dpsT5kv8pzqXtbUqcbf9TnONjFWX8X7xvs+emKc68M0lL1b5ziO0YHUlynFLE4UVDdBap1sBRpGbGglreWaTD1PJwG8kcRXpMOYtUk0eRGJ+M8HBv9UiEG8eR1l/GR4zidhgfLzqM/Ug=
*/