// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_POINT_ORDER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_POINT_ORDER_HPP


#include <vector>

#include <boost/mpl/assert.hpp>

#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/radian_access.hpp>
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
        typedef detail::area::ring_area
            <
                geometry::order_as_direction<geometry::point_order<Ring>::value>::value,
                geometry::closure<Ring>::value
            > ring_area_type;

        typedef typename area_result
            <
                Ring, Strategy
            >::type result_type;

        result_type const result = ring_area_type::apply(ring, strategy);

        result_type const zero = 0;
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
    BOOST_MPL_ASSERT_MSG
    (
        false, NOT_IMPLEMENTED_FOR_THIS_TAG, (types<VersionTag>)
    );
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