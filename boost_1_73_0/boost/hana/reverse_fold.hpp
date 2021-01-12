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
+5vkGSDPgFL1rCD5IEwI/tCUUnFO2oAiQHHijYGDOo42/Nmwm9eO9DTrwRGCIpGaA547scK8ssM48fUd3DFtQrSeo3xpnAsI5n07J3iD/sc5nfd05m1jMA/toMIaHag4Id6LZEDJgr5Yl9mRwANuFlnO7EDy+GFADowQkD4DgiU7bY7h8otJ1aNE2Q5Q0US4ASTw0Oq7IyytMh/eKMMPOnk1f6XjDImcfbIIHYloitH+FdqB
*/