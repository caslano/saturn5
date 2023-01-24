/*!
@file
Defines `boost::hana::symmetric_difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SYMMETRIC_DIFFERENCE_HPP
#define BOOST_HANA_SYMMETRIC_DIFFERENCE_HPP

#include <boost/hana/fwd/symmetric_difference.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/difference.hpp>
#include <boost/hana/union.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto symmetric_difference_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using SymmetricDifference = BOOST_HANA_DISPATCH_IF(symmetric_difference_impl<S>,
            true
        );

        return SymmetricDifference::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct symmetric_difference_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs&& xs, Ys&& ys) {
            return hana::union_(
                hana::difference(xs, ys),
                hana::difference(ys, xs)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SYMMETRIC_DIFFERENCE_HPP

/* symmetric_difference.hpp
CPuIRFQYHKgr10akIpdH24F9upoPj6XRkJmUKRDSCNRGJOvKlQLkkrfAY8jtHeCOxQ+T8fDawNqwEC32oHCBCK9ZPQ5bh8PW47AEZxDCwQGY8a44jJkgOaWOLaK4GQtaU2S6g+wzBjdKGOA5p2GHHKTBUTx2YPu6HiVzPcrSRuyDHklStS5sM9QpXbYO3dvU90wIPUP9/teu6QJStbz63n3Hq+9d8wZ4/9E9gmfuIdoJQA8d2AUdSQ//hB4qLHHfUJ82BmQMDjiltB0s+RNGL40HqnIHVOYOWCiVL16cIacYfgrhB/RYYLqjik2jFIO4RculA2cankzjPLZ0vM15N6l+mzN0Gtnm7LAGVxX5dJwrf4MtRTYoCKU/T4W2sk131LH5cKZBmc9+2IE3JFr8mDpdF3CMTUKV0gM9YaVSpuMtx2CT0mjeb3joAnbhdS6dldj+2zr3XR22LsDI7TFsyR4j1Ei4CjiGdxetUGv13MzZgfcVPtEN9hX+T2DjIAHepCyFqnvdDwpijRvQlkHuhrzj9GxYJscgFF2ojVeFvMCJEuquapNya+D5bBH6ZbMfwmYRbqXy1hQY0yPm50n/HEG/C0GaIQJUoteUIjQ5HFxFviYmp3uoTctHqemu7hsIdr/cDapztBhlQaC4rpUoikOWcmjmlhw0AbC7p3Doq7QWNmPSoJfOmEYhR6OwMQ0cek4rbkTjLt5osTUQ
*/