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
wztiJO1qdjiEKrlTnpNKQ3KzDhrBBbsIeB35P8yypRBWbLu02DhdZQRi1mZmbSXj9EaCF1q/Okbg69BwQ35kaT4DC3jri2bn0nkd0dpdIG6x0lljG/tXH4WCFL/isaioKF4fqavbgEMyfQn4vXk3eai2S5X7Mj/DVr6bScZNVXIjzLUV8dTeo95QrDV2aaLTTDl+inofU2GJ/KFrUw5R3Zye2wfNNi1e5bNLl2hApbwU9RUGsVj2TAAGl/8O+124wE6gbxUn7XwLUPaVBMMnn/Erg7B60x4kPKaY9vCAp0V4ejeJJi6SGMGCqKnINq2JnxJkQfg30Zh44PkHJ7Ue0wILYNgG2DAotJ57Gax9yf4qG0bc1l+U9a6naIDZfhX1ddkBSVI6uWSEnQh8n2Hq1C5OYIpD2pP6fmfytJlu5JkSB2iRI6z9EZ7J3TQ03fhcJz1yZVwm2MNGvAYOTbI/Cbir9IUC3r0M8BeunjcJcpiWMMQl6wm43DKI49M0gxrKIBVy6V7Ag3IpAgrhckOyeuShQxQ8CjUt58KCHLFacwwSX0SEE9txYr1cDA==
*/