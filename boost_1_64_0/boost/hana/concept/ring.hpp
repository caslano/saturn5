/*!
@file
Defines `boost::hana::Ring`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_RING_HPP
#define BOOST_HANA_CONCEPT_RING_HPP

#include <boost/hana/fwd/concept/ring.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/mult.hpp>
#include <boost/hana/one.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename R>
    struct Ring
        : hana::integral_constant<bool,
            !is_default<one_impl<typename tag_of<R>::type>>::value &&
            !is_default<mult_impl<typename tag_of<R>::type,
                                  typename tag_of<R>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_RING_HPP

/* ring.hpp
gEa2k4afmNTfipjvVtDow0PK9GY8O3fTtvuEHnKxKNVBDf9nyJONs5aJO9yBnlILQJkUhRm4CRkviSRs3BPfVCTfIpRoa8W/UCoj/p3XQDN53/1e9DLuG2/QIsJJHVbtuymivTjrkoUw0SZFHIwmQoCghXsmOFztKzABl+aU59K9ZotZpHnmvKNwdndC7kbewMCe5JG3KBYMikWzddNnSBg3o9F+AK5JpRwq5fvGw5SeoKRmDDBCD6i0lBSiAqdwhaJjFqb+UybTOqp4kBYfT62NRBjfQKo6VE2FeFimHDPa023Xmaw5ILWZ9o0L5HLqApzKiod5Qx4hmOAdBypsnT1BfSgMRiCTI/nje0coMHn8tiF/fwbi+rGNy7PG0cYa/8GQyxbRrwFFKjbMtZZeuza3pq5sRE3Ap1YZThiQQB4nbo76omJQaaU5KrpPa7JWYHulRoH8+QN2BO3bChRVP1g9Oew//Lu+u1kL/JOijYJUi8Wfde7h+N5TjB1D462LF/K1D6nWexdki6kjv5aoxsrUTs/4obp9xFuEfGJEUmIzq8kLMDgaX2Tvdg==
*/