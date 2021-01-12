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
3zQFW4Qfbg/vEC1Si88zGRbhraAj/skE/7KZbrn32+l2qPpgyVGoAqLguu4Urz7HyQliin/Ez+qourWWimyJ27gcRDR2N2OtpPWvk4+icOt+to+qCrLmjkBxy6S4j6obazpnadw6WoS287U4xqI4xqp+gBSnm9VK3azOcVqlkHP9xnNsOaKhh422Ws+xiHFNb8kuyJw+T5JVwFpBTVqUGA2hxI+jRNo6c8YISj/SEqV5axDj
*/