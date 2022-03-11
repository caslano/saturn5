// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015, 2016, 2017, 2019.
// Modifications copyright (c) 2016-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BOX_IN_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BOX_IN_BOX_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/within.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>


namespace boost { namespace geometry { namespace strategy
{


namespace within
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


struct box_within_coord
{
    template <typename BoxContainedValue, typename BoxContainingValue>
    static inline bool apply(BoxContainedValue const& bed_min,
                             BoxContainedValue const& bed_max,
                             BoxContainingValue const& bing_min,
                             BoxContainingValue const& bing_max)
    {
        return bing_min <= bed_min && bed_max <= bing_max // contained in containing
            && bed_min < bed_max;                         // interiors overlap
    }
};


struct box_covered_by_coord
{
    template <typename BoxContainedValue, typename BoxContainingValue>
    static inline bool apply(BoxContainedValue const& bed_min,
                             BoxContainedValue const& bed_max,
                             BoxContainingValue const& bing_min,
                             BoxContainingValue const& bing_max)
    {
        return bed_min >= bing_min && bed_max <= bing_max;
    }
};


struct box_within_longitude_diff
{
    template <typename CalcT>
    static inline bool apply(CalcT const& diff_ed)
    {
        return diff_ed > CalcT(0);
    }
};

struct box_covered_by_longitude_diff
{
    template <typename CalcT>
    static inline bool apply(CalcT const&)
    {
        return true;
    }
};

template <typename Geometry,
          typename CoordCheck,
          typename InteriorCheck>
struct box_longitude_range
{
    template <typename BoxContainedValue, typename BoxContainingValue>
    static inline bool apply(BoxContainedValue const& bed_min,
                             BoxContainedValue const& bed_max,
                             BoxContainingValue const& bing_min,
                             BoxContainingValue const& bing_max)
    {
        typedef typename select_most_precise
            <
                BoxContainedValue,
                BoxContainingValue
            >::type calc_t;
        typedef typename geometry::detail::cs_angular_units<Geometry>::type units_t;
        typedef math::detail::constants_on_spheroid<calc_t, units_t> constants;

        if (CoordCheck::apply(bed_min, bed_max, bing_min, bing_max))
        {
            return true;
        }

        // min <= max <=> diff >= 0
        calc_t const diff_ed = bed_max - bed_min;
        calc_t const diff_ing = bing_max - bing_min;
        
        // if containing covers the whole globe it contains all
        if (diff_ing >= constants::period())
        {
            return true;
        }

        // if containing is smaller it cannot contain
        // and check interior (within vs covered_by)
        if (diff_ing < diff_ed || ! InteriorCheck::apply(diff_ed))
        {
            return false;
        }

        // calculate positive longitude translation with bing_min as origin
        calc_t const diff_min = math::longitude_distance_unsigned<units_t>(bing_min, bed_min);

        // max of contained translated into the containing origin must be lesser than max of containing
        return bing_min + diff_min + diff_ed <= bing_max
            /*|| bing_max - diff_min - diff_ed >= bing_min*/;
    }
};


template
<
    template <typename, std::size_t, typename> class SubStrategy,
    typename CSTag,
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct relate_box_box_loop
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& b_contained, Box2 const& b_containing)
    {
        assert_dimension_equal<Box1, Box2>();
        
        if (! SubStrategy<Box1, Dimension, CSTag>::apply(
                    get<min_corner, Dimension>(b_contained),
                    get<max_corner, Dimension>(b_contained),
                    get<min_corner, Dimension>(b_containing),
                    get<max_corner, Dimension>(b_containing)
                )
            )
        {
            return false;
        }

        return within::detail::relate_box_box_loop
            <
                SubStrategy, CSTag,
                Dimension + 1, DimensionCount
            >::apply(b_contained, b_containing);
    }
};

template
<
    template <typename, std::size_t, typename> class SubStrategy,
    typename CSTag,
    std::size_t DimensionCount
>
struct relate_box_box_loop<SubStrategy, CSTag, DimensionCount, DimensionCount>
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& , Box2 const& )
    {
        return true;
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


// for backward compatibility
template <typename Geometry, std::size_t Dimension, typename CSTag>
struct box_within_range
    : within::detail::box_within_coord
{};


template <typename Geometry, std::size_t Dimension, typename CSTag>
struct box_covered_by_range
    : within::detail::box_covered_by_coord
{};


// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename Geometry>
struct box_within_range<Geometry, 0, spherical_tag>
    : within::detail::box_longitude_range
        <
            Geometry,
            within::detail::box_within_coord,
            within::detail::box_within_longitude_diff
        >
{};


template <typename Geometry>
struct box_covered_by_range<Geometry, 0, spherical_tag>
    : within::detail::box_longitude_range
        <
            Geometry,
            within::detail::box_covered_by_coord,
            within::detail::box_covered_by_longitude_diff
        >
{};


// for backward compatibility
template
<
    typename B1,
    typename B2,
    template <typename, std::size_t, typename> class SubStrategy = box_within_range
>
struct box_in_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        typedef typename tag_cast
            <
                typename geometry::cs_tag<Box1>::type,
                spherical_tag
            >::type cs_tag;

        return within::detail::relate_box_box_loop
            <
                SubStrategy, cs_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};


struct cartesian_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return within::detail::relate_box_box_loop
            <
                box_within_range,
                cartesian_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};

struct spherical_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return within::detail::relate_box_box_loop
            <
                box_within_range,
                spherical_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};


} // namespace within


namespace covered_by
{


struct cartesian_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return within::detail::relate_box_box_loop
            <
                strategy::within::box_covered_by_range,
                cartesian_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};

struct spherical_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return within::detail::relate_box_box_loop
            <
                strategy::within::box_covered_by_range,
                spherical_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};


}


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


namespace within { namespace services
{

template <typename BoxContained, typename BoxContaining>
struct default_strategy
    <
        BoxContained, BoxContaining,
        box_tag, box_tag,
        areal_tag, areal_tag,
        cartesian_tag, cartesian_tag
    >
{
    typedef cartesian_box_box type;
};

// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename BoxContained, typename BoxContaining>
struct default_strategy
    <
        BoxContained, BoxContaining,
        box_tag, box_tag,
        areal_tag, areal_tag,
        spherical_tag, spherical_tag
    >
{
    typedef spherical_box_box type;
};


}} // namespace within::services

namespace covered_by { namespace services
{

template <typename BoxContained, typename BoxContaining>
struct default_strategy
    <
        BoxContained, BoxContaining,
        box_tag, box_tag,
        areal_tag, areal_tag,
        cartesian_tag, cartesian_tag
    >
{
    typedef cartesian_box_box type;
};

// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename BoxContained, typename BoxContaining>
struct default_strategy
    <
        BoxContained, BoxContaining,
        box_tag, box_tag,
        areal_tag, areal_tag,
        spherical_tag, spherical_tag
    >
{
    typedef spherical_box_box type;
};


}} // namespace covered_by::services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}}} // namespace boost::geometry::strategy

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BOX_IN_BOX_HPP

/* box_in_box.hpp
dgrLoZSbxHayy//MYkqBOxR4E+VOljlUeBPvjsM1rGxpa2lq6WJZ3FiKeLHvitvmWzULprV8IrjtW7l18gTaGWy5tfIE+9/ZnzyDMQACLP3TtwafwDxDM7cOn396BmtuLT5Be4Zubj0+AX2AjavCTInVQ5Xzo0xJ2EPh58QcEbaApWWBRUQFA0MRAgQzReELBtHopCXhzfSTZcM45f6hhBHpp6niK4cx6Wet4jGHUelnrOI7h3Hp57DiwYYR7Key4kuHMexntuJRh1H89gu+dRjHb4fg4UBEWv7LGEOpT7Ik2BiDpRd0/t3jcVhkcQj0wrDxdvR80fEGh6xsfMVjavJED4cOanSmA/OLlEXybuIF4r/dJUilQLFI3iRcpYC5SNwkZKXAsUjdJHKlALaI7ySIrUCySOYknKWAukjkJKSlwLJI5SSypQC3SBA0J+XIsMXfMm/lyLHFF3Iq3R5xXWyXns+mnk/gGIlTeODoj1M0cmrn7i+9EOy0ePq3S5RmbuIRsku8Zu7iEbRLzGZu4xG2S+Jm7uMR0EsUd27kEcJLPGfu5BHES0xnbmUnVGvL4DkN6DiWTT86LcGkof7gEjjD2EQtaaoBQ0MfVcrZJWDLsGXVyjlky+gFXvk1uMvoZtUDd3l1GiWlVcg6TONYuXUJwPkt22MXhy3y/5/SuPEGyz1YcPnEytNX8qamffTQOZzyKuQdpnOs8qrkHaVzwvIq5R2xc+zyyuWdw7ML90bwncqzJ/PG8J3Zs0vzRvGd3rNno3XpbaD887N9fBMBRu38s2fR8hkyH+dImSVaMp/mSL2kfidqA726t7DdoG2wvwgxrFrlirkd5rK3xRo0cmfn+WfmAEO7P8XXKzi5TT9hxhc7GKVV30Ogd5tf4sPQgGmr/lqR6qzMmitv6hKvwy8rEOXv+jCELlweEaPlLnWtx+y+kuUWwVpxzEy2sHHYj9VA5CZSRD8rJzwwny0+OCgoqH+HxzSnTMcMlxeqvx8euL8uPho4qP9vEOSni6eK9VvyP+kgXV08cBT/3xz48wuHjsvNJecX3M6Hx47DZNRZWncbAwEDs4yxNcrxUGd61FpG5dRaPlcLarNhRbNexojXpR5iW3B7AJQlrorMC3VM1EH7WXVTrZEm3VYNBHOERdLl4jf5jQrZWoGFJfwKyVaWjreFsrfGvNLYG1HYl31hxtyItC3+vJWqHlwrcAlz7uXYjeu8DB33g+YN50gJeDRXk5ZM2T0bYNKhnJjnT/LDJpkDHSuBHoQGwa1g8t9wZryQScLGQLxAS1Jkr1he0Mf3lFbX7XZtN9+JY6mHdI1W3e1q7SvglHHML0SrgpZTrvG2fA6XvIbqy38qTlQrdi3Wu8HXJZhtYTboVGlMGMIXRLxNgkmt8lWLspSd9lWJdOOBUvfyblWVXkmZeaJ/2njjEgfFpdTvBayLKLjQR1WJ70kZ0ib4k3cNKDzYwHmSIXUJUePj/4GXBa/oLSjMw3LszapEPk8wgOtVmZYYzhJXxheKYOwGfMUljwBH1jLM97N6QswipuCa50f763IULt36yusSmGJfdht/RRC7TQwWQyiz6xrpBu8e9UlONail7xiDaDsfTxpb6kJlp0pgbrCHikXkx4Tr8hQe1fJT1SKqgoMoAnrwSuTCfCx8mH+SqGZ7qzTgVv+5uVMY3ByYfqzHcAPSPtVhsoFoLjJJSsapFM8pF0OtJekqG54MgH+X2yGjeo0lJsQlDNgmQHfEpnrp2eFnvSqYaqdV3a8WaY0YXseBSeKa50Nd4gObEjghtIkkO5Xt6PSacU2Z/YdynMvA7cCHOwt87gvtnBMxU1Wjt9N2ufnocfl6OTqEIWmouYzcKwShOaibv5e+m3/1fg0rGTn36tDyuvKsoeiFI2k6pUHbF9/D19Ww0bRaUvo4I5hI9AfByUx0weEOVcPwaR5Y6L9rLVddYJpIKhvcnIxCQkP8g9GQ4V7j19OT0kAgWkhIHOTCSB5CIETK5fzKl3Qo+aaWdYL6N33bsnUraBb+TKr6tYNfOiYoSFEzH9w3KtsnH948IzmT05NpDCeZH901F+0z2VvYvqmpeVN8moUW6KFRlIODbFfpz1h2gNfgRaX40YEcnY7XuVD5+uCtBCjr2aXu+ScNuXth7i0XziymTvnzX7mTYJ8EOMl8Ibik+R249IIWHsinFjy3oHILzthcyHa8ig7KgDZIx6/XIJ189m+01OIx/my7kY6C/dU+gn4pfLSq0H3BtgLA+brgjYxyc+jtPzkLSfVaBB38qIhCliv92Hk+YfdNFtvQp5r5tlfrz3lzair1zjAUvC1/h9RLlRRyZcLomyzmHWbzAiku1xeg3BNIp6JvvfIpdijGlXQh83Ghkgy4b6odBPP4G3lRhZEFAeb8H8J/7z3bQBB0TUCBHrHuvvhhUoB3dKCmlEuXp/1QQ082lNJQXf1KafN7LscpYM0rSk82kJGVdt+cj5CgmwQd5TOro5jP1ENLczlu3fPdIJeiAb1lGqXyysX+kMDDKJRqT/shjhJSC231VuMsoGUv+J8BFBbGBridt6VAJ16CC9EBs6YBJ0qKSDdBeMfBzLQCeV72RR0Z9x1PB08H8wV3BT8EBw9j7zqbKIAoUK2ahI6l1fjOyeyi3s28zvOD2Npi59XBk0oizAcuoU0c9NP0G+QVnxIwo6jZ1bOOdPZ2Lnb+hXzobMtXBOEsFVU+4zgTGXy2mTc4S2sEu5pJlpnYE7cxir/PqpdUK7GUdS8FWppzh65WjiljK09Qlq4Q1ycLz8/EJg0vapnflvQijr0afBZZRgOimTHRYoWrJl7JvBjwGqA6TLanyPOKtitpg9KE72TcuK3YsxFQM9AqMIZmbKZ3ppemn2auZr5mwWHKZtQW9laaW4RnU6RQ0FBgWRA9FDWR7En/plU61AAwCblD3DN5mHt4v81/7k/pp909gX2dRuzDfsfX1qTOhu+hdaGnofex6db/XpK8ZFdLh5XUIEg7Ut59SLvnXj1HsnwS/JbwpuAgM0j8GKcoalyXVVqMPr2gfqp85/XKP67wqTCmErSAW8YGskyr8CqhWmq28GjUwEjr8wnNIwWhNJMmmW/ww4Y75TlTcaREnJE0xqEzUg22ipZkD8uaoBZ+TNnzhD+y2zS25mnZsO3XZVhkspd1mkLIyYj6iAyJMolsiZKSipDsScXJCL8b+xT/xvPBontEU58AmisA9woSxFdSpclEooa0AcGta0MjfBYx9KSoRqgJjcmNhj6+PgZ+cH9Af5BoQH2ctj2zONM4IzlzOStSxIbk0sSh1sjTyh6lOURTZVdYq/is7lQaL83u3dI7/+MU1S7SFfUtM9u99CzglrNcio50BOLBUsixEHCqaBrS4IhcapYOERSf3TdppEwbkgp1axettIrXTMHh3/Un0uFg3c6rLWGTIRpUWSogvQpa0TwE+iP+juXWmmYBfIF1Qd/2AnFBp7iFmMTVSaubbuZewg//oq+g5C3i0+mbmaZ/vCNQoZ+gj9gTnxk5Kl8NGikkImz/j11Bq9YmAY5Q8rFltTmOnylJ88+c56bnxOf6JR5ywrjYU1GzvE7WGoqoRCHyvNVZ0KM6uV8ripGUNX5LssfEFx11BjwQ3NGzuAsRn1p+pbI0hUsSD3LGvOBVObGe4XRpTxnNUry6VtSSullA49g6CyEOPek46oFCmvEZvDvr4pLSO47iEkUxbH4XFAd824DWM5MGRjlJksbk1yS2oGDmCY5dAAwitETu6wuG9Z82ragjv1X8Ye3hmsiFSJcomsgkKSYpYQWGBGRwz7VDqEGY/Y6Hsk/N3cuYT+7uOLx+XGbIkVi6HDB77r/iQDRAvvEQ+0h2KMLHja8Zr+KRg62DaSYZLwBA2X++LHe/1eW5ysIGxaCICij9FjQmuA7z7gUNTT0OD9BCNuqlnOXEyXHEuYgUz/IKyReS2Mb1b58MIscoisrPi4LLdMq9lvjKkTW7xLZKcJRvKmDV7aakKoCjYWdBLQ4a39bFrSKeZT3K5dKQkmSOt82CrIXhikbmE05rzhwPzeHO4kfnJCdTJoGJw8QMjPFxOUaxDMYHct4bFtYWLm90JcGmoxjsdP4Fe/MKO0F4H+mX2sjmgYNhBKN303varOqxGrgGjt7TL4M9NDEI6xH2MHmbQDM9MVSBJlgF13wZm/cudCKkTeN9W3yD0KOD9Um94hS4irdScKJqDmH0Su3rbA3OoY0x7abzci2I0suw3PAme6MWmCRujAMd1RwC5/7QvSVfgmctSKMXRsp7B273lLhWdC09mRtZEdzFUIYHwt+vjDtatYNxwUJ+Urpzxq3Bwp1VVRzZrE5dIjhTvH7Tr0zOzsSGaicyNgfbW+meW70PN243LjhOOi4rQlihvtF9OnpT+eS8oKRDEuOju8mhO2g9rNx+NB1/GIuUFS8CyfUovvO1Q1Eoy0/zm3DJZ5MTLZGbVwsfySqipS+kW4vQlKQwXKRKy543tYGbwpIIOAkABfzxohuLtcyNcsoL+YqFe0Yg9q06gboI/OInkgO+loTXCZ+YeipidWvoFBeTRWTidz8lR5Z+8f1HXzsQB8hqq9QLmtWWvRugutiTsTHSdYgFMwSjBEN1l9gd7DhgP2A+gDMg8bg6ZMrszCRNO81izYgDdrDE3EQ7xexlw27ZDtLBBUyefNSzm3E/ldeE2AeE+Ybxh+IRlRnKJFAgv8ItzlHhPj5jNO7ek00muxJLSZoMNbHi1I07f1WtqlA5ZLqyRn2R+VzXCVg/3XZD5hylKWtZqOCe1Jxz/QeKK9MLotN7WCy4JJhrtLrkLuSVeZZoJsh8Fm9sX9+OZPYY6oH0geV4eRamDO1KSb7YUZGd5usfcsrEeNJhur2XW4CncjYA81blpQhHNcXQor05U1PCutZVTfICUhUbkmVhcv7aDhC3SCFQFq9OcQRdEhruYMC4o96/tL5Jlkl9Y6KG7LXJz8lHQ8RV3FwUZbuRtpLMEHzkd5s2fMRJ9+FYQEZO/G54i3SvSWhV20i3P7O0YDgaIvcp6qIGRUhmJY7S7f+OxJnLGi0TN3wRPAZiSkYrjq7u9d4iPWW8gWyoqxNFNlsU/ZOox4Fz9dLrEdouvV2fDY6K5BELVhWtqpoHSL2L1hVNqijpFaWhFtdNsRur1W2sAGrj7F1yQXNlRNIWJqGOqRTCLHq9Zq4OVQecTZfiQ+WWVldMmcU+Vb2Z8msZFneB/IQPm/rQZBBNIij6TDt895SK1uMDPwlVs/FukmgmoBIjxvGXyqlAObSWwdme+hwwfMM6ZhdO2x7Z2GOcjTgR9HZ4y2pMov/ZdI0o6lI0NOVOZTTgW7J+IA/bIXTEewFreDhU5bWq2Jm0qWjm6hXfNdrFlvXEGlNTtAQ/DZdvMIU758LCl5asLPQAbUzQ4kgKHI4OpKINj18aRtO23AJjLiCF7qRd9UXrqzSArR5cStXm8qxkXcDc/OBM+qR/IHsf6ZJalBroQqfrNeiV6OXsyQxYBBTIMTaLdL4wdtOvRxJJLUlFSfHN7jVIzvRGMr05f4JnI7cLMNWgVIOz9P1Q61vVda/yQyOE6DcuE0BVGuGYbetzm8MmXIuJxGkpyWEKtAmZFzRJretF3TvMfnFkegt/1E7NJk9kIrA98eOZwCuOuh8oF7Dc+4ou0B52WUhpSJ1I+fDfrOwSDMXtU92FqQ5srm6ii9PvbP4Rf+smnFg4xKSvIOzrwCzPM5dhEtIC+3JExVJDHy/LYdbMKNpaeKAB85oToFqHpojKjcHrKZ9cHB5NMtGoi5MdgFolsfSqRqe8A7rH7pudnp2K/dOkCpHOx+g9gCuccyOwBBv0/sLEwtACWpDFmAIaEQXgMBMX8+eEnUJu1u5qUfDVMPK5iVmDozhridrPqxQczJxcLYGPpVhqN3uOd+/sUZodbO44OnlRV7V2htTQFbOPyyPtIRLoA0QDsfly7NlPXmfY2uSlTwGrbV9TqZoo9vLPCGDXM/oypgZAGps3ViUDCnmj32go1ZDQPtotlZz2Arxa2O6UKukZqVV5dQ624yc2L8lc117BXmkPA0u8hdWpTWkYVlV5WQcZ6NsKSzH2aFs1P3ZZZ4gvI1Kytam1WTV+WpG9vUFbq7zIm0ZZ5TcEpZvgeVTDCB/EO/WVb+UjG2Mp2EbgVS9sEOxXetfoN/iW3eRtxh6AfU+VbsJSbxM0aUXbPqhduluTGz2rQX4nL46f6025tuzDYs/ifHrOstRFUdSSdpzJpG2usp5KXLU4gyOu+78sSZr8mPmWs49GxIRRz5BKV7BFG7tmaI0YK7iO6D8dR3VEbfaZJPeaUK8cyRmDUsfMfgNe8IBU0PjBCLN8DTAXuYHOGNf4GO3oBVEHkRDDyMMwo0o26Dd8VMu0TLREqWh5SbOA6SZBtSq1oUC00zypXEfq5WpWsITpUJSojbRW6cJGrLJ7pidk7mQdw7YA7hsQbHXAWV4Tp2bqgymIrHtgejG2aHaKmo6IXbFGz3/BwiQGl0ILv/Zxe1/mjwEcQtu62nLcOtgE1ilqlKZLO8bQDOOVsJCcMrwFVPwhrace9YjpBFbHaveZrdv2TAYcDwgOkBccFqS+mXIoWPOb/x6jGruc2ZTFX1YuyoqXcZu74R2DRo3bz658ufIhbpVcMHDPcsysbm8KWtOx2oXZtdABovOxfCM0bjvtJdX+tZpgxGWg4TV2h2ubUAuSszD9w7q1TYyrXoCJf3Loa2dcTXBic2pdi+aBuZEOms7+IOdJd7jFEIRHp5Rp0W0WLfQtMiaVxByudlWpvOR6hX62AwPm9TUo+c5oBXID/3MJldHE9GmoarhpLAmImiMUUe0LZxNeM6RJGs2TW6wzen07Iq4bgLErDyY++0CAK6jm1XhKVVBf1damabA7ZTyAXYBY3y7vCfsTq0PUyJt8HpLZlSkoF03oVewduE815BIwfBWUOSI0SctDj5pyLtpVaLe7/jDvUAZtf9dnX9+p0+3vWVy9XxJIAZUoJQ5rnzZsLsGEvtkt4lWgPGtuxtVUk7s4E09q51JoyCWsPv91yuoO9wX1hWpl6J9mLSliDbA/MILHn0ACFGCRKu9Kchfq5peJf0LG0ssQrUiwSdE7ofYMj2pVm09TELVHLFMaV/Om3M//8PdBwYxyTrWxyxI8S4KHdxM7cHuGcZIBNM07EDJrUgfJByFDVAPJhgq59VLUat7JjuuZG0mB7RrfBZaq1cZTH3qP4/7Cl1Ii7kkr6I8b0eIbbrdK00TnjiaMmgxbG+j9DrVsVcOhu7hAUVk/Wec/svR5LM4ddbMKR4AVFxV38jhxH6Naeix150h66TRgQ5O8260mViqYtRv8XbI+BxGubqzeZihfAIkz5EfzdxF3oK6gbT+5LRHc/Jg5kjOGR5B3SK+sbqEf0B9vSYfJm0vpaXPZuRanYj/Z2oYizHHdJ47SoxHz0Gb/Rew90bf4JnFHEXfuLxauyLv9bAcwaIPcIB8GqiMPcCsjMGwRbLJ6cmtwStWcuNS6SaPVI0KPgCe+bKe0BgyP9PT7llebQGd9s9Nn7MMNp30sp51ovubxekDLfx4RSa0Rm1zVYXrJea12uXZRdOOOc4S3EW8qnoGnBtmQMxekVsnD4yxHxuNwsnGL0CL/kMvaG3mwpWV4b1jmO+Z2LB+f6Rf7DE4DVhztSAPVJYGC9T7T8Igjz2I2iWPKJkHrEVcVDxl3zhn8N/L++rc2hy5mb7Jaky/OkV3TTANLZhqrQmYl2tgyLNNFMxKjo2LMoPsISbOCp+v+dd1LJltJNHnfUEynmVERoUYcqBGUbg3amck5osE38Z5W+VsOwd2fwg9iyPg0ZKw7rWoX/ZrVqqhJ9E1ojZwVS2NxzHeMfGxvr9VWtimDQy0yQXZKMmZs6FTaLvgl1AVE6VSYXdCzM7fhB85iFgVhyB/7BmfSrS+f+sb7ybR79zWJfkzsmA2kEU8FtV3W596AwuwfFaK+NYBjvFM/FNfjZqdjB9VqsUkfAIi+rqr7qXYgQGC0L5Vu5m/WfUayoK0gtR1iE/lZSbWThNtbcsvwivsq+Q3uE/QD9KaO3idhSgnuT9yI3A7+FYi2u8au12ErQxrSWdi1qnRJE42YMGgz6GiX1apBaVQNDh3DNMP4A0CkKXyfICx2kOf38+febvR7ZlTFSKYo7t/AB0FimXiwvFYTjatmhBbJO5YDkJq6hOuSwWMe5woa9HKOBjhTC+zapNg1lkuWx2QXn7TA9oqBXwsi9AIMJowJzAwMjqySVxSFE0qHZafZJ/azA3MTMwy9l5W6KbtZO4yXUpqJW5oN3Odrsk5/zW7MvVKQez+AXjBeqNdQ37HiA+XtDIhYggJCi7ERwHqrEEKv41NjxTpVfnU9VhmBqQVUOxW2lE2BCS1Frh74CUkt3OoNm0zAHC2CaBEaQ9SQFGjCUuOOIojMp19PLwvKu//PRMSToHqOWDgggyVKTJjJUPwxpLGMA4Fht8BUwdRFLoVLukyaTsAQuUSevMqZhFlho+g66VV8tl8EliHcms415UviyXjEkdE981v0519vQvIpX+qtJDLx9nqs8Mdqex23CkZZhSWbpYNz5KegdakLqKznxEGHaIIiGuFimNlQrrOv3piVdnYoo3b+rChDlLPzS/QHUO3jvveL80nujuaoroIKBgTIeqLHZ6TTt6Pbho5Nr2uqFQD2Af9I5qFYUMsa68PIu2Go4uNPyu3hFsRSzOh2ZkfdkQeGN5BPM9f1mk+G7mLuE5SoSRa+VIpLxPsgfX2puhJW8UzIwy6/z5amNrDh49q38re2tjpC0avCtHl7s5hEmrYxbnuA+nK2e/a2wHuQWWYhNX/Kz7T9YtAyrsU53RIK8+rz3DeLrEa99Zh1btUET6LUguo9jICRgVNcXwrU03pJ5OAA5qx+Q1qV1JFZZac1v0tT3VEg5hyqEZj9v3FKOSGozII8A9AJMEqRBZI+aRj9wwavY55atyfqSzIRyyjmautknENh98MMwQtWqSvH0ffoR3CvCiRP7epqEfPdC9kJzq0cZ9xLodKfPZXxG7Zc8FcprTutkMF0wcCmtRrBYMHrw8Gyj4DDpAb1dul3uXeE8LsuBiAJNWF0MLRRtFHClpH7NrdSQQD4wGvS6bRQ5jfQ+RsiikM=
*/