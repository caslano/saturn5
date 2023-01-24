/*!
@file
Defines `boost::hana::Iterable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_ITERABLE_HPP
#define BOOST_HANA_CONCEPT_ITERABLE_HPP

#include <boost/hana/fwd/concept/iterable.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/is_empty.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename It>
    struct Iterable
        : hana::integral_constant<bool,
            !is_default<at_impl<typename tag_of<It>::type>>::value &&
            !is_default<drop_front_impl<typename tag_of<It>::type>>::value &&
            !is_default<is_empty_impl<typename tag_of<It>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_ITERABLE_HPP

/* iterable.hpp
cfRW99/pu+12UDrn/ujO25ZC3WG8zV1y250SdAiIZjyrv/SYYoIWKhvMI5pHOELKdRbFZZUWAZSpPdeExQWBeMHgm7LgpnijwZeyYB3+JC1wxpsMvlHwEn4S4KUJ1Dd1QQrUXD4oKHQTjOcvYKR7E1YqBQOZjt77r7C3xhQLZUJxoJRBiWppR38jraiNkg8aNRAmtbRnG2JBbjE2xyFikNqexTf9DTCdG8San6J43WLmX42xXw0W3z30a/PdbW8VhTacHYp6cIov6PHGl01pymqSijXwFg7ApAPoa0z1Zcktqfx1nP4aBAxT25T2rHbpIoDzegfnt1P2Zu2VRvL+ylHmYg6gAnugFTcxwl9mXA0MfRQKSZPkQ4FEOxwJnmFmQ0CP+J207mZNueRcIpZJeI0l7176bGoOSkkpeE1KxuvERLzOteF1gRWu5Q8lzaOfkTPoZ6KFfuLM9DPVQD8zB6CWTz0Sl5GDnNLwbBr9mp9Nz8FRanl2Tg6dPQIDuDluHSFeMGzDj8/OgKfmuFS4YsWb49K0bmmOy9DuvOaVawOG5qo5WpfwZ85/levjQvDc0AHPNu3ZMwemSdYBI4yHvbCQe4aGhZSzsECs8v9fLHQCFv53bYdKKnXYfN60OL1pqJKpJ9hKzBJ/0yL0KyWBQAaNVG2Qb7YYmnPNHnjfLODXmCxTKcv958lSQ1nu17OoJ/x55ub4HHiWUw3y
*/