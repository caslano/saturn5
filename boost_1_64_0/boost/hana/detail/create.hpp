/*!
@file
Defines `boost::hana::detail::create`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_CREATE_HPP
#define BOOST_HANA_DETAIL_CREATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-details
    //! Implementation of the generic `std::make_xxx` pattern for arbitrary
    //! `xxx`s.
    template <template <typename ...> class T>
    struct create {
        template <typename ...X>
        constexpr T<typename detail::decay<X>::type...>
        operator()(X&& ...x) const {
            return T<typename detail::decay<X>::type...>{
                static_cast<X&&>(x)...
            };
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_CREATE_HPP

/* create.hpp
7u9/O+G3rpDta7EN1O+sWv+i354w1hLrVnb0tnPtel13L2pdS357lu1BsS5l0287Z1Njgx3r2/fVkbYuYl5l+nVPQsynbOU/5/QxlnZyllr9djY23sn528C0vaOJTtxal7z8i7ES7HM67HOGE3fwMaveaqzpWP7QZcYZ61Von7NLTMddPGDjP4wFIC7kxL1yTs+dxvaCnHHImRTr1vXc8PCnjY0T61T20XuHjLL96ax3YXTJTYxNctbTP/uc6uRcu3ef84xVxHRPbL7f14OM1SFn08m54a6n7mVsgZhf2Q6TL7N31H3PojnvOG/mHsY2EHP3Yntexbl7GQJxJ0LcaCdu76sem2J73onre+NiN9ieh/WmwnrTYb2ZsN48iOu8t31ct2PTXtnzVVtrsUV66fX9lzQW1nHOz0yjjoXv2fwd2/NOzkn9fj7C2Egn7qArJ79ubKyYnoctt//T9nxeTJ99ygqzjjRW0us5r+en6/Wc1/MznJyb9lt/FVtrJ+cZ26w02FjHfYvm/Pzs+z8w5hPTOX//cMTFxoJiGyhbburkp4wNc+I6dph8l62Zs17xysM/tjVTcRvK427pp6cZmyDWo3732xrN2+0ZymKdyk7c4YqhtmZiXcpWGxexPVF37LEZN+1oaybWoeyUXU/9xdgCJ27xi/dZy5h3kpxPmf4ZkV9M51x5w5mHGguI+ZRdue2h69nedXKu8NIGQ2zvOjbqvC8H2N4V0/uc+8jFM+096DjnZ2djxfzKzqzff5SxiY4tNn/4o8aeF+tWv29m5oo7jLG1dmzMK5+UbD3FfMpaP159vrGu+2U9Zaevv/cnxgaJ6bgLpj39vLG9xLqUvbbao7faujg5f9/ryp+MpZ2cR6Qjk4zlHLvz+Hvt/BXFTD2D8niw90Jbl7KYT9m+z40/2lhNxznfV2yIdSv76ciZQWO9Joup35ew+VLT17F9JmbOvunfvy+98ZutmZhX2ScXPdNhbLCYT9k6n0172M60Y5fMTVsb6azX77kHbC9lnPVWKG/yoK2nNudrw4JYQNnJWz18vbGqWI/6+0C5d3vdYudWrEvZK7nvvjHW8cCi9v3kLT801i1mZnPQwn1vdsBX5u8R9SjbSj5eZu5y/Y0Fxczfs9la/x0j+e+QWK9/bRvHtlU5t5OPV5/90PnGBju2wYubTzS2l1insoHFXjsYizn2yc77TjI2XMz0/A7y8Skr9ZxjbKxYh7J1e2YMNTbOsTe3emEFY+Mdu6PwwTxjE8Q6lY0au+vdxgpi5m7D8nG/bcZsZawq1qHst5dPeNxYTd3fjvLxK73ff8TYbDHTSzvLx5s/lP3S2AK1l13k49XOjuxre6L4X9z+8nj3eft8Z8wnZu5PCqLuT2ZMbO+/zRM+2rGkWNffFixv4dhYZVs6llMWcmySsphjZWUHOfaOsoMdayg7xLEFyoY55p3ynx3qWI+ywxwLKTvcsb2UxR2LKzvCsZHKjnQso+woxyYoG+5YUZl7f5Uppj/D5RMcq4LVwOra3DsCa4K1wDwPtrcOMC+YD8wPFgALanN7CSwMFgGLgsVc0/0JlgBLgqXA0mAZsCxYDiwPVgArgpXAymAVsCpYDawO1gBrgrXAPA/B/IF5jfnD5ZhjPhV3omN+sABYECwEFgaLqDMc5FhUxR3vWAwsDpZQ64UcS6q4MxxLgaXBMmBZtZcjHMupuNMdy6u4wxwrqLhRjhXBSipn3LGyihvpWAWsClYDq6u9HOpYQ8Wd5lhTxQ13rKXiTnXM83B76xAzOQ9xzKviTnHMB+YHC4AFwUJgYbAIWBQsBhYHS4AlwVJgabAMWBYsB5YHK4AVwUqqz4Y5VlZxScc=
*/