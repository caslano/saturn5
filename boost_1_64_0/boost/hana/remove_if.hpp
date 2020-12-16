/*!
@file
Defines `boost::hana::remove_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_IF_HPP
#define BOOST_HANA_REMOVE_IF_HPP

#include <boost/hana/fwd/remove_if.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/filter.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto remove_if_t::operator()(Xs&& xs, Pred&& pred) const {
        using M = typename hana::tag_of<Xs>::type;
        using RemoveIf = BOOST_HANA_DISPATCH_IF(remove_if_impl<M>,
            hana::MonadPlus<M>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::MonadPlus<M>::value,
            "hana::remove_if(xs, predicate) requires 'xs' to be a MonadPlus");
        #endif

        return RemoveIf::apply(static_cast<Xs&&>(xs),
                               static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename M, bool condition>
    struct remove_if_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::filter(static_cast<Xs&&>(xs),
                        hana::compose(hana::not_, static_cast<Pred&&>(pred)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_IF_HPP

/* remove_if.hpp
wWzfFoU0HX506Abq0eibEi3HhReWuSm1nuqu4ZjORyNqzCC61v7Uj3Qn4+NjorYwGs79Rz7wUuZHBX4cpxjvzxv1By6yyhltEn7nilfFTh+Nj6GtCS3XMQ8JK3rTYzEsQnwg30zLHO8rozuHkX9pJFsog/paKJPtvZ2WVpk+07eDSSx8en8c4Jodz8kLo/E3PoZxA+MPesxhscThRpVfNohhyHCd/HCEh9XIrmoKv4a3oU0ADQSbVfAQzZGR/BWL4iodyfgIH6C2LERR+XMFVDx4vaZeOuluTPgAbuVojArtql5XrAvlh5cRcrtODqrHx7jklE/PNNeN1IVgYJKDV3Lik4K2qU/J6vfAsXXRVlIzeKqzy/5F5/SoQ5O8BST++KvzNsD84EXT917DOK8Nj0IMm0eNdOq1rW3Xt4hxFmN7jPEb3kjLGWZl0etSVljMtrN4aNf70ai/XVnB/2b2DWj+pKRzaYny4jy8R7hC9AfyopMBvt1ykisyPgUTlRGl1e1/+a60/nDyroR6bcrzuGoCjAJMcgAimsHvf0o2JoLZtrW2rNnaxsRvS/sgp2aRD/r03bJyPlhEVVhdF6T/Sb7CHWzQFQ++F+N1/r6MXwf8Oi6tU2N8OcIO9RxjWe0C5WVY7REe2r5g/t6xcWofvMbzun9D6WULZ4stSiU0e8D2ftSCrgbzHTyVQaRJGw9cGhixcWI/zr9nb7hVrW1BgPPUsGuNvPdwjh2d8WN/MOUle9aBfqgxjWL3O7u6B7zy1mFz1ncH+eORtF1vpLyEYVLoshWFZifBXWQ98gFNZIgDD1/OL1twn930sggMmWc1Ha+Ml38H66UwhWJqezeqMLHs3sD+kRBEBhgNzBmRhQ7/hPIqma0L3Xs7In0m9BB7BN/7KPw94lkm/gPf7P3oJOV31FVt2zVtwVbOTe2gthLtgzJaK3nJ+84B7ep5pE1z6iylXSqV4Z1UNUvapxlsnT1Kf9ypqq69PxnG7qA48hf/JJ+vXDd1V0Z/v7wGtOF6JpTJbKBK3bVcVswDK5NFkpy2t7dwyW2mPr0661MljbFWiVgtaWiif3PWJwPXEg0tjfRkgBFPLqNvneqqzulITwa5SXcmSs87H1+gdX3VRJyPI4NjwXY4SybEgT/uK54Va5L8mc0rb7/vnC47jw3mvDy9HidWmk7bmxC6anAeWIJbQ4Y/ctuf5vK6sUrZtpcsbQfwOoqG1zMrfLrP3D/j47F9tNPCavDrJc+50M2d2EK4NEXzxf0dvz/AnEGbCsprqYKPYWrXMoJAE8V81Sccwz2M8w5lM9x0LkEOdCDTrm/srqFpI5S7GzDRad5slWneZOU1U60wXde2bAT7gPstwYDC/Z7yEB2zRdFp2bt4+Zy9QUEKvR0x8q0XfkZ5Odb2yikQUwkvugzGrPyGxFAnT3kd57ruQeCshptUGki8G/wsH4e2lIUtTMHuE5Fy0IM24qB5L3reom4B7wavyuWSWiqlWmNRT+HPfwLaHl/8x/Y207fqV43eb+vaVby0I7vpgzlSLFLaRy6Zs7DqrXbB5iFghs4CtSJjMvefkvHxttyNc22hmY4RqYgd0emxegYGksrNb8t4layxVddVbYfzbzPgkEMXUbmDDuTQt1WV5ISMj2B94V8wVZ34oGvuHE7QHuRz+cym1QAfo4SyJvGZjO3qvVsEwY/wMak/fS1Y039I7yJeRgL9efQXfkpID+YBwXbnbWhHDuruSvYYCz7mXSXlRbuikI523qB0gyxMR1tv5ws4X+AaIT3Foi+Lk7xG2msnHrVYXiC01xvSrZAnMO2GIc0/IE/rujGkBQUn/KDlbxLST9ynbKZpNwtpXno=
*/