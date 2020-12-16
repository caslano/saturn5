// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014 Bruno Lalande, Paris, France.
// Copyright (c) 2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_TYPE_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_TYPE_HPP


#include <boost/config.hpp>
#include <boost/type_traits/is_floating_point.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL

namespace detail_dispatch
{

template <typename CoordinateType, typename IsFloatingPoint>
struct robust_type
{
};

template <typename CoordinateType>
struct robust_type<CoordinateType, boost::false_type>
{
    typedef CoordinateType type;
};

template <typename CoordinateType>
struct robust_type<CoordinateType, boost::true_type>
{
    typedef boost::long_long_type type;
};

} // namespace detail_dispatch

namespace detail
{

template <typename CoordinateType>
struct robust_type
{
    typedef typename detail_dispatch::robust_type
        <
            CoordinateType,
            typename boost::is_floating_point<CoordinateType>::type
        >::type type;
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_TYPE_HPP

/* robust_type.hpp
rEVd7s9F60qvPaPWfFHzBO9pbhDxgPaD81hlx4aCoM4a1NvkCvslyUtttWX0+eYiXF3lpszUCy5IHLcSAdvzj+4sLsxHJxjM97t9+IV50f7KUjGvcd+XOHTZiU4PZdUovrulcD+OcO0V2OqWbGakL14GRu1FdWd3dPrfmbQG1DtIXjUeEu54aMaPB6bb4yHhjodm/HhYcsdDcw3joekZD3p8P1Tqj6pNoH/o9jgvv1vV5baS+m6NDKxtOFZpHXrvx9U+R+q3C2I1bHSj04TIdV1schrlRrmQxPaI59mfVBvreabHzs0/5dOB7U4U8T3vp3WrKH8ek2IwJlV6Y3yiULgPdzKZnEwVxEatptL/NNqn3X9Po6G1OrQZIlNQNZJhkAoPiI2aqAr98gD6Cm7ML/HxPn4Y9v89P6Hj/OWWWouD/4/YhIitm/LfuQpaMhFlMtdc6cwtz+kMVOBKbdtcq6zccd3lNcpKcY40KmzPkm+nZ/QTBmUPeNwZB+ZvKOMrJCa6z6CMARgiPB/vqnBn+3E8GBmeGFd5P2cwX7NIUpf6xy3JHlfT2+dJWCcF7V9My9YnFVHpawmySYoXDZkm9tTriSZO09mYCXJ8noom+rYvS8V3G/GtyxOqVEUBUF7olaL+WuofW1iYlbrjMNIgE2zvoXsqXZQmjeJ7kxEqz2T0yilnzHyJreR7jUijGOe0XQ5r/t0TsRPmPo9e6LRG9oKO77N3vONIowGT9IH9d9grCHe4H/G5sN7mg4nyX/GBjUHfeQefeBEU6Z+31XE7gY2VD/e6ly1JSP9MbkI69b5um2L3sf6JGO+gd3rgg7dRxNCbPRnFVo7sByIKZNt4C+s1W4C3ZSrV50+CNti+oO3IiPsG7Br24OP6bfCtwK9tn095XBBpVt9XEz7cBvzq+2q2hQv86rYKap/kDuBXtSOo99JXx7LupdJkr+E0jh2GyrxxJzCrr1M07k4NA/9f2Jrupd8Ku/7a0+1RuxzdTtdy2hjbE9vaT98A2Fi7Eu9X3nRD4Eh/4PGcuDG+2/oDpTm6K6KpJGhDW4cSeaJceMMTw9DVqAz8dj/eLTGdCwyvDW+MAKwvtr7lpvWM+sSSTjO0ahraDy8dsPVvO02sOh6d3yyt4TzorsYZSm4Nbaznyw3WAb+2elOap66ahupN5fqTSLN63+hzBrw/vyY896Ux91obkPa/amPlh2voTajCseUTJyBWZ3DmLw9A+d6LeebQyyqg9vBJcPwA2w9BWQ+KMIE/kO8R25iqVHAi17IHmj6od1a2SLdomNMP1PuLC591zjV7M1jthEcV/icP0ZjfyOdsWzgcMyBR0Ntd9u+8uYXhNgdHISNa49qXycT1kO+y9rrqk+q0H/ib3A/o7mjTnD9j8ornE82LNfSZOEe5N3QaGOUmpg6Fwq1Qtutu5RdU8TkGKfse4sSDnn7QVBD9LvILq7ma9i/Njwi6zVnoVQG+T81A0xBdbb55iTlwD38f8puxCmPbnHktLGxiekwf83vHjPX0H5cLthjG2WOB5nx2CzBr7GM9568VadbUl1Hfb5NjIs5lj+07228Q955lOZioBZV947xvv7nk2eexV9fz4DfyHNv7ontA+3bJY5A3IftxX/q8wlbQd4EMibOiy7JR8unzdlzS9f+XTBvnOZloaz5XFc71xNR89sp8YryuwIdit1tyLM5jkduyIvn2SzzdljlJ953CJpZ12e4lMXFeWWyf+Pnn+3BUjgnFw5aoiVlNP6LptjSd1bz/oHlzH83S2Y1K2+9dlpjTmLsyxvZUA0aX4UZ+DPVRUtLjLcbA0XqOe1V6YLuXqkiePkLy6y3hDNfyhx2JnSuHM8o=
*/