// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2021.
// Modifications copyright (c) 2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ARITHMETIC_ARITHMETIC_HPP
#define BOOST_GEOMETRY_ARITHMETIC_ARITHMETIC_HPP

#include <functional>

#include <boost/call_traits.hpp>
#include <boost/concept/requires.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/util/algorithm.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename Point>
struct param
{
    typedef typename boost::call_traits
        <
            typename coordinate_type<Point>::type
        >::param_type type;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

/*!
    \brief Adds the same value to each coordinate of a point
    \ingroup arithmetic
    \details
    \tparam Point \tparam_point
    \param p point
    \param value value to add
 */
template <typename Point>
inline void add_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    detail::for_each_dimension<Point>([&](auto index)
    {
        set<index>(p, get<index>(p) + value);
    });
}

/*!
    \brief Adds a point to another
    \ingroup arithmetic
    \details The coordinates of the second point will be added to those of the first point.
             The second point is not modified.
    \tparam Point1 \tparam_point
    \tparam Point2 \tparam_point
    \param p1 first point
    \param p2 second point
 */
template <typename Point1, typename Point2>
inline void add_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

    detail::for_each_dimension<Point1>([&](auto index)
    {
        using calc_t = typename select_coordinate_type<Point1, Point2>::type;
        set<index>(p1, calc_t(get<index>(p1)) + calc_t(get<index>(p2)));
    });
}

/*!
    \brief Subtracts the same value to each coordinate of a point
    \ingroup arithmetic
    \details
    \tparam Point \tparam_point
    \param p point
    \param value value to subtract
 */
template <typename Point>
inline void subtract_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    detail::for_each_dimension<Point>([&](auto index)
    {
        set<index>(p, get<index>(p) - value);
    });
}

/*!
    \brief Subtracts a point to another
    \ingroup arithmetic
    \details The coordinates of the second point will be subtracted to those of the first point.
             The second point is not modified.
    \tparam Point1 \tparam_point
    \tparam Point2 \tparam_point
    \param p1 first point
    \param p2 second point
 */
template <typename Point1, typename Point2>
inline void subtract_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

    detail::for_each_dimension<Point1>([&](auto index)
    {
        using calc_t = typename select_coordinate_type<Point1, Point2>::type;
        set<index>(p1, calc_t(get<index>(p1)) - calc_t(get<index>(p2)));
    });
}

/*!
    \brief Multiplies each coordinate of a point by the same value
    \ingroup arithmetic
    \details
    \tparam Point \tparam_point
    \param p point
    \param value value to multiply by
 */
template <typename Point>
inline void multiply_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    detail::for_each_dimension<Point>([&](auto index)
    {
        set<index>(p, get<index>(p) * value);
    });
}

/*!
    \brief Multiplies a point by another
    \ingroup arithmetic
    \details The coordinates of the first point will be multiplied by those of the second point.
             The second point is not modified.
    \tparam Point1 \tparam_point
    \tparam Point2 \tparam_point
    \param p1 first point
    \param p2 second point
    \note This is *not* a dot, cross or wedge product. It is a mere field-by-field multiplication.
 */
template <typename Point1, typename Point2>
inline void multiply_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

    detail::for_each_dimension<Point1>([&](auto index)
    {
        using calc_t = typename select_coordinate_type<Point1, Point2>::type;
        set<index>(p1, calc_t(get<index>(p1)) * calc_t(get<index>(p2)));
    });
}

/*!
    \brief Divides each coordinate of the same point by a value
    \ingroup arithmetic
    \details
    \tparam Point \tparam_point
    \param p point
    \param value value to divide by
 */
template <typename Point>
inline void divide_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    detail::for_each_dimension<Point>([&](auto index)
    {
        set<index>(p, get<index>(p) / value);
    });
}

/*!
    \brief Divides a point by another
    \ingroup arithmetic
    \details The coordinates of the first point will be divided by those of the second point.
             The second point is not modified.
    \tparam Point1 \tparam_point
    \tparam Point2 \tparam_point
    \param p1 first point
    \param p2 second point
 */
template <typename Point1, typename Point2>
inline void divide_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

    detail::for_each_dimension<Point1>([&](auto index)
    {
        using calc_t = typename select_coordinate_type<Point1, Point2>::type;
        set<index>(p1, calc_t(get<index>(p1)) / calc_t(get<index>(p2)));
    });
}

/*!
    \brief Assign each coordinate of a point the same value
    \ingroup arithmetic
    \details
    \tparam Point \tparam_point
    \param p point
    \param value value to assign
 */
template <typename Point>
inline void assign_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    detail::for_each_dimension<Point>([&](auto index)
    {
        set<index>(p, value);
    });
}

/*!
    \brief Assign a point with another
    \ingroup arithmetic
    \details The coordinates of the first point will be assigned those of the second point.
             The second point is not modified.
    \tparam Point1 \tparam_point
    \tparam Point2 \tparam_point
    \param p1 first point
    \param p2 second point
 */
template <typename Point1, typename Point2>
inline void assign_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

    detail::for_each_dimension<Point1>([&](auto index)
    {
        set<index>(p1, get<index>(p2));
    });
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ARITHMETIC_ARITHMETIC_HPP

/* arithmetic.hpp
GwWKNmrQvr6xKftVkuH729xVYOOvHDESG9nbK8P4XSdcq894aemX2ts31qN5XgvlWOXBJPUB69xllx9MNBmByZdMLejqQfnwQc4wyWy48EED2EWiDK7Ko7/VyKP9FgaJZh8RwDNw6qpMy4z+A9+RJM5aZhKSYjVN9yjyPfbd75cR3TNwI0W+j32gbWbnXdSZQXw7iR1fsyAJ69+Hnj/L6he2KjaiwW3koc8mOccis7rQUyZ/jqO2h9hgAKCF5UlQ9qz/X+2i56GrtrQ+3b/YmOUEIqGaJCSKiqSqqKiIyjgJnSRrb66eInJezDpIPJRren7Cdg4a5pjXn1/QL8zpD0pdAAWFn77YAKyCBaa6m2NR08Rxo3/iDPB8ueW9yVjxXPn7cPNl2ADSYka15q2mpcpQg0KZaNatqjkYavw4c94k92mwSwDsN658VW/r5Zix0vw7JaD7UeXzhct9pe+iNSkrrc6Tbs0xIEnrssR0k8uQcyT/229B98WZ9lviAGBvPz8QSKv58r4xUqm3YZ10p/ZJ/FS+HLXoUfIRwABBmWf2lFnUtE5kzTT8adLVnPiNcYt+ByXgwqY6jCHFHgue+JvitrrXrcTdC3a5zL4U5ZEBwpfs1kxG21rMpBn92EDPfwNyk4DaTuKWxYQbV11VfNflo7nXwlG581TG0fyA9ZGx99sdmmqC5jwYdK0a5AWplUtmVDtG/h2mGdAgX4u8H9DC73+3Q0YKQN8yfk2lxH97Ad09ATZ4gUh32U7VIhrxTY2Esb10ByaA937HKaIT0JqwKTbRxd91FEjtaN1Un7AJhaLncHwjSqXhtJOiawhBd+DqSFlTXLAGJ3kaVF1UhawD3MArx8Idv78v17fX6VQp1tgAMYB1/mP8BUBjm+xnqDJiH5vCPvaVjzbMbA0ggPxOZ0yoiPnzCUz/4tQWNWHLRouLrGt3eC/y7QfuZ6A88NmTJw51o0UQ/II0DCjrybbS7Iw+/CaY3PlwXIueSG31zul4Kcro0tBgcaMpB38J3N3mb03tSCtyoz75mj6Soo/945GX8Wbi1xSXuyFogPZoqyf7CSA6qdp1hE6Fbc3Sm5r/49kUF0PRyTTohnnWk/bPj03Bj77jz5syG+zLg+5NooSs/RNJV3MJD4GnSf7LMnHBC8hICb+xpy+GR1DvBORN7fjDGsWWG5I8vl2WMHVQOVXpfDdLgjqd8pWIiZeA6qZyFrsYHwAFVUKRnJb4peIGm1oecwgIE8QQERzTYILmYH15PA2xkzbe555v2g+WjIO/8lqxfMuTRf8pnASTpo8TjzptAH0YnWV2dqRE7FZ5wbRyBORIhSUpLCC0Y5v4CIRyKG+S+WacSrFRe59VOy6dJL94BHkTYCwu8yE40IEN854nlBfsn4AjfD6yCOl5lXKF3Hvm/0EU/JjMf75SMEVg63/hjPomEHxYgUgA5bMIwiBK45APQ79dEEGGY5rxL5oH4fH6ABOgNKfH2S6TmDZKAJoN4oyDxhdXCJmRB+pfDfK+LgxuOzLnSn4qJPgiL/itMYePe2UUWH03CCOYJ6BNqY0ZvmT9ShAFcMLIaBCU3/MbRcQE6FDCec8QvnjeKt1UCVKAbgk9ZTK8ZNZE7ByD2AK1OwScstNrOtypXpJ6EfL5Db6PgK9zrdSyqJneZ2mZ0iUmFahwQFvCbYeCD4438w2wE9G316xUy8pBfnPf+lZdG0rrY4vkbSSkEX36lfPw9HpdU6wCYEdZhU3bHSRGmHcv/ROPM6NsCT5jBwEPD1NyZPBDAOJPAe7cxgivimDuektictxfSt8nifX3+sn6zXUy1cvWd6nk1ERSoAugk5YPUhd7cMeT9Al6ybPr3uCf1LteUxREN8UVZix97MomxTm0LxWVqKiToYFglL02SeWGz4jwpmcGtZwyNtDqTJp/HiQL2wqVGdy0TwSq4nHiY2m0TAJqgYACfwT9CP4R8iP0R9iP8B8RPyJ/RP34+yP6R8yP2B9xP+J/JPxI/JH0I/lHyo/UH2k/0n9k/Mj8kfUj+0fOj9wfeT/yfxT8KPxR9KP4x78fJT9Kf5T9KP9R8aPyR9WP6h81P2p/1P2o/9Hwo/FH04/mHy0/Wn+0/Wj/0fGj80fXj+4fPT96f/T96P8x8GPwx9CP4R8jP0Z/jP0Y/zHxY/LH1I/pHzM/Zn/M/Zj/sfBj8cfSj+UfKz9Wf6z9WP+x8WPzx9aP7R87P3Z/7P3Y/3Hw4/DH0Y/jHyc/Tn+c/Tj/cfHj8sfVj+sfNz9uf9z9uP/x8OPxx9OP5x8vP15/vP14//Hx4/PH14/vH4AfwHU/9y5lwq1Nd9iMMtWpNWusWIHM2pvcgStFxos+zNFyyEyB3uC4ni5VDk12+Y9H7gQPmufVORgA+tQ9hzGUwqta2SHQow+anYrzK+CZP+Rh5yTBqDYbzWby3ome488K//7NjQYU+TI84uSh4AxI+ck8qBHCq8RupL9Thoz2jErb0f7xtCRi8agd2MgB63GPgUZUQqfxPGGZz73OPQl5WRFuBCrjNgfBSb6pDM9vHUTbiKp13boP857KfqxYniMJHF7x8VhX903/kVyevbsmfLJhCRne92fCCW246Hqn9OtIJ4vNukrwaY8m7hYYPkSd8ynG5avVsvvmwBUg/bAVwAhMWwdE1yzUe9DvL5Z5v5i2yD4EwMCdwB8EqTJ7OM+ryUpwBz3fvu8brqKKlmXCIu85d1Sd3f7jOOUT1lx8aE2+dIIhD2z7QvhO3JJd2/D7fwM6Ckdy2/T1IzKcjQ98rf+CrJf6itbbfWLhP463UMprIno5gHKxK7u22F0tG86+KA6WPhR6G77RXnIb7xMOnxgiUdaD5B23wqPdp+GD6gw/IBPLZ67wK1DEd1DgDnx6L/xb4Jb1G9we/shVMGgwG1Q7qHhjQWyL3I4bFKqZ48V6vfEX3QbJHRq+vSS1YHaGUNmjczr+ab5vxrfHSG6h7sxW2u53oFxWGN9w6STDPbbv5nS82xjox1Lu6TDekvi13KNs4Kso46PlomgoFogGq+417rhSu48wWyuGt+txArWtr+ZtBg2oUYljcvfK69TqBVQsOhzYRmDbdZoR/PpUOwqEuONYBTQ0mf9d2e6ZwssFhMHyAZBtLGqztddklKI1t4X4UGIkaoBwCdpxYg9AkuCTgLAuoJupbunKnYCdqwPlfZCwjjo1q+0ttXTsaq8eZFeT2EHA8KAEwCxvYqgIhlL13mTAxw8cLfOiZ82xh/sk3/A+eoJGe4fiZNDqmVBVp7ltfI/6gcSJ3fF3uSCRgzyRBLwqEFP12i57zXDocSbSvFWHx+NVyZ39QfMFEN5rIBOaP22wHmbsdXN27ylT73Rv/MY1JV4nmI0cK4xoIXbyOXjjDofydNxGy74XuqmXh5WpNWP8dj8vBB3/TPaJ9eNJf4wkDG4CK0NJ6oGOjRo4UbFI4KeeN5W0hyg7Eo4yERogEqZqZyWP/Zm3r+clzaZcsrb/PuNTL1PSDwil/b2KNrt+KanAfKHzahXKVhy4pnb6dzLu7xsAKKH0u1iYNMdRHZcLJhQP8zlpLpXZsMkPZpN3dx0i7q7x/Fd+WUaNFQIQya+/1g2ShUfmVLR6eAi6xA4jFpZykXxk5Xh1cr5JPXZWX+3ivkkjDjspBCi3rZK+g3U089b3B8i879T80eEpG5GUy+q4eCLztK5w3EYWf/WxOKMa0RhSHT5qgo+e/hmbeyyhwV7ZQ70S7WLMqGqAUhQW3qlIrFKu/iPCO9c0nj/BZBaPaOJXRAZF25kk5cDq3onPvkVVmowcGjbm/6bwzO+F9sG7FbFIcIbBWyzFu+EF3nTyM/60IMcDUB0fGMTxH923Fv7rXgfKgXSX+z6n4tEUt4M6FVJY21vwW8hGnZhDGdREcvku4uf8k+kiFLONfh5L32sB2qPjMqoZ9NxZWicf0MmDbfbBsOm3W2MLnsXnHoS8x9AC8vlvLlcICrhvKpf2OmYFGmP3CogeprX6u6jn6fn5X8oro91wmOWk++Csbm1CH3VWPp+N+UZskQbOBPHvwd9kR5D+FkA3u3AJxEyeKftKnvlwAg6D6xGofwEzhDLiTuZ8C9is6b1vIBwifUMMJ90GdvPQb4iz1v7NynMVnJ7J0O94eQf+vox6QjUnp0/kp9CCFsA+6mL2x6dT5KfTghxAX8mRMfunlCjOY5SYERbRp2bU3KGFJrKzJf4IYOtiYjcHpz7kp1WCYT9zE7GRP85ZZ6+QsxL+9I8k1tq4HZEb57hANrmRXwy+RWQ47w8o6j08Mh1Rj5dzKuMC36obXl6n/tvEq9afg93g0mLs3yP7frW5bUJhop81Q34WDQCT2x0B+INc36LOZirjZR8TIlP7s3haOrKIiV/0sDAh/8ZQ3vfzFE4q+ATfJUDUmkfcnBRvekAZYDt/G8xLZLjrcspVruLDpyN8GHhHHKGpjkbGGuQr9pCCEEB0NjBwhd1c11FfdQEr9ZqBroylFs3vzVLc9wKKgpmrtj16dYpw7sQWJJn4/RLVKi3sYdDK4W9pAhTSzO1aK/m+L24FPLWta6DvmuWV0OrE7ebU60onGkjo1sF5HqV7c8R8DnwTh8bTMivJeBYLhXAyO3obJnq/Uy2Lzr32yK2Bc9Gh8jVBPh13b+TZUnEoDvxgvi1kyRY2ER5yxjPxY1B8Iqu21+QtudcDbRIjPhj+JQhW0hg6yb20c4zmvGsAwy4WgOTLybaIoQbdcCSb5v/JulHsPdYJQ6t9Evki8qkvMsOp9dxvR23Pl91wrW5SYz7hmc0CmUL01ubQy082MG58dLtk3L1z5NfD6MP2ptAhc2BXNHJCOLsRudcwNoNvYzTx6lbMKJcogAa1zkZsM3cvnCzfr+R6oxU2P4aVG7GsfQm4Ohe5zMp/myytHcd4H4zvtQDe2Q7bhms/iXA1kh2VTHgCEbQCOsvg+ENKFutBTaUANQ+0ezVd+FX4msZ7XFbKW/eFEwAC92llb2wQelRHy4c4v4qfoxJG/ua7Z9AXBT6zlZmlEnevVedqbnwC9SsNKm464JH4SXcKXr2cxp5xBF0dhokDjzcKlhNgDlMmBmglAvNldIjp9eEofqIkPszBBNlSn3RUqIpO8KK2MaQPfMnpjxLoz/xHkvEPGnRvjF16mA9an9n94F8c0eOHn/pok1cPTmXKja8IpvQOlD6o+1SilFLlpFmE6rCZEX0FRfXdS5Tuv7sbPwePyIkDXfzDe2v6nnGzuw6+VLkGuzGzlNcep5D1TmdOx0exS79M2fmTJt2UNXMHrpCPgeye2L2b5s0uIl2/Ht183yj/75P6uO/EMenGELzfhfQ7fsy6VwB/Y8hxNoYMQA0LRSKhT31xU0VkE96D/i4d5I01A7MTuote6RI+nIpuOwtcg6Zh55XYr4cbuqHLz5sLTG9K5s9V/c5CQuBBGyQ8nYguMppzVNkMyd0c4JXtKP0B52jwI/4ihXhUKyTyg88+p67gOwWFetIiY+V0dsrlXjrw6/ATAOeFxQVbV5sJUXlR8jki7NOIytsny5OE15MEXzvOQc1ZSPp8az7jxi6ktcK8JG604QiUc+uwuMO2HcW27xd6+BGhujxxfGLuQL2mK0JUkRMXrXXxYS1t9uAOyttHPC6RjFuo/sxErR9FfED2FJcN2tk7rtHXlK21ssGR5sBfyLcnqfX3QZaRRn4u06pFio++DgR9v2SLySKd63rppxBcI1TLkCbub2jzDxpMQJZkwd65GpFCazkcJGNWHydXPO3n+QeNDvPylYZRd4EHFAzELTLKWEFjpMH5UXvLY6rn3vcIUaQMN6NJ32O25PpqncbTpX80/bxR3N2qyHoN73OKK3VsyjyJZ2+RNwDDGTuvwRVEK+Z5/GccYPAOuIiP/jJAWezMFr53lW7Imqk/ysr4r5ro7czoaygzfrLm6SG1Sy6Za3wmxDUBdWPRcDRgb9bATqmAd3ago8YMUYgDSyCbe4toUUtkAm/BX0rMX2olzHcP8yDUtsieaXb0j6ayuTLokYuCjgYjhQNiYCjMgWknKKn4kaY/L2HLkCwEIsjIA+0qd0RgGUhtPoXG8wFyoLL1HpFNcBatgU2QYuwpklPn4YoQE/V2wBBR2citu194K2YiZaLScMUAfT1cbJcApGdRT+e4nj4zhWtESDodByJHDOHaz4HCtnwDox9YZgrUiAQIY68aO/M+Lm2IYphd1HfwScAJWklrOo1bMeKM9LcWDB3+tenqbgiCQshHbEAUcHUYDxWLTw9S8y0tJD1Wa/ndIW4cIj/9cjNRTi+W/0K0PZ5t6odfam0GJl6PoEihS0N7pi1D941mxMhV6uJejygG3OhEBdj16z4TQuwMvNrNSsqH8INmLQMCoct+LuisSXfow86wdfSTPEmm9iqJQNTjC330eZijt7vUs39WGp3Wv+PPTNCkwSxEiYS9UToOW/LRSeYpsGZqeyT3lJW674FoZwM3M6YBCx10azries25jbShEUB9sHphngC11Cm02qNkg0yICqw8aCMOoQaaqYIQ47EbiCqsohtHAl20eBxTO5XmNQAYNyHqO5eGSSiSH+X+9vX7/J2CsaCX80r6XGECxebt2r/CRsv+jsds3awMXv0UMQjj2spuk5gAQGe/+62jYUuN2GCpPD/7VWCJ/d2TnIDulUf8i/q9NaGSwEcRL83DUwgvLb0RUNYsOAnOA34pjOGE79wH2PbQBJwLT8/2YN2qbvScwWVxOBg07cPNjwHl5203DCahONy0Iu148v8in/gGoUdvpaJfDz97k4xO68OQJTlmkSEz7s/vJyZ4MWhtjNnblT2IfAhOnZpmzTErK2ricI/ZzcYpceHm61b/8/7x8E/eTTXbDhTtI8+4Io+4QG1ImYV6+klF9XMNkd0beBzAOX+H45LTVDEw0/Ds3Ouh6SkVKienUDfHOlaLgJjhgmf9TkWkA5z9Pfv2ollMmnw2cVhv1WVASYoCtA13u1a3zviJVRJKdJ1liUm7yMh7FqWNSs2PrPqJ9yKqhGwlPrTWHRlpkE98S/7eYyJ10Gkv3bBsswqty+mwpfMHWtlk0NZjv5xIpSbLzuhoy4aZCX9RI6LAcjYRjA8jW2oqJWmsPS0iXRh+GfaVerfHdRkM2UJawrT86VYi/V8+7WVh8L0VgU0Hw+C7vUXCaqKZRqzkActaWqwKucxjfD0vHfy06ZPtjqz5rWuiWeCjMnlmtZd+SsR8Ihy7q2p2H7NCCG1isbLWeVEmlufVbDjGp4m/3/xI3FxkIq4fbdDbgSAEy/GzBeOLm1ktU5kt1mQP8uZWNFY/93jCtuQS8V+/WCIRVowvnEanpB5gDITNYKb1Z0v3UMuPxq6WX7m5gRpg+htMh7uVfTFTjt6i9uh2rTDnctr69nEdm8JvbsReE1U5vCFGWCQejRW28b9gpP5EDH9SaKoZXjkSswi+YHNdiNUuR1R+6v8meCwFZGuDUu4AMu3a+a40GVwAPO6IfQ2uxMsGK878gCmzTOe+cx2EnC3bVYFCKRatPBP4ZzU869qZC81hbuuk+bVMs/XqKSRKKf+EG4lE7s8Pze5tu7zHkJgWzuV5ivHC7MUqH5KLvMr48Zh7y72n+QbX
*/