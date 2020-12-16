// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2017 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_IS_SELF_TURN_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_IS_SELF_TURN_HPP

#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <overlay_type OverlayType>
struct is_self_turn_check
{
    template <typename Turn>
    static inline bool apply(Turn const& turn)
    {
        return turn.operations[0].seg_id.source_index
                == turn.operations[1].seg_id.source_index;
    }
};

template <>
struct is_self_turn_check<overlay_buffer>
{
    template <typename Turn>
    static inline bool apply(Turn const& /*turn*/)
    {
        return false;
    }
};

template <>
struct is_self_turn_check<overlay_dissolve>
{
    template <typename Turn>
    static inline bool apply(Turn const& /*turn*/)
    {
        return false;
    }
};

template <overlay_type OverlayType, typename Turn>
bool is_self_turn(Turn const& turn)
{
    return is_self_turn_check<OverlayType>::apply(turn);
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_IS_SELF_TURN_HPP

/* is_self_turn.hpp
sM85KMrC2b19icZEw8IKS80HzjXtPXde6MC8uTW+6kZssnSNVuYX24KHeTfColK8fNqmxF6oIdT3RoLr6/vK/0Hyv1j+j5T/p8n/Evk/Sv6fLv/PkP+fl/+z5f+F8n8e/8GQWz992fNQ5dmF5xU8b+Ax8LyP5xM8B/FYUIpsPHl4jsczCM9peArxDDe/LQXJnzX1ZbPZzC8tBbNnZec4evXOzbbb7SlYyvdIWF433/x0OP6O45dzy9//x/NwJv9HWcLYMTDJ9zkxlmJVKwKnlq+yfR7JoxafBsTKGTbuvu6dxhc37+BL1ICT4/029Qp9cg99P17GvFVE4pBKpn6eTQq4a7J84jC0Z8WCArJ42qUWSAsUXnPUdRsFeAVz1smTu6cYlzyJJCIhAiWJquGD48IPOGy1SXhUFCpWtnHLSepC8WsoliNBvKZWqWu9N57KWN+HQHC9cfPvNMsaMqqkiqCxcRWcBaaz3FgDpyI624+4ZG7sIEl1orlSVOdlXCYFNfuMW1nXyEP4ZiWDQyhYC0pYiDCWKp+l+glJvkaZnVim8WhmobzNmblQ+B3baZHNUJrRDBXGBSqlUjOlIlkvJhdX9ctL1a9B0pNSMrBKNlGpaqJys4mqT4RvsjCPsDC7uxheFLEWrb+TteA3azGGtXhUwkJFybwZsT6jbZeNS+adH7uHaZkVi/bJrFgA8jUHz6bdhuTSjHifWDHVhsCXPwFodTutgE1DGuD/GT4ExBtKt8Z34Sva9FDi+OAp+B8SHIDjTXPAM/JAdhLNO0Nr9YgPtU1xpyc6/MyA2Do+OiaIEOPMfFxh7hzmyyq/Ji2byqskmv1iOyuY/4JiRpTqoXds/upmbnu0DVXVWwLaVjLwilFsxTVvQTmIhU8jfgYK3fJENxSaC6ci7X93+H+EtE/df1eYpCdhmXauR9rbkTvY1WcRfaqXoyMIk33ufzyFCTyTHibQdEfQY8doiie5/na3V2VLFYTTVkQh4eo96p7fEUrNaLd5o04lOjw68XljyGMmDi4Ys+ZUU6XgGiXVf3hsWqVghPElBFR6apnGoIwY4wuhmDy1yCs1+YXqZc41Y1IWU2aqdC9AusxLWUx5Y2VP6UpLs/3lqA2ebabvZbA21IHpGvXIGJ6DTU9gNtG5Mun9TemdkflclfmL7nTmpcZVPWaO+fpUmWyqxYxnf5Oe1VsWEsSfjCix/l9hr0qaCrmQy5nqfq2/2f3vVlV3lu2oEh/i/Kbx+X6JhLok5VaWPtk+MVmhVtkCoc5ZwbI1p5i9v1Q11KN6Zu+fjeBoKJ5uYi25Fnx9vTyxZbwjU9rNaXIE4s1BPCZDI9BIM22j6MCjTCL2lizED00+AkwRyuI8gUTMBL5oJvDD7gl4jHqVwP1mTExSU42hZjX64k2zfDflSaP1srTxudSLP75KtJgHkifLTOaP9olbZsrEVUoeiEADUZ/D2K78j0+fah4pIQuGp7DoF6pxllfaET2JRYNZsATDv4MvZoeiyXNq3Rrsn6S2eLT9qxMUXiiixl+9G/JOOVBp6BnfxGawqI2CR1CNja71zjtSNrACYr38iJ306F8mnJP5fSeZ30tAtsxBtODhngeRyETMBx7JDLTHcuwGyo7SR5jJ9PYdnyTyxryuiDwK5MsaKp/UK8MQn4jdcI/xij3QRwiImFEo8zfQGny3SzXFHUlKbCPRxmGqQ61ACC9PPrwF6Rk8EutDnxU4l/wAn3UvB4+vBBeWdicnis0f/9q5CllVdrXILI2lj6RZjduM99EsTHyZVfaDPJlP+C9N+DxJxfyAKAtwoNotb14ylpjeFylvueLIDvDVNi3li4oAZpgv9hDmYTPMuWY=
*/