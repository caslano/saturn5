// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2018.
// Modifications copyright (c) 2014, 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PYTHAGORAS_POINT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PYTHAGORAS_POINT_BOX_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>

#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/calculation_type.hpp>



namespace boost { namespace geometry
{

namespace strategy { namespace distance
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <size_t I>
struct compute_pythagoras_point_box
{
    template <typename Point, typename Box, typename T>
    static inline void apply(Point const& point, Box const& box, T& result)
    {
        T const p_coord = boost::numeric_cast<T>(geometry::get<I-1>(point));
        T const b_min_coord =
            boost::numeric_cast<T>(geometry::get<min_corner, I-1>(box));
        T const b_max_coord =
            boost::numeric_cast<T>(geometry::get<max_corner, I-1>(box));

        if ( p_coord < b_min_coord )
        {
            T diff = b_min_coord - p_coord;
            result += diff * diff;
        }
        if ( p_coord > b_max_coord )
        {
            T diff = p_coord - b_max_coord;
            result += diff * diff;
        }

        compute_pythagoras_point_box<I-1>::apply(point, box, result);
    }
};

template <>
struct compute_pythagoras_point_box<0>
{
    template <typename Point, typename Box, typename T>
    static inline void apply(Point const&, Box const&, T&)
    {
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


namespace comparable
{

/*!
    \brief Strategy to calculate comparable distance between a point
    and a box
    \ingroup strategies
    \tparam Point \tparam_first_point
    \tparam Box \tparam_second_box
    \tparam CalculationType \tparam_calculation
*/
template <typename CalculationType = void>
class pythagoras_point_box
{
public :

    template <typename Point, typename Box>
    struct calculation_type
    {
        typedef typename util::calculation_type::geometric::binary
            <
                Point, Box, CalculationType
            >::type type;
    };

    template <typename Point, typename Box>
    static inline typename calculation_type<Point, Box>::type
    apply(Point const& point, Box const& box)
    {
        BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point>) );
        BOOST_CONCEPT_ASSERT
            ( (concepts::ConstPoint<typename point_type<Box>::type>) );

        // Calculate distance using Pythagoras
        // (Leave comment above for Doxygen)

        assert_dimension_equal<Point, Box>();

        typename calculation_type<Point, Box>::type result(0);
        
        detail::compute_pythagoras_point_box
            <
                dimension<Point>::value
            >::apply(point, box, result);

        return result;
    }
};

} // namespace comparable


/*!
\brief Strategy to calculate the distance between a point and a box
\ingroup strategies
\tparam CalculationType \tparam_calculation

\qbk{
[heading Notes]
[note Can be used for points and boxes with two\, three or more dimensions]
[heading See also]
[link geometry.reference.algorithms.distance.distance_3_with_strategy distance (with strategy)]
}

*/
template
<
    typename CalculationType = void
>
class pythagoras_point_box
{
public :

    template <typename Point, typename Box>
    struct calculation_type
        : util::calculation_type::geometric::binary
          <
              Point,
              Box,
              CalculationType,
              double,
              double // promote integer to double
          >
    {};

    /*!
    \brief applies the distance calculation using pythagoras
    \return the calculated distance (including taking the square root)
    \param point point
    \param box box
    */
    template <typename Point, typename Box>
    static inline typename calculation_type<Point, Box>::type
    apply(Point const& point, Box const& box)
    {
        // The cast is necessary for MSVC which considers sqrt __int64 as an ambiguous call
        return math::sqrt
            (
                 boost::numeric_cast<typename calculation_type
                     <
                         Point, Box
                     >::type>
                    (
                        comparable::pythagoras_point_box
                            <
                                CalculationType
                            >::apply(point, box)
                    )
            );
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename CalculationType>
struct tag<pythagoras_point_box<CalculationType> >
{
    typedef strategy_tag_distance_point_box type;
};


template <typename CalculationType, typename Point, typename Box>
struct return_type<distance::pythagoras_point_box<CalculationType>, Point, Box>
    : pythagoras_point_box
        <
            CalculationType
        >::template calculation_type<Point, Box>
{};


template <typename CalculationType>
struct comparable_type<pythagoras_point_box<CalculationType> >
{
    typedef comparable::pythagoras_point_box<CalculationType> type;
};


template <typename CalculationType>
struct get_comparable<pythagoras_point_box<CalculationType> >
{
    typedef comparable::pythagoras_point_box<CalculationType> comparable_type;
public :
    static inline comparable_type
    apply(pythagoras_point_box<CalculationType> const& )
    {
        return comparable_type();
    }
};


template <typename CalculationType, typename Point, typename Box>
struct result_from_distance<pythagoras_point_box<CalculationType>, Point, Box>
{
private :
    typedef typename return_type
        <
            pythagoras_point_box<CalculationType>, Point, Box
        >::type return_type;
public :
    template <typename T>
    static inline return_type
    apply(pythagoras_point_box<CalculationType> const& , T const& value)
    {
        return return_type(value);
    }
};


// Specializations for comparable::pythagoras_point_box
template <typename CalculationType>
struct tag<comparable::pythagoras_point_box<CalculationType> >
{
    typedef strategy_tag_distance_point_box type;
};


template <typename CalculationType, typename Point, typename Box>
struct return_type
    <
        comparable::pythagoras_point_box<CalculationType>, Point, Box
    > : comparable::pythagoras_point_box
        <
            CalculationType
        >::template calculation_type<Point, Box>
{};




template <typename CalculationType>
struct comparable_type<comparable::pythagoras_point_box<CalculationType> >
{
    typedef comparable::pythagoras_point_box<CalculationType> type;
};


template <typename CalculationType>
struct get_comparable<comparable::pythagoras_point_box<CalculationType> >
{
    typedef comparable::pythagoras_point_box<CalculationType> comparable_type;
public :
    static inline comparable_type apply(comparable_type const& )
    {
        return comparable_type();
    }
};


template <typename CalculationType, typename Point, typename Box>
struct result_from_distance
    <
        comparable::pythagoras_point_box<CalculationType>, Point, Box
    >
{
private :
    typedef typename return_type
        <
            comparable::pythagoras_point_box<CalculationType>, Point, Box
        >::type return_type;
public :
    template <typename T>
    static inline return_type
    apply(comparable::pythagoras_point_box<CalculationType> const& ,
          T const& value)
    {
        return_type const v = value;
        return v * v;
    }
};


template <typename Point, typename BoxPoint>
struct default_strategy
    <
        point_tag, box_tag, Point, BoxPoint, cartesian_tag, cartesian_tag
    >
{
    typedef pythagoras_point_box<> type;
};

template <typename BoxPoint, typename Point>
struct default_strategy
    <
        box_tag, point_tag, BoxPoint, Point, cartesian_tag, cartesian_tag
    >
{
    typedef typename default_strategy
        <
            point_tag, box_tag, Point, BoxPoint, cartesian_tag, cartesian_tag
        >::type type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PYTHAGORAS_POINT_BOX_HPP

/* distance_pythagoras_point_box.hpp
B2//VWslxEzoDW7qyhfLX53y2xarGHwS5AXlhtltV3qCMMXPBgQ1wqsLemvZFQQ8rrShytgurMPSHx/NhBs8xr+bzuy9uUVpe/xq30ZyLdnMEqEb2Jy6YVnYQb7XZDmgjgUojzqMOs+ncb10vBwYC0ZNAlBIFNJKLCpc/uTsb4KwlGGJww+OOIwYSZwgr7icHFHNp0K4Catl3BFYbcerIC8o5EATzEV4e0I1h9E2p2VEhlr7DHlKBQupQY+xu0a57AvbzrF6qBFzDqwD3c9LT8C5vbYk7nSA0ON7nu1xMGKPss/hpG+WGSckoUPjmTa0IU1Zc2d0vH5P2/39FbqNEW9T5vj15uqbBDnyrPOOvSM4048+Ct7z9orAFSH2/kZNH6s6IWqthBgBQazrRITbsidEwPPSuLBJTV+95jK21Zj/l4MCrDYVm2UOdmJM08hEJYL77DH1xZzwkYJ2CKnydLDAUv9kbCJlZk8nQNyRJY4GgdNAnjGj5HsUsbsD45jqyR4f9DGioZZ9L2/yjFv3RtrLxETf/3DRMARRA6Dwa0sIMsJkYelwz7DyGOYsrQzd5rWalQlRxyNvEmDm9JL3D2GlNRIhBDRB87t4JldhLPQHKME5ZTAfQ9ULwHc8OoA31feyWuagpJwLcN4c9axwGMgzoClYtJjwQ0YsxBhh6u+/rPlhwLB9309LIXC0pwL7CMcnzzUCE4ctzJs5YMJyus6l83t2bIW8oekvFlaEuQCZo9mCwhXnDvIvAATr8xP9rWsUvAkrORqt8+DMCs1Q+JoI8SI02TOY9TP0tPvyVQW2C7Ujm6G1/TDLL6zHmAIKc2ZZJvpkLlROygXX1dQE+QKu1iQG5BiThEagc/mdnuU7oqrf5NdUzHA6w8UgW8emnuK1islZqK9klJJZn9Kv3k4yaprWKJGpGlJIIkEy5Cdb+d/nBJWC3c5NguJObT/QDmynnWNeL40071psusUbr35uvR6Ytr5vAbofiI9BaEeyY6+0LUC7Py9tk96/ftlm0QDzeHzk3k6JPj/9uNm9D7b7pN7y+TpNdMhRk4E5gtmW7tJoF0UfXWJXw5iaxuitZ5grv/M10HlrfcfPUtAAlaG85qbJjE/Ey6nOWGPCHhxZPV3t28GIiTWpd9Qh8ZRgNkHiRyex0lS6hUldL97P66DH9rcsMalPXWjRSjMwVnUIledlBqankm9j8IL5LO/S6uXpfj5R+HHzDWjdSR8UphI9+i/P7390X+pful+PfRn2n3Rf/N+6n53aE0MijhTaEzZRXnmVnq1tU5ysMowFCQIC68W15Te8E81gz3hbGy9DWPQzLk5GAxSy1Xg1EGRS6lnK1dgEVETFeblapsBy3dxZ1RvL9w4jHusuUvdrrOf+MrXy8+NwvEVIS4yyrqu9G/KsYyTV9guITmhAnDK/HKOvGPtzJpANGtFA7dCBwMMPfBhRtU+bYMoOY7mvgRFMLtk5paOaFlhOQliYPsSRJ2c3NJQ76MrAraeDt59qjPf78XHwJtGao58I/Mrmmj4kd1Mre1eDirE63J2r/zexB3slMgaDFo0swJGz30QENlVywQqogko/eMyEnnfqUr3kniCTSLv6sviw+vzlQL2lPXPkXJX3ff00dMT0G8HuuWf6enB//1aT92VW9ptzNxXzY4L2/m1xOhwY4Srnt24XkLSYVTJVPQsEm1yvu6Dblzke86yENxHbitrsTUFX0U79zUApruqNRp/ugka4Me46iCcNIru6CEatNIxSrVbvyLAU7jCsjZ7nDSh2H4iZmgT0QC/MCqTNQVa4+8QO2gVSI98lH8dv+3pWdRcACCz30xCCPvidZCYTg0k0GsEukG0At9hn7yW7uuH9DNNPDINJ4whKv2OoNMO/HRF/ew98QOFBQIpCBvW+pp31dZv0tsOX9VazlReES16KAAvImO/O1zKD13em0MvX8y5C7SeRCeKmmT3uF/Qh/AGUGxe5REmRO6An8O3nCn6LojJUUCZlDuSbkYRO2p096GqL6e7RgfCDIr8tH/gM9Q70ipR4g+Ohhjm+FGUUOVwoHEOjsBfglHw8UatsMtD9WjgsBDOCGAeyjLYXkDG1bpwIwRQARYFpIC8Eo+G5bI3cBtQFtBrginKBCOOGUM3WIt5IXEDa7tgbWxikzzcHf1myF3YNM0jtJuDFvDOMR4cufFBy89BLzkv0tAzisdgsWe1Xrf4E8gLvJTr6jKC43BbT83pJrfPWX0spkgoMaZZm4U5knYsdgKM5PnXc815w2Vc6Dd6udfruZxZovAWWXlE/Ok99cHF85Y4mwpbScXArghgQ+NvvrZE5IHIffBFPPQdTQfSszgLth5O16QIGGFgrlInMpN4+8NNbGN6mFJjwjZkiwb4QzhxoCh5OKrmIz4BILSRZQMYv+0l+WXw3c9LLYeEJHfiV2VvCVgqbEM3xpBMrLfKV2tnUFISFwH1tANqJBjOiNosMQhWK8XDK6hCTDlpN1ptzVd4SOiJQDVhNjGrfuacNwS3yDY0bfVIoFwY8kdk9HydFDEboHt8vbbOvT9GxDnxOSJeZEhZCMkJmTojC/ViZrpreZ7LxDtcV69hQP8SbggH4orPX32PwwxHXeOtYDyi41S0D57T6OPHSfInE2QJmtWxiLHKCjAGqI/fZRoVBRPneEN58HMLtM/U/JZVg7UWrkIduYUP5Ifv9SoRO0BT8ZpqlS8YQyyBjPPgb/uAXdGTCi5xA/HgUiRKDpP3KS2TzRqdQ44fo2wzv/T0KmclikSsijudkDaQk86nYSGxBkbzDpGtlFCZY7MsTo5GLsGYJImimKhG/9FxcoHALvTmvqRR8Ah8k4fH6JnIYadv9SAOfbddu/oH5+vHs68JzhwLU/X53anEja2sbftUt2V+7105z8fSeYo3U5lJxEtyQDMIIKmSEH+2UPE5EE8IU7+y4yBV6ijvMoca7dffxZS6l1sBH68wOjw6rDZT6bBq1+XVr4Jb5JgwCWr6IVhjvy5CXR1Bq7dpzk9DT2pErI65exuRuyzKn3P9rKlQwvTJ2ddP16vzNf/84AZZ/1WbOIvwLAcEtt8pLA+Tjf8Ljcv/S5SF4erP/pMux/9bl4tTxCmNRtCFfS+XL4dPEq/VTSYQ1iAExPhAiZjBmNPuiQNiBOsi93J2Nb/5sdjs9EWgkYOiYBH6hAmQURKlGQ/JG6NHLTM/pwvIlB7mmafYWOLenx96jWn3fc83pGpXRad/XCMdJXdCXDdOrSfDu91iEMGIGOnSaVFlcsLP2kc/3ayLgM3jvZbzJNAUTTPANfqCAM5rUdzpgOFzDNLCrNxsEeKIpENfNx/T36u1UquOAsVt7W9ZM7pe7O2C4YdOPi9lVfFyBg8/Qbw5sr/clBwQVtKlp+moIuqMBN68hxzpuTL6HjEB9k4H0pu4/XC1LEFDz2ssTwJGyE/cB6KEnCp6PV6fZhf41H0ctG+zcVTY9X0O5JnVb7NyHmtsf7SO6Pt/7sS7VkOTD2HbHNCWPRwerNV4Idz14SHFyodIHY6k7fv5tKNcj6zWfJyRHSX1wVs4xIZpNAGi6XqM8IMqdQ9wWTXZTA/EydS1Oobi5oQ/7WtVaUogftiiM1ihuQJr+/8JuhIwh2IFeZjVw+qKkcPNMSykXef9ikNO8gSGRxwk4L5iU3i6m1KzMQWXjIt+Jx9FLrb5usOmkpHBStJuFNAy4vMTOJleI5ssONLeCAyZGT2vH5a5M1bTLPC1tZ05TA0rwQyStTqD6lyK67rdrS8ycvgikSb8Poqwe6HbQNvUGHkaZxH2gD6QX9o03bBNES4FS0OCz7i1Q3UZXEFZCDIh8tL/Y3a9uq2SiDSypNwu7psNM0/KM7b0RXCQ42UzXKxrXzejJrFAOUemqiHqOCOAQwPV/OqmlT/2JYKTZp4CCCcc4gNYmr70ozDxz2bdmYa0ZBxdmGCaMRPm77Px3wY8RSCZcv8z1q7wfV7+UFhDjkS1/2Ma57ZPV/76ScE1Ol+vr5hv5pR+YdxmGUGq64Y3kxLW6qJEy6bc8dBN7bphq+u1105FomuMbcTJSo/O1KrkokmSMsU8Fqz/vShS50K52G9dsLNYWRbp6OK/78fCr+6b4OvJjp0NXO3LEropbSigEo+eDRpJZAEMvgfGgJxi0JiI5K7f7S8U6W3YT/0Rx1ckbU4g/kDARMEZCBn/l5p/k5btB04/Omt73IwARVwhsAadwR0E9ktMAQrQyCc5YmwJVAAId9BEEL280i53U3xqhN4eeEmdYSa7Iu6aDLX+syfjmYOXpJkya2goEvVdILpUDBZdkCtaWyeQ8MI27qrZpn99+dk2K7D0637zb9MZo5QkgpaPIGvD4F7XrxlimpK9HpUEQGi5J+eUp9E1rUOUqwEvK3UfVzENcdh5FV6j+IW2Hq1J3clDhNbm61T9rt8lALetUj18EYs8QIeQgX0HEhXOPf0m7EYSU3Qq2w+mujf9bYF0c/Ye+Vp6hUKjfQ4RrAPhmFWIBOKYCrDQ4Ky1LJB8mRON1HoJZqRkGXxMxXvkOmwY0EamadMexAFQkGMeDWQ0DaFh+G3dyJSHbGdhkpmAtSigSHkRjbPJPUJITm0ohWDTB0aCCGyIh1+0zuRn7uuRujDf4a2Jk4Op6RZsilmVmDVRX8nIJAozg3aulpqwnDgpk7IYl4kgQDTnaVv7vAxCl4JcNRSQBfftr2rgWXnd9TrYr4JtIXl+c51AhHJ5xSd9v+KtuDL/vW8/7LtfXXVkf2rszgu3X76uE3B5XJpyXZYSpsKucUHsu7CJiLy97+QZa4tmqPFG6c/gBRMQyYy4Oec4nl+eF/tRzf1My6iCQ2gmjnD8L7UjT1E14ET4SZVfZzDbX7yiCyeOLZy/Udh0ig5Qh1hKigaHNKBc2To5X04dj/OQQprdRVsOU647tVlRTMe4x64mp9h6Zi9tfK7SsQZZMFdCRdbzY7y3vCM2I75A3R5wIx9By33/uZcd9AVevEeIiBfEW/zcf63+YN57mX/quryx285/eZ+b4R9/FhqtSpsv/6ntoT1P5U+66SFT+fJq/Aw4LM7MdLiQUm1PSxN6If3fADsgLeMGO0IhSn6mdUeCUADAVFFlQWmMR50zbcZZ2kwp409kFR2pOMcJC1VqoZ/dnhW5VkwVUb8/XK8Qxlo/PQ6JueOf3juvXJkZNq+vnvSnw50W/68vePY7DJvRz9XbIGy/fOmL4T78Bkvearu9TnKZml/2tx/WP78TtXww2eqKIm7sn8MK9EDdYK7tLmIypCiPG63uRIG6qWeBs7zQti1vgqmIi7NYHDtCDj0fIVJRi+VpGK5/WZtFtfKxjKiPrzcFounC9PCwX8X0pV5QdEgZP0DZWpQLVmta6GhRkYFy/fsem2MHY6N2+66+ojDSh1tKixlo4dh488TuMB/BIdJoVLghUF7PaXjAAmMWsp/E7VmSvKHfqp3V+a5IuY3+tUALqhJnEJlb0QnMNm4FAzsCKqix/1qf336K4vZDHganxVfcuu+X0dZBqNwKR70D6gLaZ744BHaXau9Y/38SXwR3pc/tP7LiHHYatXkVFjTHvtM73LQGYINysx9QFnNsbBaxkvZ/7uptdQjtNL3HjKlhzd1HE8In7wadBNlCKhlsg24zR8oA4BTnZINzEkAmIRQwwrmhLig99WAeQMJysQ8lU4dYQEk6ZUjZDzWaJJuEW+HEduSJ/ExWBa9NDzOdQHPefFyHv5Ie0Dl8tMr2ojjxdat+2v1PPx+3pD7ZBFkP215FhjYT0Jl5Ux+6u9LYHwZ0DLiNC71YRpvuhSQL++P24ujNm3Z/tj+256Vi29e7hL2Hr/UrAD3EXOwf2sQgUlETmBcZB4HV7/uGID9Or+/1y3lMWUSa2WCmsbDmWlNRYklROxhiPL7kTo+Fc1VSiQbsowNpgNFjfVpr7uddSY+wHgfB1SzX98qPn9VD287UimWDrE168B6sS++N91xB/E3cEYPvxwuNantjAl3AvvRD4uQd8q/nLmd7pKAmY1+0U7Otupwv8a+ue+n52JJFQHBEsnieWthfexXYQ/NnnR531lLnNdyZQzjgYNzaUeYDwbOuVULtBrAVZfN/lavn+mVIgzVSWMwQ5p3xLRGsBGe1TQ1bkCnvQJ2XTFm7FzuDtpPg44MmjFz5mKoCdBORXH0re3MXvVFWdlj8RLZlVfJtZShDUFBBn9tt1Ew5TP7XormcpoExtBausq9IlgoE68WrnqzwSwGrqU8PrYvsLkyFfwH3uXKxtQFbGgTgDwkHV1sSsveF78otveCIQItY9VLViFxITEvSgyx1W77mrkOq7im+Q8YTsfzsreQUl5EHmGNmSWyjSQPOI2bTEX3+Bq1G5rfqRonqCzTtatYuun33W4yrarAwOZuK2+HwH791t9zh+TMNuKzzE5FXoRRInxjG5qTmi40UXqw7LhuBlO4CUkg85cQBqftUeBB1ATUYY8ScSi/MXujzA4gYI2gnhlv8Yjbs4MRLbchlsJ3PKmGEnSuxNihOPr7RnFp49uTjLg6MxEaOeGTE58cDtjUxYxspm5iB3spFLL+KnPyvzw1bAG8ZBFaxKkBROJResakWeay+wtJkhJVKEHkReNKvtx6uJ+Z1/loZ9hmMh0p4gX5eYGswle5IwQ0mkaEPKYoWIp5QpXCGP5KxENUo+AdMOC5WA/qOKul7qJAvHSWUGVLzQaWwLQsQsHJs4RGKwjIS+qFg7+jX5Pb0R/UrLV8L9wQFXT0AhIGkt35yXi/0X2V5IZhNIUoBcW/s7jzltpwOvxp+34wXBRxzfCaIu9UPL3a5XdbhdL+v/4v/4Jx5A+y8ddlOPh/sPcVTgsn/HAzYTZiUV5XGHe463HK2X237iqiNNBawLTErgGjUT50bmfSDcDeJ7nYj/Hj7tJ5O8I/WAjOIWwlSJlbcC9x8IOlCYq+7XU1RMSm+NvnLpKg2tkOaGVxVC+My5unblzdq+ztqGeIkmBORRSFjxMqRLucxVCc03ljjkLZ9ngwPaq5qFIMWvwbEMHzW3/9S4Q6aDMkDrsSCHm1myC4IwtKsPxyQu/10UyhaIAUKFs/i506Hs816Xt25LbGmMJoVJHADCzMkc8iA/hTO9qFU2TD/FhKL+9ePNiWxcGkiBqvlTq1nnT06AUgfX75JXdH5EizaYEIF8bPUUzUuXd/Oe7e/0PLYf4w6WFKjlu1sK8klqhIhh5+08meOHJU7auXCgwLf1MIqopOiw4Mr9DCqBfXnt1yZowuHB/bv0yRR+EtqvHbehETI9PQoqs2TfL1POGKp90NsvS8qifdZxaEwM9+ZprywlPDL+6bAmPHAqI36Oha0P4EN7MIDeDnsw0+lG/tw2BI8DcARBRKB8aMCN+RWh0LMxNYYQPlkA3MBcGwu9sx8kq4+JHCeo6A8xZevT0kKkPBd8fPxwy4IKPAHpH9XNkQwqBojal5h/d2lGQQLSpY5Gl9usUvvM8vf3SFtadIDzmfC5YixiifdhRo3qHWX9wd89UYbuNFlXtjN/i832+XOGf8vO1vnfRWx1tkjKy4Nm5h5oEtxf1l1Z59OdEJK/iBQnKqL4vS0oOHXDHVdvguN0gFmhjlNQSSyN
*/