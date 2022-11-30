// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_LINEAR_OR_AREAL_TO_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_LINEAR_OR_AREAL_TO_AREAL_HPP

#include <boost/geometry/algorithms/detail/closest_points/linear_to_linear.hpp>
#include <boost/geometry/algorithms/detail/closest_points/utilities.hpp>

#include <boost/geometry/algorithms/intersection.hpp>

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/geometries/geometries.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace closest_points
{

struct linear_to_areal
{
    template <typename Linear, typename Areal, typename Segment, typename Strategies>
    static inline void apply(Linear const& linear,
                             Areal const& areal,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        using most_precise_type = typename select_coordinate_type<Linear, Areal>::type;

        using point_type = typename std::conditional
            <
                std::is_same<typename coordinate_type<Linear>::type, most_precise_type>::value,
                typename point_type<Linear>::type,
                typename point_type<Areal>::type
            >::type;

        using linestring_type = geometry::model::linestring<point_type>;
        
        /* TODO: currently intersection does not support some cases of tupled input
         *       such as linestring - multipolygon
         *       this could be implemented directly with dynamic geometries
        using polygon_type = geometry::model::polygon<point_type>;
        std::tuple
        <
            geometry::model::multi_point<point_type>, 
            geometry::model::multi_linestring<linestring_type>,
            geometry::model::multi_polygon<polygon_type>
        > tp;
        bool intersect_tp = geometry::intersection(linear, areal, tp, strategies);
        */
            
        geometry::model::multi_point<point_type> mp_out;
        geometry::intersection(linear, areal, mp_out, strategies);
        
        if (! boost::empty(mp_out))
        {
            set_segment_from_points::apply(*boost::begin(mp_out), 
                                           *boost::begin(mp_out), 
                                           shortest_seg);
            return;
        }
        
        // if there are no intersection points then check if the linear geometry 
        // (or part of it) is inside the areal and return any point of this part
        geometry::model::multi_linestring<linestring_type> ln_out;
        geometry::intersection(linear, areal, ln_out, strategies); 
        
        if (! boost::empty(ln_out))
        {
            set_segment_from_points::apply(*boost::begin(*boost::begin(ln_out)), 
                                           *boost::begin(*boost::begin(ln_out)), 
                                           shortest_seg); 
            return;
        }
        
        linear_to_linear::apply(linear, areal, shortest_seg, strategies, false);
    }
};

struct areal_to_linear
{
    template <typename Linear, typename Areal, typename Segment, typename Strategies>
    static inline void apply(Areal const& areal,
                             Linear const& linear,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        linear_to_areal::apply(linear, areal, shortest_seg, strategies);
        detail::closest_points::swap_segment_points::apply(shortest_seg);
    }
};

struct segment_to_areal
{
    template <typename Segment, typename Areal, typename OutSegment, typename Strategies>
    static inline void apply(Segment const& segment,
                             Areal const& areal,
                             OutSegment& shortest_seg,                       
                             Strategies const& strategies,
                             bool = false)
    {
        using linestring_type = geometry::model::linestring<typename point_type<Segment>::type>;
        linestring_type linestring;
        convert(segment, linestring);
        linear_to_areal::apply(linestring, areal, shortest_seg, strategies);
    }
};

struct areal_to_segment
{
    template <typename Areal, typename Segment, typename OutSegment, typename Strategies>
    static inline void apply(Areal const& areal,
                             Segment const& segment,
                             OutSegment& shortest_seg,                       
                             Strategies const& strategies,
                             bool = false)
    {
        segment_to_areal::apply(segment, areal, shortest_seg, strategies);
        detail::closest_points::swap_segment_points::apply(shortest_seg);
    }
};

struct areal_to_areal
{
    template <typename Areal1, typename Areal2, typename Segment, typename Strategies>
    static inline void apply(Areal1 const& areal1,
                             Areal2 const& areal2,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        using most_precise_type = typename select_coordinate_type<Areal1, Areal2>::type;

        using point_type = typename std::conditional
            <
                std::is_same<typename coordinate_type<Areal1>::type, most_precise_type>::value,
                typename point_type<Areal1>::type,
                typename point_type<Areal2>::type
            >::type;

        using linestring_type = geometry::model::linestring<point_type>;
        using polygon_type = geometry::model::polygon<point_type>;
        
        /* TODO: currently intersection does not support tupled input
         *       this should be implemented directly with dynamic geometries
        */
            
        geometry::model::multi_point<point_type> mp_out;
        geometry::intersection(areal1, areal2, mp_out, strategies);
        
        if (! boost::empty(mp_out))
        {
            set_segment_from_points::apply(*boost::begin(mp_out), 
                                           *boost::begin(mp_out), 
                                           shortest_seg);
            return;
        }
        
        // if there are no intersection points then the linear geometry (or part of it)
        // is inside the areal; return any point of this part
        geometry::model::multi_linestring<linestring_type> ln_out;
        geometry::intersection(areal1, areal2, ln_out, strategies); 
        
        if (! boost::empty(ln_out))
        {
            set_segment_from_points::apply(*boost::begin(*boost::begin(ln_out)), 
                                           *boost::begin(*boost::begin(ln_out)), 
                                           shortest_seg); 
            return;
        }

        geometry::model::multi_polygon<polygon_type> pl_out;
        geometry::intersection(areal1, areal2, pl_out, strategies); 
        
        if (! boost::empty(pl_out))
        {
            set_segment_from_points::apply(
                *boost::begin(boost::geometry::exterior_ring(*boost::begin(pl_out))), 
                *boost::begin(boost::geometry::exterior_ring(*boost::begin(pl_out))), 
                shortest_seg); 
            return;
        }
        
        linear_to_linear::apply(areal1, areal2, shortest_seg, strategies, false);
    }
};


}} // namespace detail::closest_points
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Linear, typename Areal>
struct closest_points
    <
        Linear, Areal, 
        linear_tag, areal_tag,
        false
    >
    : detail::closest_points::linear_to_areal
{};

template <typename Areal, typename Linear>
struct closest_points
    <
        Areal, Linear,
        areal_tag, linear_tag, 
        false
    >
    : detail::closest_points::areal_to_linear
{};

template <typename Segment, typename Areal>
struct closest_points
    <
        Segment, Areal, 
        segment_tag, areal_tag,
        false
    >
    : detail::closest_points::segment_to_areal
{};

template <typename Areal, typename Segment>
struct closest_points
    <
        Areal, Segment,
        areal_tag, segment_tag, 
        false
    >
    : detail::closest_points::areal_to_segment
{};

template <typename Areal1, typename Areal2>
struct closest_points
    <
        Areal1, Areal2,
        areal_tag, areal_tag, 
        false
    >
    : detail::closest_points::areal_to_areal
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_LINEAR_OR_AREAL_TO_AREAL_HPP

/* linear_or_areal_to_areal.hpp
P9LgtcmPvpfWncGXzPdXaUGvTXpl8GZeovlf4IWXzDWqZUFPt3XfcV2D/Ce9NPAG+ad41nwkPT94DdJrA0/V1p2+mtbuXSOcY1Gj8y/Izi/40SA/tsEL1+j9P3DgNOo8/q0hDJ+mOfhr7G3xRs18lhRqskbqGuH8ptN0/tNpu31USN/kafOezp7ebavSbF2/UKNx8Y+qzjLprQLXEdZOa99P/EhY/3Ga1n+QndK3rv84Tf1c8AZeNtvDEeCxzjX1u60N1W3c/v/LZhuxLPg98zKdt3IVxngn6TkL2zT5tAGc61xbE3xKk3bo2qozVKf5Pth6XqHxH/DwK13fi4Lvup071wZ93ytmHs4DpxHCml7vtcKe/OTHKtkpfVse+siPGHiVV8z60QBeQtp7Eabq5lhZ3Rdb/dDvlaofY4L9rOBXoG7ei5DFVvlqq98VSpNaTx2m9ctp2ObqtP8bcKNu/wY/LcSVozKRB2/wVZr/Bp581dI+CfdOt3fb6hj6v6/S/u/AeYTlV7X2Qigb6Vdp/weyU/rWfePJDy94LfLD89q6M/Ca2V54Bb0W6S2CN/2aea/8wCmEhdfoux5BM/qa6U/CYqvisd1nPW53HgO8MunVgcfOrDut17rpW4kJ+5icof1PyG5DSEOZ/GiAFzhD+58AR8/YxyuKb92/5AzNx+6vOtkzZvrywOUz5v1SPJufWdLzgudp0P6HwKON3WNWxbXun9ig/gZ4c6S5ALxk0fQLmnOkmQBvrWGmexPY8/q6U2x076OzX5jHatD8V8O0Swj3a438qIPnfZ2+/wFeRvC/ro2LBT/Cr9P3P2RXF/zQ43Tr+4Gqs0laReDK693xhuJYv/8hrRB4fW+Y+TUInEQYQ1h4o+vf7AGhD/sG9X8ttqOCP9E36PxjslP+2cqI7rPbdwCv9IZ5JkYN2PNH9EUQ6tvy2iRlazsTo0RxrIHn/aO5Hnn6z9BXdrb1yLqW29cAL0H6KeD8x+gXBf0E6bfAa5G+B7oj23vrtwT9FukPHqw6/m1TPwgc/Rh9ZWfT17Xc9gK8LOnngcfe3Ft/4qC9H977pjke6f8YHb/gZ5b8dMALvGn6GQJe/hh9R9DXtdx5ePA23zTrXBF44E/rztabWrt2UFjH8Sat/yA7pW+r55vkRwO86T+Z6fQDO3/aO50NIZ26lrvGabnqpEg/C1z+GH1lZ13/T/pe8Dxnqf8PPHxWe+4tC/3/szR3DJ7vLPX/gcNnzXevimftx5NeDLwk6WWAc2fNeYCYoJckvTR4zbNmO9/bxD1s7n4uK66tzW2SZgG86abpox842DT3mygIPuq26k99Nx6m76tVvzFK/av4P2G8PE3fBh1C+0++1IBH30Lamtq6uUPCPo5v0f6PZKf0rfOmlIYgeHNv0ftP4Mhb9n6x4lvff75Fz4Z/rDoj/0rrr2Cbp7jKwGNvrzvbb+2OK3pIeJa+Tc9/wT4l+JonX2vgBd6m8R9wFmHpba1cCHmx8jZ9/0d2NSEv9DjdPtB1VadOfrSAPe+Y/XrFs747Ib0AeN53qP8HvIzgf0fbB+U6of/3DvX/yC4g+KHH6dZP8DbJjyLwQAvtuKa3LPjRJj/6yC4t+LFJfpTBm25R/QcOtsy9TcqCnm7rlr3D6P+QXgo426K1dYeF879Jbxi8eovWfwL3vtvdS1BxrOtGSasM3sx7NFcfR/rf7X57oOqfHzgL3hhCP0IMONThTBw+P1fVR3Ft4fdgxw/+LfUurf8GbiHkSLPHoqnPmW1rNkEhzSqurEXv31RZRVrKFrt/V/3/92j+D3gFIdi5nhV8jLxH+19oNmXBRzeuuL0dmn6X1h2CV3+P6j/w5PtoA97X1jDHhfdY79P7L7JT+tZ2g8qJOl9qmM5XKsI28j69/wOuICS1ODKCb5vkW5HsioJvepzu+8C/hW9/Sf2u66vOUJvOfwZ2ECbb2t5egm9zbdr/g+yUvvXc6Dat4bga4wl6lxyG7Uab9j8C9p1DG4Z/B89pe7kJ8bQpbX0WW+/1wncc5+j7j3OmnfLPum8SpS0JXuQc5T9w8hydMyykQbd1yzD6B5F/ofEqroWoz1CHXvscnf/zwbozjzD8we61AXkhPZMfmHkwK9ir+KznB5H/40eqTpw0k8BNhOwH5l40A0eEvtgH1P+z2Kp4bOnR43bvHfqYM9THDMDW+yE9/4H9H5p9/IDgn27rPj7Ai5JeAngLIfWh9m7ziHCO+Yd0/jnZxQU/ouRHEbx9PSfM9b/AQYQxhI/2FhT8mNFs3faf7IqCH3qc7t8NeP6THyngLIJxFssNwvOf9NS7iQDN7w/Btq3xVDnru+CEM4TAexcqrq2stCkeH3izF5iaAeAwAu8d6BM0dXt3TQ54yQvMe5EBziHoY6uIcC+SpJcGr0l6vReecPoR9L5aWtBrkl4JvKkLzTT7gIMIu/Y1E9Ks25+f6EX+X0j5D5y90Eyz4lnzn/RGwauTXgvYc5GZ5lFBr056PvC8F5lpngaeQ+B9zBTX+g3HRZTP4MVIcwV4DYGfBRFBM0aaKfC2LjLTva1w7wljXXlKSPcW6eXBG+s16/gk8Exvt44rjnX9Y6+pFThadRY713b6zABQLK/TMeDpi0981GfeBE52OLWEvc/cD/6+o/Y+c4V8bQCPgt8izR6Lpt4fHdZsduLqscSl0mQ9o5XSngfPudjM6yjwCgLPwSiuLa91ezct4BVIswK8jbBrzwNBs0CaPcfQ//uEWX7GgCcR9Pe3imftx33C1BsEL0R6S8DLCBWEj+aBBb0Q6Y2Dt/kJM4+LpKU41n4zac2C1/cXptYg8AjCR3v6CFq6nfuuAjw/aQWBwwg745qQoOUnLXWeSpDOEVFnmHnoLK4Y9AqarZr3rAC3EHyeE9Zz35WNbT68QD5sgDfiMbW9wAmPrJ08Jqyf1HTc9Z97aGwI/um+uM8V8PIe836XgWuebt6VhPudJ60meP2XmGkdBp68RPazKfip67ht140o/6S9BLyirkHXpq1sbNoh0h4Gr3AJ1X/gbQQ+00VxrfWfNKfAG7qU6j/wJIK+h4XiWev/paaeo9J/qenjEnAcgfevcAQfQ6RZAC936Qljz5IS8MwnkfeflO9tu2OTuPH8M8B7Aa1l+qT5DBgBHutc+3+WqxiahD0AgENLtZ0PWFTF+vjPwgqrrrIIKCoaKrKWVhalEpZogliAiyhkBlqZecluVruGJf5ppdxOW1bWtTLTsvKWlZUppXZBTDTNrKyrVyktq2NLCkmKiu3vM7O7sLtAdb/P/fU8H9lzzsw7M++8887fc/LFaXH+ieciP619k2RbUL41ws31S0P+/x//JM++eK3+Pxc7BvnG5UeKD3UM7F9ruJ5gDOwP9EZvvOWeMlmD69AYqIfBXA8LiqO0Ekek3+qZnqB8rrvmSPG+cUHf+yTuMmOgn1jDdTm0ts9zUxtp+cuQ8yfC1RoD/YTSaVOxsVOznxBhWv3+Y5CscsIN7xTYNjK5Xgo3dWoeDy1vQ15xp8B8LA6KJ+S31qb805S+h3DbOgXqah/XNdDaPkN9G7raFiQ3+oUjxXGdA33VIK4zOrftB0WcVv//r50DZQ8mXHHnQN0t5npZ50CfLcK1+v5HkLxZhNvROdCv7Oe6pnPLsY8I2+r7z0Eyl2KXcRbvu0a+s30r6NcjNjV97yX4ntLKPd+4dAbX+0y0bf5m8ncwzO2CLwWxj5fA372Rm4rXQzTPGnzpIKtDa3vN3udC3x1F/iP+e9m+75CYlJbfIfF9296ktPy2/dIXPPGig56tRHb5C554wc9mmALtvZjrMljkve+TqbQi09//rPOL40tLaSUtUQcdWxtfBdXVVMLpIwPzFs11PPj2BkSYVt//jQzyL4SzBMmayvXMyObx6Nw2ZPnitfO2tWWRbdehf93pW6m7zd40gr9JVBOUt0auDV2afc7mNvIm4vnSU1pJ79CK1tvpTV0C2/hMv/L40mxY0brPWByk2+EvHile2yXQFjZzvc17Tzxv9fxvl0A50whXHyRHH0UfEOW5N60NOfVBchYRbnhUoD4zub4hqrmuRZhWv+UbFShrgUIfqA/a7155pHh5VKBPW8t1eVRLnybCtubTlgenQ7jaIJlKND4huqXMBW3IrA2SuZxwo6OD1n+4ntGKzOVtyPSPL/eJCLcsSOYarje3IrOsDZnLgmTuI1xNdGA/2SjKHrOp1f+/uwjfWj9ZEyS3VpQ/Jqj8XM+IaZnX2rbKHxM0T1hF+YNkruF6cysyRdhWyx8kcxDhaoJkNnJt6tpS5qA2ZNYEyRxNuNSugW3AwvVNXZvbgAjT6nfjugb5YcI9GiRrOddrujaPB6a2IevRIFmLCLe/a2BZNa4bWynrojbKuj9I5krCDeoWKHM415ZuLWWubEOmf3zZfxFuQbdAm1zC9RpYdmVLmxThW7PJBUFyD4nyB+VV47qxlbweaqv8QTIbRPljA/35cK4zYfmlfmcEV7Xx/cvYoDHgS8x/YgPr+1Gul8U2244I0+r7z0GyZpmPFE/rF3RGkLiHYgN1UCOuu29q8R0XEbbV/4dHUDrFhBvcPVBmKtcTWpFZ3IZM//jSJxJuUfdAvS7lejX4f+dXhGt1/y9I3nrC7QuSd5Tr+iB569uQty9I3m7CJfQIlHcF16N7BMrb3YY8/7hynCf+HxhB/6+IG4YcKdZGBO2JcW9xatD36V4+UrwuKC/lXO+F8gHNeRHhWj3HHZSXxdhNfJDdzJh0pHjzoqB3IJE3oGdgusO4zugZuB81qI10/ePK/WzCFfcMWv/lennPlu1ThG11/dcv/jeH+iulJ/srb8Kn8Av0re+vjIJb4EF4CbbCdxDyG89hFNwJK2EXnIQrTvVXpsB8WA/nof/p/sqN8DD8C06DuaG/Mg4Wwj9hHzSC+Ux/5S54DvZCLfQ621+xQDEsg8/hDIw6xz34AI5C/8b+ShY8Ah/Cz9DhfH/lIrgOiuBJ2AIaGH7vrwyAp+AjcMOV7v7KvfAqfA7tlUTlb/A6/AwDdYnKzbAQ3oHP4QxcFpKo5MDdsBy+gw6hicpFcB3cD6/DJ/AzxOsJC8vhO+jQLlFZBRXwUFiishmOQrfwRGUE3A6Pw6dwHnoZEpVCeAgq4Xvo2J78wQE4Axd2IE/wMFRDTMdEJQNmwTIoh1qINSYqqbAKDsAZ6N4J+TAPvoaIzonKpTAO7oMX4V/wC8REJCpXw23ghC3QzUT5YAucg36Ricq1cAc8Ax/Bj9C7S6JyDUyHx6AcTkBEVKIyFIrgedgNNWCMTlSGQB7Mg1dhD5yC3jGJSjr8HR6DctDA1DVRGQZTYTGsg/2gdEtUBoAFimEl7IBaiI1FJzADlkAZHAZD90R8cKJyAyyANbAflB7IAgsUw0vwCfwKPXomKqOgCJ6ErVAP0XGUHabDMigHDUy9yC/cA6thN9RDXO9EZTTMhKWwGY6C8YJE5Qq4CR6F9fADdIqnDDAVFsM6OAw9+mCTcD+8DPugXd9E5WKYCCXwKmgwpB/5g8dgA3wD7RNID26BjfALxPZPVJ6FCqiDxMREZTIshU/hN7jKnKjY4DX4D4QMoI5BhW1QA/0vTFTS4E54GrbAL9DvItodvAjfQYeBicrlUADL4FPoPgh7h6XwOZyBPhcnKrnwALwPP0CnSxKVK+E2cMIWCL0UncOt8CJ8DrrB5AXuhBfgY9Cgx2XUJzwHu6Ee4i6nbmA+rIGwpERlOEwDJ1SC4QpsB26Df0A5/AoJVyYqmTAPNkGXIYnKGHgY3gYXxA9NVK6Hh6AcXBA1jPzBAngXfoJeyYnKeFgEm6Eehl6F/4DH4QgkpVA38DT8CJcNR7fwBHwAp2Dw1dQvrIP90P8a/AE8BZvge+g1IlHJBydUggt6pSYqWWCD/aCMxAbhAVgN26AeRowiDHwEx+HSa/FL8DxUwkmIGk1e4Vb4GM5CjzR0D8XwPlRDfDp+De6H52ArhIyhjuE2eB1OwvAM2g6sht1gGotPgjmwDWpgyHWJSgNccj11B3uhYyb3YSashv9ARBZ1BnNhLXwFEdnoGhbAOtgPyrhEJQXugOfhGFxowU7hZdgFp+CqHPQNj8BW+BXM49EJVMAZuDA3UZkAS6EKYifQNuEx2AA/QsTERGUsLIR/wudQBwPzqGP4CI5Dj3zaDpTCFvgFYm5IVG6EB+F1+A4GTaLe4XnYBedg4I20KVgKn8FpSJ2Mv4LX4TvodhP5gLvhDTgIoQXYGtwML8F/ILaQMsI2SJhC+WARrAdlKv0K3AlPwxa442b8BWwCF0TdQh3CHfAUbAIXRN2K3qEYXoY6GDGNvgt2QMJt2Aa8Ci4YOJ02Ae/DDxBzO20G3oM6GDGDfgB2gOFv2BushkMQV0Tbh9mwHS65A58Li6EBBs+kH4Fl8DMMvxNbgtXwAyT9HVuDldD5LvoE+Du8DT/DtbPQF7ig592UFZ6Cb+Cye9AxVMFpuPReygivwQlIs+JX4D34Hnra8CPwFGyCH6HnbNKARbAJXBB1H/qDabAIJhZTHtgE30O/OegL7PAGhN5PeLgXXoZf4OIHaOPwNLwP1XAezHMZR8DDUAF1EFlCWSAH5sBqKJ6XqOyEjPm0M1gPnRbQd8E98BJ8AmfhooW0f/gOih7kPpyFfnbyCJ/BgEX0z7AGlFLqCBbDXoh9iGdghwPQ/WHKB+vgLFy1mL4V9kMnBz4OlkE5/AqDHsF2YT58CPWQqNI+4QnYDrUw5FHuwTOwHY5DdydxYRGsh6NgfQy/AjUw7XH6aEhYwn3YDfonSBNugaehElww4EnyDatgHzRCwlP4Krgf1sDXoF9K/wnj4R54AfbAcej3NLoBFcrhMCjPIBtugCfhS2j/D3QF4cuoT7gPVkENTH4WG4MDcAb6PIc/gI3wE3R5nnoEJ5TBHcuJC8kvUF4og0a4egU2BF/BxS/SF4AKO6DTSmTAPbAadsPvMHsVdgNuyHwJncFa2A8xL9OWoQiWwR44A0NW4+fgUfgQNOj6Cu0a7oGVsAdOw5Wv0h7ABk/DD2B6jbYGNngBPoXz0GsN9gtPQSV8D1H/RL+wDmoh6XXaMKyCnRD2BvmBv8MzcBBC1+JX4G/wBlz7Ju0MdkPntwgPc2AVHADd2/h2+Ai6rmNcDPNgE/wC5nfou+F9qIYp79JXwBl4+D38CfwK5vXkFZ6GLfADTHifsT+chswN5B2egUpwwcUbaR9ghz1wHLqW4ddgOiyHfdDtA/obeAc06P0hfQM8A59D502Mg+AojN6Mz4R/wD7otoU0oBi2QMhHicpd8B58Cedg5L+wBVgD1dCjHHuBJ2A7HIfEikQlG2bD2/BvcIN5KzYN8+Ft+DeEV3If8uFx2AjfghtGbKPu4QX4FHp9jD+BJbADem1PVBzwNvwE8VXYEDwIr8NXYNyBbcE6OAhRO+lXYQ18D1GfMMaHR+E36LUL/cFS2Ay63dgaLIFy+BUu/xTbhS/BtIe6hDJwwcDPyCM8CK/BTxC9N1GZBAvhHbjyc/pnWAeHod0X5AE2wXlY8SV5hah9tG+4G16Dz6DTV9gVPA5fgelr2hh8CGeh778Zg8A62A+G/dgIPAxVcB5GHMBvwW5ohEv/
*/