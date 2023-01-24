/*!
@file
Defines `boost::hana::intersection`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INTERSECTION_HPP
#define BOOST_HANA_INTERSECTION_HPP

#include <boost/hana/fwd/intersection.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto intersection_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Intersection = BOOST_HANA_DISPATCH_IF(intersection_impl<S>,
            true
        );

        return Intersection::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct intersection_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INTERSECTION_HPP

/* intersection.hpp
6lqernerk/oXdYgZRuDwnrA51CFGm7OSn92sFmwGirF8EhcwHQ8Xqn4vBj1EeTw8pve0R9Mk9UdqXsN29xgqir8ZDO52jH1LEHAzsFIKMXx+XH2cUFEueuPp3PnRHO6faVdzmbWLEZ3RPXvySJn3fNGbQk+eUkpYTo++LYeXWkknctom5oVG0RvpRL9vF29wLS81tX41p1nS3SjrrUDwpSunIM/ddzq43c65YOWaNaPXvFl66t0eqgsvjTsxZadCi6HjkmsVoamfD/2vlVdJ3X+jvEoO/p8sr4fqqtufss/E0lNPoRZaEbJnM2+dmEFoUdQiNWlMWMC1r3lC40b9ohn6OzMfe5h5i5NoJ5nNhBA2KCGO0Gg1pPIYkPQ/avc7zKP1oLjqSjM3bFXU/8v7U9KPS28FxmdzmHL1+VA7z3PP5/R8ZFHIy1qdto/Jeu3K8z/vsY+HUuW7VXqL0zs0U7xFiV9WSEcrxlqsCn45ZSHUYFfyxkNnxgPDSRItlcHOc6Fxs6QPl3IkPnr0lCR9NLZXzrRRw2jiKf37cavK1+GuN0+tyeNULUuVW2OSGAsr3zV63tc63E+V6y2e8XU8hBgOTxLAFl1pThPLn6SJ0RoT42OzmyY7n8sUMbXQ+aFOK9drhJrDRxgGSFUeIhLiFYvRAUlRVCUttZbLqmeEKo2H5WNUj0zgL+IhYlCroB7PxKQ1oRJ3zyG95xK5
*/