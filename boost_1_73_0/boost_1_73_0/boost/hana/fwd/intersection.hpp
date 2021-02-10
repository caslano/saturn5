/*!
@file
Forward declares `boost::hana::intersection`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INTERSECTION_HPP
#define BOOST_HANA_FWD_INTERSECTION_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct intersection_impl : intersection_impl<S, when<true>> { };
    //! @endcond

    struct intersection_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr intersection_t intersection{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INTERSECTION_HPP

/* intersection.hpp
eFpbyhgWQVaKzwG4DBFmOlACzzFJECOs0Jtf+s94ki6gfIT3CYZLBTcGPC/C+DMnIIbK5SCRlmjilA50DHwSCtNoinqeCT73FYQdAcgq0ms0RThhgdtYpBdPMIQmESbmbKVxHQWEiGOLMRJvuQkPIhlgKDHGKhQLAUAizAv2n2X5eJFyBcvck1QBHtrsQ3no9viqijixkUfnwwhuX719PxoMT3v9N89IGGVbHTb553Pf+3hQrHXW7/3QPR0cnrjq7i6v2z972z3tHRk1cwXew/3h4auTbnmRYfekO+z+VF6gd7hX/vCH3qC3FDyKs9Uz3ZeJf+EtwvSZaTka7QNjSCFtcYUAd9L0aFY/JILVXKA4sADmo8wECWbNWH6R1d4YfWCsm5kaDXSbufDSNczvOtsaxjEMfpcSluUB7IIq5EHXtEdA8aNyCHJA+0AAP4oXl1dCzpBngx7KIuYknPQ2Avm/L1Bd4tmtjqG01AOKCi3tm+iHyvuAhsezW3Q86oI1MCtihaLcIjn4RgPg2JDRY88mC7JRI5ENSAwVSms7jQ8/j0kP8fN5nIWZWheZigocid7uM+0xUZUqfN87FiB2Klj8YzWB2OAgnwy/O3139ua7LGIl3Dp/Bm5lLSh9wgLUWvtZ9vDLG7xTHZB8
*/