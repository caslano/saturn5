// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Bruno Lalande, Paris, France.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RECALCULATE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RECALCULATE_HPP


#include <cstddef>

#include <boost/concept/requires.hpp>
#include <boost/concept_check.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/size.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace recalculate
{

template <std::size_t Dimension>
struct recalculate_point
{
    template <typename Point1, typename Point2, typename Strategy>
    static inline void apply(Point1& point1, Point2 const& point2, Strategy const& strategy)
    {
        std::size_t const dim = Dimension - 1;
        geometry::set<dim>(point1, strategy.template apply<dim>(geometry::get<dim>(point2)));
        recalculate_point<dim>::apply(point1, point2, strategy);
    }
};

template <>
struct recalculate_point<0>
{
    template <typename Point1, typename Point2, typename Strategy>
    static inline void apply(Point1&, Point2 const&, Strategy const&)
    {
    }
};


template <std::size_t Dimension>
struct recalculate_indexed
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline void apply(Geometry1& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        // Do it for both indices in one dimension
        static std::size_t const dim = Dimension - 1;
        geometry::set<0, dim>(geometry1, strategy.template apply<dim>(geometry::get<0, dim>(geometry2)));
        geometry::set<1, dim>(geometry1, strategy.template apply<dim>(geometry::get<1, dim>(geometry2)));
        recalculate_indexed<dim>::apply(geometry1, geometry2, strategy);
    }
};

template <>
struct recalculate_indexed<0>
{

    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline void apply(Geometry1& , Geometry2 const& , Strategy const& )
    {
    }
};

struct range_to_range
{
    template
    <
        typename Range1,
        typename Range2,
        typename Strategy
    >
    static inline void apply(Range1& destination, Range2 const& source,
            Strategy const& strategy)
    {
        typedef typename geometry::point_type<Range2>::type point_type;
        typedef recalculate_point<geometry::dimension<point_type>::value> per_point;
        geometry::clear(destination);

        for (typename boost::range_iterator<Range2 const>::type it
                = boost::begin(source);
            it != boost::end(source);
            ++it)
        {
            point_type p;
            per_point::apply(p, *it, strategy);
            geometry::append(destination, p);
        }
    }
};

struct polygon_to_polygon
{
private:
    template
    <
        typename IteratorIn,
        typename IteratorOut,
        typename Strategy
    >
    static inline void iterate(IteratorIn begin, IteratorIn end,
                    IteratorOut it_out,
                    Strategy const& strategy)
    {
        for (IteratorIn it_in = begin; it_in != end;  ++it_in, ++it_out)
        {
            range_to_range::apply(*it_out, *it_in, strategy);
        }
    }

    template
    <
        typename InteriorRingsOut,
        typename InteriorRingsIn,
        typename Strategy
    >
    static inline void apply_interior_rings(
                    InteriorRingsOut& interior_rings_out,
                    InteriorRingsIn const& interior_rings_in,
                    Strategy const& strategy)
    {
        traits::resize<InteriorRingsOut>::apply(interior_rings_out,
            boost::size(interior_rings_in));

        iterate(
            boost::begin(interior_rings_in), boost::end(interior_rings_in),
            boost::begin(interior_rings_out),
            strategy);
    }

public:
    template
    <
        typename Polygon1,
        typename Polygon2,
        typename Strategy
    >
    static inline void apply(Polygon1& destination, Polygon2 const& source,
            Strategy const& strategy)
    {
        range_to_range::apply(geometry::exterior_ring(destination),
            geometry::exterior_ring(source), strategy);

        apply_interior_rings(geometry::interior_rings(destination),
            geometry::interior_rings(source), strategy);
    }
};

}} // namespace detail::recalculate
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1 = typename geometry::tag<Geometry1>::type,
    typename Tag2 = typename geometry::tag<Geometry2>::type
>
struct recalculate : not_implemented<Tag1, Tag2>
{};

template <typename Point1, typename Point2>
struct recalculate<Point1, Point2, point_tag, point_tag>
    : detail::recalculate::recalculate_point<geometry::dimension<Point1>::value>
{};

template <typename Box1, typename Box2>
struct recalculate<Box1, Box2, box_tag, box_tag>
    : detail::recalculate::recalculate_indexed<geometry::dimension<Box1>::value>
{};

template <typename Segment1, typename Segment2>
struct recalculate<Segment1, Segment2, segment_tag, segment_tag>
    : detail::recalculate::recalculate_indexed<geometry::dimension<Segment1>::value>
{};

template <typename Polygon1, typename Polygon2>
struct recalculate<Polygon1, Polygon2, polygon_tag, polygon_tag>
    : detail::recalculate::polygon_to_polygon
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH



template <typename Geometry1, typename Geometry2, typename Strategy>
inline void recalculate(Geometry1& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
{
    concepts::check<Geometry1>();
    concepts::check<Geometry2 const>();

    // static assert dimensions (/types) are the same

    dispatch::recalculate<Geometry1, Geometry2>::apply(geometry1, geometry2, strategy);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RECALCULATE_HPP

/* recalculate.hpp
3jfK5JlwrV/wTPilKh1aN8l/u7BLScz99D0IVxCNPDfUXBw8s/Q4vV0SsT7cJS7FNGUDa49Op7tHB+zF9xRXqLsirxXpSZWosyDKXtcRLe+XdFlvffMaNZ/Bfunvl0LYyJa+aPSU+OHsTwiXBPGUFg5Lf9T7U2/l+Aj79NBN++8d8IPvwA8YJ/aVjBdh6ScV8K0BdcfW3ULm8pB3Ze4R5f8zftnEuwj3Cf1l+MIyhBXvzerM7gM+Hrx1er8NfhSP91/INN8l0izDnyoLhj+rwueq8BkqvFmFj8P5l837ZvU1MK3vI5ODeKOHxP9Y4T+r8I8p/LkK/1OFP0Phf6bweq/PEwq/WcV/kvCLct9JY/oFzfWNNEhfZot0GIL7QE+JMd527AdZg7L4qzEOd3KgLacNobjDnttzC8O9DoCNxF4yC35T7mXu6ZCwZyZjHRPr4bVo05+VayC72ZfKe5dKs3XNB0rRvqj6/dfEV94FgfrN6iHL3G9FXZZRP9ByXfY7lPlnYMsh8dBu/F7F+wPX6UxD9ld3CAqaa+J2TyynicKW5kX2GcKDRvrMSwL/9GTio/Avi/rjauCIzpavV1Tcm9UeoNdcXONH3L94Q/Uv3pwsdcZ5SNjiTtTb08px1knUmzNRxheV4UyT6j+YuOVq/9g7nG8WjzwIb7PfVbSjS6Np/6to4WehtHTZtdSR8eU4mz1M4A8pG4ovrkaeC7xu60sUjdFd04wkmqix1Sw1tpq127t2ct/PM94f11o5PR2zURd8oNrIS3e2zsjO0Y6qlm9ZEm3C4PmyNAmIPtebRzx7frJ66BzWdBqfyDvrMT7hsVExxoAIU/xOz//e1+vslPXZOJozx2uEXHeVivRVkJ7ttXKnqwiTlpv3aLzd6O3pXUzzMZdcVi3HUCuXNDcuXzhjzvRAjiuo1R/jPKxZdLI+FUqfSqVPXOnT6fThcLdpJ8RenBKznil0TBl/rJ09R7mkBLEPfCDEB+LkA3oP6wQ1zjigGvd4lYm3J8pEHY+446p5n6ot77IuOIhwLAd9e13HfwRyboIctGehvHV7Nh5xdyCuSWOduBfArFdjvYf3lk60djyF15eqKLwgjznqReA1ycZf7Pl8F6i83OLRXJ05hoD8Toyj+QYDc/nJ727GRX7u9I5ZvGTlsuYVK5bxqgNDeM1C9kN0H4TmnVvTnr73G2F+37QWsqtZtt1v33ZygujZkRB2XsT9hRtR75ufvjuqBvkwFb42Xu45xp1MJjyt2ui2tlfePfZR1sXoae/kwXqIVUYC5F1W5BfR+syAPrW70Wem0Gca9JkVok9Ph9MFAasH2jCbJj1umiPauJkh+LnVctyGO/YwbkE4vB3KlVdY2zm8OtsX+bhLP+syP0SXIwgW2sbkkRdGRh1kTIvmoe3HcRsQNzytnbSAKNsOERZjdN0XycA3zF89Rl8Ev2isFu83hvIIiz/CW1KN/jNwoFf1XrF3FNd7Bhd+D+Ry6DJX1K9V4rtOfB+JbzmW/RjGRk/4/USEf6bCT6rwTzks+2Go/3lugF4Kqg6+P7phjOrXqXmu40FPOJ4Xs/ei6rkA9AElL5MGiT9J4X+m8G0K/6TCdyj8TxV+rcqfsHapM0ADH1E0J7M/cD7rvHYzviF0YfeJ9wq9LyUfrhkdLKsp5sNvEzEvyae/Ws/7EZR9XPtriZchepQFpj8ZeWz8/PgxWtcR3gahizwHo8vCYJCO53g03akoD1cIv/+c+P6y+L5VfF8t/GsbfPsi4dumz2Lg0o5nVku8S5/0j7Ogy2VqPjOD+5Ngy8B7OOcInhPHEV8l81zCN+Uxd2FemVveuGrxioW20otCch16vujfPVI=
*/