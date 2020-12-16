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
R//U1IO7xNxoj2qre1Vb3TfV9cmP9O9UMfNXKLtyl1e5xkhll+yTa8ID0hc4P0or9N2EZBUjAaSZoM3Y1eQlz12Wg8QzckxTBH873698C6UVkQ6dBxA6ngLdRskzInzQlDy8Uqoe4f6uUbzSyp9FvcOYFXV2e8T7JhtR5kehzFF+/HZqgTtKMgm+iovDbLNboLd9w+dluA360FS884430jtgA6eGbGAkns309aTi4k13eU1x3mjcFS9sT7+L3Gzsz73Z7/Gat3wT3tLjvIGQKcYyRUsi04+8d/S/zJN9m0XVwzMoLMdMZyJ8RtBWRe8T24G82PdcVLpnq3Q/hvDZIl1Dd4aqQ+cq/0Px1lbPc7ZI9OqNCoV/NvAvQFtN+mAftU2NQz5FYW3zF4LuLEF3kaK7OILuMwST9yPJeb5/lPnvRWW8VbDlS0K2vMJXKyGZy1X6jKFl4ifnqKDdpvGCGFQKkXfv/Q/42ndUVNlepsr2coQvU2V7mSqrz6uyugxldZXwQ5dF6PaL0G3gKzI9Q1m5RyWRlfc+fDmk2/YljXZS0TdhDuc/Nz8GjX2PRenkWqWT6xAmeN777CaUyjEr3mIR/R+CKVy1RoM6ca3S8/WsZykD3ZUu9HxthJ6/LdtorPk0Qe9TCug98JHkFPDUmO9HY+Q3B8z4D3tYbxRlU0t6PqahaZ5StQCFxw9OR5QGxg+Br4Y/JBcu78G5SduBSkkA8p/fKILO3iOm7OEWZQ+3InxLYA/RZ/CK1IlJ83aV5h0qzTsRviPCBq8uC95p0zZ411TMaSu8aPyJ3o/YZiUOPolLNvtj2OwtymbvY5uVeqL95cC/Q+H/VOHfAfwHhI3fEmHjD4r4OyLiH1Z14CqqAxsL+p6+ZCbbjucWRH/BvZnSyW9RurpAeEND8SEcC2aygF+tse9WW4f4rcCfT5Xrg3SAZW17l1so6bTmEYKQdWBdmMoOfiN4TxqfLJNJ3i+Jv09zA958yqIPejXu9tdryb+Cnmo97s9H158i5LVn75UtP6Fs+UmEn2Bbho3yW17qUzb61NQx10RsR7WjcVXbMY24lzYqxt/vDXmXFcGzcU1X44pOOnIErpFx4Pvs1DHvxW5cUd/WIK5TCQPhH74qbFb3b4+ydmu65NTHFXfDxXD3F/lQYY80i5VdibfwGE52OBLfpODP2LmrdHxjcgOft/uDnbci1PiIkYD7+M/ZuSvy2+hLTyY7f17YebsbR/Slh0KvMStgoTNFm4CqFis1GDzGWNvaSK96WvIQBGX2R983Qed/cnOOG0xej8Iew5eCvJHubWuVpO1joatJFTT/GY7/Wjd1K+kkeEdL19puum05uBJLgWVb85eC81AtnZ0rjfGNPpMSGQO9vVJcHZK3nDgHEh3Fsr4GvtI/kTu3d0C/KPr1b/h1DXPFL9syIg2KetKu6snfS2nsa2AjPdlcOjhvuUm/4QP4qWIPyV+J/1avZ4N/h9+rFD7HS/TLN662mXA3aAC7iGDBgaCgDl5iZMXhBVk3r/Lss89BJGhep/SuQx33+fyNYNu9zGDPwd1mf6tn80iwe9XZ+4fk2XvAfiXeDSo1ZyKEjT/FNqrNs0C/29Fs7GEahEHzdLRP43IhnxZPJ3qGVrhMcxnWyvKCr5urfN3b1k9RUol+eizAY5/Y7N93iHTMO/jtpo0W5bAGvFbSRZc+bJ1PZ4CvBb5wMI8vTBlfCD80hXT5D6HLrfBlieDwEQN25D6TtiXLGuu7LH1UBNeff00Nn2f7t5WF7z+jsDvLZrIn7a7UI/X1ZER/h/SU6Lfht0w54O5O/22Jd2S/BnmkUaic8JRA/RYy7qCJj2TTCap08gwM3RM=
*/