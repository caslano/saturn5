// Boost.Geometry

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AREA_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_AREA_RESULT_HPP


#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>

#include <boost/geometry/strategies/area.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>

#include <boost/geometry/util/select_most_precise.hpp>
#include <boost/geometry/util/select_sequence_element.hpp>


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/variant/variant_fwd.hpp>


namespace boost { namespace geometry
{


/*!
\brief Meta-function defining return type of area function
\ingroup area
\note The return-type is defined by Geometry and Strategy
 */
template
<
    typename Geometry,
    typename Strategy = default_strategy
>
struct area_result
    : Strategy::template result_type<Geometry>
{};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Strategy>
struct area_result<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Strategy>
    : geometry::area_result
        <
            typename geometry::util::select_sequence_element
                <
                    typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types
                >::type,
            Strategy
        >
{};

template <typename Geometry>
struct area_result<Geometry, default_strategy>
    : geometry::area_result
        <
            Geometry,
            typename geometry::strategy::area::services::default_strategy
                <
                    typename cs_tag<Geometry>::type
                >::type
        >
{};

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace area
{

template <typename Curr, typename Next>
struct pred_more_precise_default_area_result
{
    typedef typename geometry::area_result<Curr, default_strategy>::type curr_result_t;
    typedef typename geometry::area_result<Next, default_strategy>::type next_result_t;

    typedef typename boost::mpl::if_c
        <
            boost::is_same
                <
                    curr_result_t,
                    typename geometry::select_most_precise
                        <
                            curr_result_t,
                            next_result_t
                        >::type
                >::value,
            Curr,
            Next
        >::type type;
};

}} // namespace detail::area
#endif //DOXYGEN_NO_DETAIL

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct area_result<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, default_strategy>
    : geometry::area_result
        <
            typename geometry::util::select_sequence_element
                <
                    typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types,
                    geometry::detail::area::pred_more_precise_default_area_result
                >::type,
            default_strategy
        >
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_AREA_RESULT_HPP

/* area_result.hpp
UAXZ10J27HZuXkDdx+nXOaV/BNO3D0LlMFwJjUabntNoqMyX1UdBensb7sJiVPwjDG62E7hzEdzhCO5km3qYlTcbXJebrkiewJ5ioEMI6EoTaA4CfSnXbhAHr2yot7mUIqM1TWxbputml5mluTQet1zhhTKsOYKYkRAlB+58LYZ3rH5sMCeQe892jlK5SlWOJpljkMoBqSlYHLCXcd6FpCK91NJVpPkAdQ7paXHlhzXzQFuq1X3QcZYqGe3D05rwUArRV4kFMoSpgGMdoY6llRyNg/T3/FAkc+o33Mypq3RO9Tbyqof0EvWI2DyKGEJrExX6+jxbZS7K6J/RhG33utl2Jx6rqcxlIQ58fzUw12j+DxnEUAJxmwliIIDoenkg0pRQrmTLgwWWhmQ6Y38qaUqqJDv1erzN9ZhECyqOL9ZBPMfxeSogb769sgt0M4JzFznU8eLpWh3HDCQ6BwNzkUOWYlXhL0ZXw9o5oIMfLHzhZlNGpORVPJ5RO6Pfb7BomcXtqvsbeREhYZOM3VpJtphwUCpGxK+4nGoChvngC+eapxe64SEO+D67zG65DC/VauVCh4HohyFNPa86hyVnPoTfDZTqehXeesTe7O9dVGJ4WFKT5IaTB4I8RilnoQMneAGlrheyGZWdtHG9khRyE7ipgGFsWeAAY8MxAKM5u9fBJDwfUY3oqJ5fn4zqcC7mXKdiTsdi9odi1LB09hW2a8hCNYE8eAXrgGSxfdcCyJHE3PfW2/Tr1JHadnkyUiWM1M/nOyD1/NGAVCtZnGXDRiw1BmBKatwjVdhaiFafZY2iPhgz1eSGNTw2bRA3seG/qvD6xjhZC3hTD/xqHQTaHE7Z21E0xUrPb1KXfhZ5ihMpmXh8OZQBGJjry6Bo/6uQBlMss/2/ge2fBV1yjobwClrK48CuoYGB3LUUog9dGo8nlnYMl3amU2knYWn7QWkJZW1u8sKH5ThBNdQoGt94BU9lPFeE6B4Bl/aXK5Pnij9VWq4+54ElmbJMxGKNi39smGW0jGhpLKdzef5SQlQSmQToboJCMdAotieVALjramEnYqc4IffpHDNwgW1C3GqYqJGkTsfYVWY15JsoYomxQzBfvCGj6y0ffB1gonHTPIHGTyFSOQAKVKJQhM4WuVdpOTx46kpZ6n02SeQFscXrNHWtJEybOqlf5KJdKU5XLm/tA4obsJK82H8J5OZl8LVgascpMuzQ5dwDogSZn0KaUBbKbcjCUqnC7tga7UKZFFGtYgZ4vxHZ7Q2zg7/9NWC3VRkue7Q/voGVPRCoQnEKoTgF93Soa19/oEr+0BxSF50CZw24qHIDDi/LZJcb48yjjMb5hMZTJhpnIRoHZtiEExetvpbEEgfNta9brWWI+xHEt02IWQjxj+kOU85ScUFkB2lNBOiohr9MBnmiHkrC455WDYq6DjjFrSNreSBsacCtFQcp2fZ5llvoQDkwxuagt0SF6nrpXomGbUDRhwMbB12HF0Jwn1JMsiZ4Y/WVaraxyHklWBzzABUadRdiqNlRHIpHSLBxfTM5ivOYex7guEZxC69RnoHGjlBkvP/yXfpIbd4+VKlisyEVZ1Y66qTCz+DN8fNtbvcD5tLFRLPd84LQ7q96nSqF6LV1GpVq20m8sjQeN5MrnflnOrR5pr15p5nbhai/2NFj7mYzt8thBbSZDFA6sIaaDFdaSXE8zaLFdp2GMxrtrrGbSbQzjCQ6xZxiPjwS7Y15iJazVBefRV18lj4nc03o6PfPHTQszVpwspGAFpSzZKK/QiI+wUZJKAzLjGDDgWal+fQW2qLRTWPW1TLatOAp5bF8Z3E81eRUsyajsSbvup2d24hRKFQ=
*/