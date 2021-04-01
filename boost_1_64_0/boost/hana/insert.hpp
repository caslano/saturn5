/*!
@file
Defines `boost::hana::insert`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INSERT_HPP
#define BOOST_HANA_INSERT_HPP

#include <boost/hana/fwd/insert.hpp>

#include <boost/hana/append.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/take_front.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Set, typename ...Args>
    constexpr decltype(auto) insert_t::operator()(Set&& set, Args&& ...args) const {
        return insert_impl<typename hana::tag_of<Set>::type>::apply(
            static_cast<Set&&>(set),
            static_cast<Args&&>(args)...
        );
    }
    //! @endcond

    template <typename T, bool condition>
    struct insert_impl<T, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct insert_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename N, typename Element>
        static constexpr auto apply(Xs&& xs, N const& n, Element&& e) {
            return hana::concat(hana::append(hana::take_front(xs, n),
                                             static_cast<Element&&>(e)),
                                hana::drop_front(xs, n));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INSERT_HPP

/* insert.hpp
c6I8omwmPlTZNu0UQ1448yA4LwcA+LqY8kB2cyG+2Vt8rnYkYCPZrwx8XNg08H02z4xlcxN4WrEf1FNqVRFuAsVJweSUjMKOw8h9ERVi8EEinc46TvnVOlJhq7+/40ft8SP5ZoFZ3x+bbi2vexOukVLS20fn27gWHl+xRNNs68K9NMGTGBm4660bnGj1a0bStBhw4mHbqdZrrrmsjF6Kd0ZRMW2zT0uwOsMIkoIoIdLu83fiLI9A2Q4QwhKZlI61H4KM5vEI5JQ70DGcRtXH9kcHoF5FwzZde52sJG8ybfyJHEU4j+IVha1mT9hhv7szXHRtnaBEZJwc3Rg0aXbG9EEvSeabvcQz4c28EUUbvIJM51yZRGTP5saEnJHEaEdvBQafj/YhFSG2Mg5Z09F4eR1w4T/0CBY45OLxQyHL/dV43SqhzkWKc3tPfyUZrPWi3jJ/3lypbptBCS6AePN0Xq6YvkCVMDJ7U6dyQa/rwJD2oOCDycLZy2uT9xagBIXAU4L65YP699zzEssn/kdrx4Tm7QeYTMM02sex1BGk6BqiWb1eagtBx7rGgw==
*/