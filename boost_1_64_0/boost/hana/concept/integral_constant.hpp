/*!
@file
Defines `boost::hana::IntegralConstant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_INTEGRAL_CONSTANT_HPP
#define BOOST_HANA_CONCEPT_INTEGRAL_CONSTANT_HPP

#include <boost/hana/fwd/concept/integral_constant.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename C, typename Tag = typename tag_of<C>::type>
        struct integral_constant_dispatch
            : hana::integral_constant<bool,
                hana::IntegralConstant<Tag>::value
            >
        { };

        template <typename C>
        struct integral_constant_dispatch<C, C>
            : hana::integral_constant<bool, false>
        { };
    }

    //! @cond
    template <typename C>
    struct IntegralConstant
        : detail::integral_constant_dispatch<C>
    { };
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_INTEGRAL_CONSTANT_HPP

/* integral_constant.hpp
XjWsZYKlP652onP1f572Oi0UbWEjBD0ngV+sG5Jmh2SZONtovLIUrzSQbK4Ca1LFRnYQilGN/zkCuYEPJGUu5qhRcX8m4s1iXR5q2wanDYtO9Rw40SxSE+JfpauAjswAU4KpaNfx244Oo70F/pbDpGRMHz9U8Jl9WgLIl6Dw0JZP1puzo1rFPDIotaCnm/eDecP9qQniCnCUEn9uc7OfxawIICtghWzZLtiaEaaZBnLrwJ9I91rbirWQ5lG2riqYFcy9uHZTFCrQpeXCYM/dO4LX/eaNqqq8JjELx4NXYApGOj24wRhgUwcL70Cog0t3Oz0XayLvxDkDJObHksZ+AQ1us11lk06v9eiXaMmH2YcSKvsRTgBV390NBdCQYaMpJDYly6XCqVEe55K9lhmVRcJmW3wIxfpLktRzEDoRvL79pbRjKW4o7TB81w5+doa+auBdNzUlgH7kwQS8VQFyHk1JZ26Vbn6PfiuihLiNi/Pwm0YFbAagmyIOYbY8pwmT2YHzQWFC6csNBxNiIdYH/HVesRerVv6CgJf0JYlX3v3msRzoEfbH87Id8Q==
*/