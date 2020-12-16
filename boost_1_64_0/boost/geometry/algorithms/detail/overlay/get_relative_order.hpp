// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RELATIVE_ORDER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RELATIVE_ORDER_HPP


#include <boost/geometry/strategies/intersection_strategies.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


/*!
    \brief Get relative order
    \details Can indicate which of two segments R and S,
        both crossing a common segment P, comes first.
        If the two segments cross P very close (e.g. in a spike),
        the distance between the intersection points can be zero,
        but we still need to know which comes first.
        Therefore, it is useful that using sides we are able to discover this.
 */
struct get_relative_order
{
    template <typename Point, typename SideStrategy>
    static inline int value_via_product(Point const& ti, Point const& tj,
                                        Point const& ui, Point const& uj, int factor,
                                        SideStrategy const& strategy)
    {
        int const side_ti_u = strategy.apply(ti, tj, ui);
        int const side_tj_u = strategy.apply(ti, tj, uj);

#ifdef BOOST_GEOMETRY_DEBUG_RELATIVE_ORDER
        std::cout << (factor == 1  ? " r//s " :  " s//r ")
            << side_ti_u << " / " << side_tj_u;
#endif

        return side_ti_u * side_tj_u >= 0
            ? factor * (side_ti_u != 0 ? side_ti_u : side_tj_u)
            : 0;
    }


    template <typename Point1, typename SideStrategy>
    static inline int apply(
                Point1 const& pi, Point1 const& pj,
                Point1 const& ri, Point1 const& rj,
                Point1 const& si, Point1 const& sj,
                SideStrategy const& strategy)
    {
        int const side_ri_p = strategy.apply(pi, pj, ri);
        int const side_si_p = strategy.apply(pi, pj, si);

#ifdef BOOST_GEOMETRY_DEBUG_RELATIVE_ORDER
        int const side_rj_p = strategy::apply(pi, pj, rj);
        int const side_sj_p = strategy::apply(pi, pj, sj);
        std::cout << "r//p: " << side_ri_p << " / " << side_rj_p;
        std::cout << " s//p: " << side_si_p << " / " << side_sj_p;
#endif

        int value = value_via_product(si, sj, ri, rj, 1, strategy);
        if (value == 0)
        {
            value = value_via_product(ri, rj, si, sj, -1, strategy);
        }

        int const order = side_ri_p * side_ri_p * side_si_p * value;

#ifdef BOOST_GEOMETRY_DEBUG_RELATIVE_ORDER
        std::cout
            << " o: " << order
            << std::endl << std::endl;
#endif

        return order;
    }
};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RELATIVE_ORDER_HPP

/* get_relative_order.hpp
D4OCK/iXawf76xOM3zip/x2PPv9ZE9wvrk6Gjp+5fr9aXad+Q71D80DvELfSGDRNAcmiPRFLa60HhUycMX+ZlHlAOg9h2sIleZ/KCCGd7CvDzqys7Bfxaw+8hvN/WX3+2ewKaQW9hUtC2ocwZo+i6EGhEoVY/XTFGVjV4vuJJhfG8lVrft1SZUYf2TdPXhXom8tmh/fNe/WO9vrDdTveawC7VEd4x+tKKgl1vM5jB5TSQy1HlbHT9TZ1JJWIftd+TAt1vN4+EcE+8hHwze7x11oJriG162Wpcz7Ipo83Xi0OyH+uWI3GxgAKlFLFjUJv4Y9yk1+dN1dM8pymHO7yW5fPqAVcKL3H4fX1ag5rhoBeWgNUglqL7YYL0XcyWUU+qQRa0kDRv7MXZFxeEQmZ3E0x4o4P28kZ0YcbLfMCu0wdgb5IrOg3J5OSrtrUmV/K5HKT06d8zXK1FZtOJrmxTUyj2HZjDh59J+6w3InLbaszUWyRO/5YS8kjPbxYJn0TF/tzaoXg/F8wMjnz+Wo5u2+4Uj8JctypHlYPccAy6C3R1d0oTgwtEV1hCvz+PskFJRNHui8rjtPn5y3lzsLwytD8fK/Wq7eYn9fcmO/njtS0EPpFEv2aMPQuWmsd3eZQt7rU9eqHzHU6mkDwcLzCyWv22Zw4CTz/pPXZf/H66D99/e7fvL72e9e//tnrVfr5p+WB9TzF96jNLAy06NzWYGO/Xvr8A6awuuTIKxGBexConwfMX2IU/tw4zD5ATISbwoV1Wv5r3g3LH6SC+XdG/r/rfFfo/BxHn/GBGzguPUNP5/Mvj+Lo76KmeNvVWnEd50iuS7+fwaNy3PMuRa4trK0yDDLnWKyi474Gb2t8y6zTa902F03RLtxL+jqKB1vb4KiFTeHMarWoldCpOrHEJK+tlDu9F6eU1Hy+6ayfQH9RV35Tl4XGI4NuCnT6ofjbw+KvOUN857D4RmeIvygs/rOs0+NPLg3FHzhD/Mdh8YsQ/wv3V/rbdRv7mkyT4rer1Vnc4tmn69rbUteOui+AX+raUeracptZhmPyeoynHlORE25FiSNUT4Mk1LBdcYpuV5+WdnUmvmXrU5rBql6lbXJh1cDXzVg9hd1mnMFnN6evmxZK8qJM0qs8ZIpTtT+69LFojbP0OPcy1ptKCmMLeXqp3MSLba3lRZC3geevQBNvUBgLW2XRMezpp6Z8st5s6OKLcJvZs3mxYnD6ZYFkXhb4fZb8zE9Rqqj/d4SssY+B86DWmapY6joeOfXy4mv0svtl2fuVUVwfoeQdtWd6hpb5U7E8tfIAu3b3FcE0kXIl+pKykLw6a3fVSZWDL4madJsiZNPD5FRn6JClsId5fRfUSYUhUgx2mORXyiCjf0ijBrytl/IEjwhfCkZc8phv++JrdZYVWcz7SgNaca22vIfUikAtDC6nzmZTZwfSpgzlWb+RLl+b7W2iDHOLO8mbJv7mMV9FwaMp8pB7rZJ0qiaBVbslNeoMBkyttRYfawV79BCo4ETKR7mKtZVD2B8m2g7705z2J5iwDAk7IWHA/Dh081PzlTA/twTNzxqW63YxQhstK2QuvuzJEsta0T50ihtN2gU9grMqlEpXP5TUpaJ8YaVXdxL7B6TC4smNOnhIgLkXKbim1UDxuY3V35/iQR6rthYxKSVZ3o41r5KTgYKTu3nE4QH9AEZvETSMQYP9v274/7sfFy+I9enHa3MBNUn+s64m1U7eD+phocLwkN+McjFIjVE8pafQ0I1ZvmEmHF7sZRSj0W0ub2vuStqPluFk4AKxKHtISd9snfEwbVTSZhq4oS44E3v6IpqhtyZ2FuSVmKW+S5uWRZsG/xI=
*/