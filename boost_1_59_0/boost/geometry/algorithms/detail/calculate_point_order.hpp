// Boost.Geometry

// Copyright (c) 2019-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_POINT_ORDER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_POINT_ORDER_HPP


#include <vector>

#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/strategies/geographic/point_order.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{

namespace detail
{

template <typename Iter, typename CalcT>
struct clean_point
{
    explicit clean_point(Iter const& iter)
        : m_iter(iter), m_azi(0), m_razi(0), m_azi_diff(0)
        , m_is_azi_valid(false), m_is_azi_diff_valid(false)
    {}

    typename boost::iterators::iterator_reference<Iter>::type ref() const
    {
        return *m_iter;
    }

    CalcT const& azimuth() const
    {
        return m_azi;
    }

    CalcT const& reverse_azimuth() const
    {
        return m_razi;
    }

    CalcT const& azimuth_difference() const
    {
        return m_azi_diff;
    }

    void set_azimuths(CalcT const& azi, CalcT const& razi)
    {
        m_azi = azi;
        m_razi = razi;
        m_is_azi_valid = true;
    }

    void set_azimuth_invalid()
    {
        m_is_azi_valid = false;
    }

    bool is_azimuth_valid() const
    {
        return m_is_azi_valid;
    }

    void set_azimuth_difference(CalcT const& diff)
    {
        m_azi_diff = diff;
        m_is_azi_diff_valid = true;
    }

    void set_azimuth_difference_invalid()
    {
        m_is_azi_diff_valid = false;
    }

    bool is_azimuth_difference_valid() const
    {
        return m_is_azi_diff_valid;
    }

private:
    Iter m_iter;
    CalcT m_azi;
    CalcT m_razi;
    CalcT m_azi_diff;
    // NOTE: these flags could be removed and replaced with some magic number
    //       assigned to the above variables, e.g. CalcT(1000).
    bool m_is_azi_valid;
    bool m_is_azi_diff_valid;
};

struct calculate_point_order_by_azimuth
{
    template <typename Ring, typename Strategy>
    static geometry::order_selector apply(Ring const& ring, Strategy const& strategy)
    {
        typedef typename boost::range_iterator<Ring const>::type iter_t;
        typedef typename Strategy::template result_type<Ring>::type calc_t;
        typedef clean_point<iter_t, calc_t> clean_point_t;
        typedef std::vector<clean_point_t> cleaned_container_t;
        typedef typename cleaned_container_t::iterator cleaned_iter_t;

        calc_t const zero = 0;
        calc_t const pi = math::pi<calc_t>();

        std::size_t const count = boost::size(ring);
        if (count < 3)
        {
            return geometry::order_undetermined;
        }

        // non-duplicated, non-spike points
        cleaned_container_t cleaned;
        cleaned.reserve(count);

        for (iter_t it = boost::begin(ring); it != boost::end(ring); ++it)
        {
            // Add point
            cleaned.push_back(clean_point_t(it));
            
            while (cleaned.size() >= 3)
            {
                cleaned_iter_t it0 = cleaned.end() - 3;
                cleaned_iter_t it1 = cleaned.end() - 2;
                cleaned_iter_t it2 = cleaned.end() - 1;

                calc_t diff;                
                if (get_or_calculate_azimuths_difference(*it0, *it1, *it2, diff, strategy)
                    && ! math::equals(math::abs(diff), pi))
                {
                    // neither duplicate nor a spike - difference already stored
                    break;
                }
                else
                {
                    // spike detected
                    // TODO: angles have to be invalidated only if spike is detected
                    // for duplicates it'd be ok to leave them
                    it0->set_azimuth_invalid();
                    it0->set_azimuth_difference_invalid();                    
                    it2->set_azimuth_difference_invalid();
                    cleaned.erase(it1);
                }
            }
        }

        // filter-out duplicates and spikes at the front and back of cleaned
        cleaned_iter_t cleaned_b = cleaned.begin();
        cleaned_iter_t cleaned_e = cleaned.end();
        std::size_t cleaned_count = cleaned.size();
        bool found = false;
        do
        {
            found = false;
            while(cleaned_count >= 3)
            {
                cleaned_iter_t it0 = cleaned_e - 2;
                cleaned_iter_t it1 = cleaned_e - 1;
                cleaned_iter_t it2 = cleaned_b;
                cleaned_iter_t it3 = cleaned_b + 1;

                calc_t diff = 0;
                if (! get_or_calculate_azimuths_difference(*it0, *it1, *it2, diff, strategy)
                    || math::equals(math::abs(diff), pi))
                {
                    // spike at the back
                    // TODO: angles have to be invalidated only if spike is detected
                    // for duplicates it'd be ok to leave them
                    it0->set_azimuth_invalid();
                    it0->set_azimuth_difference_invalid();
                    it2->set_azimuth_difference_invalid();
                    --cleaned_e;
                    --cleaned_count;
                    found = true;
                }
                else if (! get_or_calculate_azimuths_difference(*it1, *it2, *it3, diff, strategy)
                         || math::equals(math::abs(diff), pi))
                {
                    // spike at the front
                    // TODO: angles have to be invalidated only if spike is detected
                    // for duplicates it'd be ok to leave them
                    it1->set_azimuth_invalid();
                    it1->set_azimuth_difference_invalid();
                    it3->set_azimuth_difference_invalid();
                    ++cleaned_b;
                    --cleaned_count;
                    found = true;
                }
                else
                {
                    break;
                }
            }
        }
        while (found);

        if (cleaned_count < 3)
        {
            return geometry::order_undetermined;
        }

        // calculate the sum of external angles
        calc_t angles_sum = zero;
        for (cleaned_iter_t it = cleaned_b; it != cleaned_e; ++it)
        {
            cleaned_iter_t it0 = (it == cleaned_b ? cleaned_e - 1 : it - 1);
            cleaned_iter_t it2 = (it == cleaned_e - 1 ? cleaned_b : it + 1);

            calc_t diff = 0;
            get_or_calculate_azimuths_difference(*it0, *it, *it2, diff, strategy);

            angles_sum += diff;
        }

#ifdef BOOST_GEOMETRY_DEBUG_POINT_ORDER
        std::cout << angles_sum  << " for " << geometry::wkt(ring) << std::endl;
#endif

        return angles_sum == zero ? geometry::order_undetermined
             : angles_sum > zero  ? geometry::clockwise
                                  : geometry::counterclockwise;
    }

private:
    template <typename Iter, typename T, typename Strategy>
    static bool get_or_calculate_azimuths_difference(clean_point<Iter, T> & p0,
                                                     clean_point<Iter, T> & p1,
                                                     clean_point<Iter, T> const& p2,
                                                     T & diff,
                                                     Strategy const& strategy)
    {
        if (p1.is_azimuth_difference_valid())
        {
            diff = p1.azimuth_difference();
            return true;
        }

        T azi1, razi1, azi2, razi2;
        if (get_or_calculate_azimuths(p0, p1, azi1, razi1, strategy)
            && get_or_calculate_azimuths(p1, p2, azi2, razi2, strategy))
        {
            diff = strategy.apply(p0.ref(), p1.ref(), p2.ref(), razi1, azi2);
            p1.set_azimuth_difference(diff);
            return true;
        }
        return false;
    }

    template <typename Iter, typename T, typename Strategy>
    static bool get_or_calculate_azimuths(clean_point<Iter, T> & p0,
                                          clean_point<Iter, T> const& p1,
                                          T & azi, T & razi,
                                          Strategy const& strategy)
    {
        if (p0.is_azimuth_valid())
        {
            azi = p0.azimuth();
            razi = p0.reverse_azimuth();
            return true;
        }
        
        if (strategy.apply(p0.ref(), p1.ref(), azi, razi))
        {
            p0.set_azimuths(azi, razi);
            return true;
        }

        return false;
    }
};

struct calculate_point_order_by_area
{
    template <typename Ring, typename Strategy>
    static geometry::order_selector apply(Ring const& ring, Strategy const& strategy)
    {
        auto const result = detail::area::ring_area::apply(
                                ring,
                                // TEMP - in the future (umbrella) strategy will be passed
                                geometry::strategies::area::services::strategy_converter
                                    <
                                        decltype(strategy.get_area_strategy())
                                    >::get(strategy.get_area_strategy()));

        decltype(result) const zero = 0;
        return result == zero ? geometry::order_undetermined
             : result > zero  ? geometry::clockwise
                              : geometry::counterclockwise;
    }
};

} // namespace detail

namespace dispatch
{

template
<
    typename Strategy,
    typename VersionTag = typename Strategy::version_tag
>
struct calculate_point_order
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this VersionTag.",
        VersionTag);
};

template <typename Strategy>
struct calculate_point_order<Strategy, strategy::point_order::area_tag>
    : geometry::detail::calculate_point_order_by_area
{};

template <typename Strategy>
struct calculate_point_order<Strategy, strategy::point_order::azimuth_tag>
    : geometry::detail::calculate_point_order_by_azimuth
{};


} // namespace dispatch

namespace detail
{

template <typename Ring, typename Strategy>
inline geometry::order_selector calculate_point_order(Ring const& ring, Strategy const& strategy)
{
    concepts::check<Ring>();

    return dispatch::calculate_point_order<Strategy>::apply(ring, strategy);
}

template <typename Ring>
inline geometry::order_selector calculate_point_order(Ring const& ring)
{
    typedef typename strategy::point_order::services::default_strategy
        <
            typename geometry::cs_tag<Ring>::type
        >::type strategy_type;

    concepts::check<Ring>();

    return dispatch::calculate_point_order<strategy_type>::apply(ring, strategy_type());
}


} // namespace detail

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_POINT_ORDER_HPP

/* calculate_point_order.hpp
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
*/