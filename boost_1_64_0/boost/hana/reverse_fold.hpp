/*!
@file
Defines `boost::hana::reverse_fold`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REVERSE_FOLD_HPP
#define BOOST_HANA_REVERSE_FOLD_HPP

#include <boost/hana/fwd/reverse_fold.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/fold_right.hpp>
#include <boost/hana/functional/flip.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename S, typename F>
    constexpr decltype(auto) reverse_fold_t::operator()(Xs&& xs, S&& s, F&& f) const {
        return hana::fold_right(static_cast<Xs&&>(xs),
                                static_cast<S&&>(s),
                                hana::flip(static_cast<F&&>(f)));
    }

    template <typename Xs, typename F>
    constexpr decltype(auto) reverse_fold_t::operator()(Xs&& xs, F&& f) const {
        return hana::fold_right(static_cast<Xs&&>(xs),
                                hana::flip(static_cast<F&&>(f)));
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REVERSE_FOLD_HPP

/* reverse_fold.hpp
N+VTopqqdrrDt/oyxpQOpc53IlYFDoGpBObGjjsEUxXT5niPeZX7+bD8dv/OcToqBx9u3fl8uixiudTnhzJrrlF9xfnZf7bo2VCNVcjMjtdl0duT+2j2zc4dee3srLZbohYUbYahh//r2+r7tL5fSKgr8NoLNMIXhfZF+3/B97vUuld+y9/4FTszjgb8A8c8YmhV7hNVO1LfyeC1OW9FKO6+MruWJTbnIShE7VqKZKjQ510spOj26zKVoddtqUGp90S+iu0HL4SV0TVwCjX/vP3oxuSzvk0Fs1QV6Zwn0q7rjZuPft3LRvpsua06SaAAmRaaWfIMiLmjNI2zyKfSWTcYQ+yCucQORgbSypdZGYcHcHdnmm0mwuc3xH772PXz6i0uvuXn81aVzI2mjqMy87+16QybQlCAYvuvAa0Z3gjPjX5KawCLrYmy/5mnkb7wLP6R6kA15mM6EDZzVaSQYS2zlIgNGIcxiX6QmtzZwvD5iwWxHBt3ObxUEO8o0VqL/xQIcJb5ym0vZIUJi7dGUdECMR3fTXkJHpksOklEOUGY0gheahor+IafpA==
*/